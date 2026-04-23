// Fill out your copyright notice in the Description page of Project Settings.


#include "TesterCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "InvenComponent.h"
#include "Blueprint/UserWidget.h"
#include "Item.h"
#include "TestPlayerController.h"
#include "DynamicMesh/DynamicMesh3.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATesterCharacter::ATesterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Component"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 100.0f;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	CharacterInven = CreateDefaultSubobject<UInvenComponent>(TEXT("InventoryComp"));
	

}

// Called when the game starts or when spawned
void ATesterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATesterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATesterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ATestPlayerController* PlayerController = Cast<ATestPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInputComponent->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ATesterCharacter::Move);
			}
			
			if (PlayerController->LookAction)
			{
				EnhancedInputComponent->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ATesterCharacter::Look);
			}
			
			if (PlayerController->InventoryAction)
			{
				EnhancedInputComponent->BindAction(
					PlayerController->InventoryAction,
					ETriggerEvent::Started, 
					this,
					&ATesterCharacter::ShowInventory);
			}
			
			
			if (PlayerController->ShowTitles)
			{
				EnhancedInputComponent->BindAction(
					PlayerController->ShowTitles,
					ETriggerEvent::Started,
					this,
					&ATesterCharacter::ShowTitles);
			}
			
			if (PlayerController->UseItems)
			{
				EnhancedInputComponent->BindAction(
					PlayerController->UseItems,
					ETriggerEvent::Started,
					this,
					&ATesterCharacter::UseItems);
			}
			
			
		}
	}

}


void ATesterCharacter::ShowInventory()
{
	if (CharacterInven->InvenCheck.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("The Inventory is Empty!"));
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Inventory Empty"));
		}
	}
	else
	{
		for (const auto& items : CharacterInven->InvenCheck)
		{
			
			FString DisplayMsg = FString::Printf(TEXT("Item : %s , Number : %d"), *items.Key, items.Value);

			
			UE_LOG(LogTemp, Display, TEXT("%s"), *DisplayMsg);

			
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, DisplayMsg);
			}
		}
		
	}
	
	if (!InventoryWidgetClass) return;
	

	if (!bIsInventoryOpen)
	{
		
		if (!InventoryWidgetInstance)
		{
			InventoryWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), InventoryWidgetClass);
		}

		if (InventoryWidgetInstance)
		{
			
			InventoryWidgetInstance->AddToViewport();
			bIsInventoryOpen = true;
			
			
			FString FullList = "";
			for (const auto& item : CharacterInven->InvenCheck)
			{
				FullList += FString::Printf(TEXT("%s : %d\n"), *item.Key, item.Value);
			}

			
			UFunction* Func = InventoryWidgetInstance->FindFunction(FName("UpdateInventoryText"));
			if (Func)
			{
				InventoryWidgetInstance->ProcessEvent(Func, &FullList);
			}
		}
		
		
	}
	else
	{
		
		if (InventoryWidgetInstance)
		{
			InventoryWidgetInstance->RemoveFromParent();
			bIsInventoryOpen = false;
		}
	}
	
	
}

void ATesterCharacter::ShowTitles()
{
	if (CharacterInven->AcquiredTitles.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("The Title is Empty!"));
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("No Title"));
		}
	}
	else
	{
		for (const auto& titles: CharacterInven->AcquiredTitles)
		{
			FString DisplayMsg = FString::Printf(TEXT("Titles : %s"), *titles);
			
			
			UE_LOG(LogTemp, Display, TEXT("%s"), *DisplayMsg);

			
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, DisplayMsg);
			}
			
		}
	}
	
	if (!TitleWidgetClass) return;
	

	if (!bIsTitleOpen)
	{
		
		if (!TitleWidgetInstance)
		{
			TitleWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), TitleWidgetClass);
		}

		if (TitleWidgetInstance)
		{
			TitleWidgetInstance->AddToViewport();
			bIsTitleOpen = true;

			FString FullList = "";
			for (const auto& item : CharacterInven->AcquiredTitles)
			{
				FullList += FString::Printf(TEXT("%s\n"), *item);
			}

			
			struct FTitleShowParams
			{
				FString DisplayText; 
			};

			FTitleShowParams Params;
			Params.DisplayText = FullList;

			UFunction* Func = TitleWidgetInstance->FindFunction(FName("TitleShow"));
			if (Func)
			{
				
				TitleWidgetInstance->ProcessEvent(Func, &Params);
			}
		}
		
		
	}
	else
	{
		
		if (TitleWidgetInstance)
		{
			TitleWidgetInstance->RemoveFromParent();
			bIsTitleOpen = false;
		}
	}
	
	
}

void ATesterCharacter::UseItems()
{
	if (CharacterInven->Inventory.Num() == 0)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("사용할 아이템이 없습니다."));
		}
		return;
	}
	UInvenItemInstance* TargetItem = CharacterInven->Inventory[0];
	if (!TargetItem) return;

	FString ItemName = TargetItem->Data.Name;

	if (CharacterInven->InvenCheck.Contains(ItemName))
	{
		CharacterInven->InvenCheck[ItemName]--;

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, FString::Printf(TEXT("%s 아이템을 사용했습니다!"), *ItemName));
		}

	
		if (CharacterInven->InvenCheck[ItemName] <= 0)
		{
			CharacterInven->InvenCheck.Remove(ItemName);
			CharacterInven->Inventory.RemoveAt(0); 
		}
	}


	if (bIsInventoryOpen && InventoryWidgetInstance)
	{
		FString FullList = "";
		for (const auto& item : CharacterInven->InvenCheck)
		{
			FullList += FString::Printf(TEXT("%s : %d\n"), *item.Key, item.Value);
		}

		UFunction* Func = InventoryWidgetInstance->FindFunction(FName("UpdateInventoryText"));
		if (Func)
		{
			InventoryWidgetInstance->ProcessEvent(Func, &FullList);
		}
	}
}


void ATesterCharacter::Move(const FInputActionValue& val)
{
	if (!Controller) return;


	const FVector2D MoveInput = val.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}

void ATesterCharacter::Look(const FInputActionValue& val)
{
	
	
	FVector2D LookInput = val.Get<FVector2D>();


	AddControllerYawInput(LookInput.X);

	AddControllerPitchInput(LookInput.Y);
}




// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TesterCharacter.generated.h"

struct FInputActionValue;

class UInvenComponent;
class AInventory;
class USpringArmComponent;
class UCameraComponent;
class AItem;
class UUserWidget;

UCLASS()
class MASTER_WORKSPACE_API ATesterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATesterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inven")
	TObjectPtr<UInvenComponent> CharacterInven;
	
	//Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UsingItem")
	TObjectPtr<AItem> Item;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InventoryWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UUserWidget> InventoryWidgetInstance;
	
	bool bIsInventoryOpen = false;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> TitleWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UUserWidget> TitleWidgetInstance;
	
	bool bIsTitleOpen = false;
	
	UFUNCTION()
	void ShowInventory();
	
	UFUNCTION()
	void ShowTitles();
	
	UFUNCTION()
	void UseItems();
	
	
	
	//Actions Binding
	void Move(const FInputActionValue& val);
	
	void Look(const FInputActionValue& val);
	
};

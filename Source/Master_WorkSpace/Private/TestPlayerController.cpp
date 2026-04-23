// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"


ATestPlayerController::ATestPlayerController() : InputMappingContext(nullptr), MoveAction(nullptr), LookAction(nullptr)
{
}

void ATestPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
	
	if (HUDWidgetClass)
	{
		UUserWidget * HUDWidget = CreateWidget<UUserWidget> (this, HUDWidgetClass);
		
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
	
	
}

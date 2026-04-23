// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class MASTER_WORKSPACE_API ATestPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATestPlayerController();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> InventoryAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> UseItems;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> ShowTitles;
	
	void BeginPlay() override;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass;
	
};

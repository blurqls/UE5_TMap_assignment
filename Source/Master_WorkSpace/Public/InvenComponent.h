// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.h"
#include "InvenComponent.generated.h"

class AItem;

UCLASS()
class UInvenItemInstance : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FItemData Data;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MASTER_WORKSPACE_API UInvenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInvenComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Inventory")
	TArray<TObjectPtr<UInvenItemInstance>> Inventory; 
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(FItemData ItemData);
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItems")
	TArray<TSubclassOf<AActor>> AvaliableItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TMap<FString, int32> InvenCheck; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSet<FString> AcquiredTitles;
	
	
	UFUNCTION(Blueprintable, Category = "Titles")
	void AddTitle(FString GetTitle);
	
};


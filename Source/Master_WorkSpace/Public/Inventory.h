#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inventory.generated.h"



UCLASS()
class MASTER_WORKSPACE_API AInventory : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AInventory();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Inventory")
	TArray<TObjectPtr<AActor>> Inventory; 
	
	UFUNCTION(Blueprintable, Category = "Inventory")
	void AddItem(AActor* Item);
	
	//Items that can go in Inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryItems")
	TArray<TSubclassOf<AActor>> AvaliableItem;
	
	
	
};

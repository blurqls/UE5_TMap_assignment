// Fill out your copyright notice in the Description page of Project Settings.


#include "InvenComponent.h"

// Sets default values for this component's properties
UInvenComponent::UInvenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInvenComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInvenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UInvenComponent::AddItem(FItemData ItemData)
{
	if (InvenCheck.Contains(ItemData.Name))
	{
		
		InvenCheck[ItemData.Name]++;
	}
	else
	{
		
		UInvenItemInstance* NewInstance = NewObject<UInvenItemInstance>(this);
		NewInstance->Data = ItemData; 
		Inventory.Add(NewInstance);
		InvenCheck.Add(ItemData.Name, 1);
	}
}

void UInvenComponent::AddTitle(FString GetTitle)
{
	if (!AcquiredTitles.Contains(GetTitle))
	{
		AcquiredTitles.Add(GetTitle);
	}
	
}




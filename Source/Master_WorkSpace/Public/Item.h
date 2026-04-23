#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USceneComponent;
class USphereComponent;
class UStaticMeshComponent;

// 아이템 데이터를 담는 구조체
USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TitleName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RequiredTitle;
};

UCLASS()
class MASTER_WORKSPACE_API AItem : public AActor
{
	GENERATED_BODY()
    
public: 
	AItem();
    
	// 개별 변수들을 FItemData 하나로 통합 관리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FItemData ItemInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InvenType")
	bool isInvenSave; 

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> RootScene;
    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> Collider;
    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMesh;
    
	UFUNCTION()
	virtual void OnItemOverlap(
	   UPrimitiveComponent* OverlappedComp,
	   AActor* OtherActor,
	   UPrimitiveComponent* OtherComp,
	   int32 OtherBodyIndex,
	   bool bFromSweep,
	   const FHitResult& SweepResult);
    
	UFUNCTION()
	virtual void OnItemEndOverlap(
	   UPrimitiveComponent* OverlappedComp,
	   AActor* OtherActor,
	   UPrimitiveComponent* OtherComp,
	   int32 OtherBodyIndex); 

	virtual void ActivateItem(AActor* Activator);
    
	UFUNCTION()
	FString GetItemName();
};
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGun.generated.h"

UCLASS()
class MASTER_WORKSPACE_API ABaseGun : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABaseGun();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;
	
	
	//상속되는 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
	float Recoil; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
	int32 Ammo;

	UFUNCTION(BlueprintCallable, Category = "Gun")
	virtual void GunTrace();
};

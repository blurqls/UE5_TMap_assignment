#pragma once

#include "CoreMinimal.h"
#include "BaseGun.h"
#include "Rifle.generated.h"

UCLASS()
class MASTER_WORKSPACE_API ARifle : public ABaseGun
{
	GENERATED_BODY()

public:
	ARifle();

	
	virtual void GunTrace() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* GunMesh;

private:
	void ApplyRecoil();
	void RecoverRecoil(float DeltaSeconds);

	float FireTimer     = 0.0f;
	float CurrentPitch  = 0.0f;
	bool  bIsRecovering = false;

	// 라이플 설정값 (기획에 따라 수정 가능)
	const float FireInterval = 0.2f;  // 연사 속도 (초당 약 6~7발)
	const float RecoverSpeed = 10.0f;  
};
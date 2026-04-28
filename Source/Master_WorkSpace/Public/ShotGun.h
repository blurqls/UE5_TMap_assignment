#pragma once

#include "CoreMinimal.h"
#include "BaseGun.h"
#include "ShotGun.generated.h"

UCLASS()
class MASTER_WORKSPACE_API AShotGun : public ABaseGun
{
	GENERATED_BODY()
    
public:
	AShotGun();

	virtual void GunTrace() override;
	void Tick(float DeltaSeconds) override;

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* GunMesh;

private:
	// 반동 관련
	void ApplyRecoil();       // 반동 적용
	void RecoverRecoil(float DeltaSeconds);  // 원상복귀

	float FireTimer    = 0.0f;   // 발사 간격 타이머
	float CurrentPitch = 0.0f;   // 현재 반동 각도
	bool  bFired       = false;  // 발사 여부

	const float FireInterval   = 3.0f;   // 발사 간격 (초)
	const float RecoverSpeed   = 7.0f;  // 복귀 속도 (도/초)
};
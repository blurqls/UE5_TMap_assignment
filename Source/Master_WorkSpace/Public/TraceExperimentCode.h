/* 해당 TraceExperimentCode는 Trace의 여러 방식을 실험해보기 위한 코드로 본 프로젝트에서는 여러 방식을 
 * 직접 구현해보고, 테스트 할뿐 실제 과제에는 포함하지 않습니다!
 * 일종의 더미 코드로 봐주시면 감사하겠습니다 
 */ 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TraceExperimentCode.generated.h"

class UNiagaraSystem;

UCLASS()
class MASTER_WORKSPACE_API ATraceExperimentCode : public AActor
{
	GENERATED_BODY()
	
public:	
	ATraceExperimentCode();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	void LineTraceSingle();
	
	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<UNiagaraSystem> BulletEffect;
	
	UFUNCTION()
	void FireNiagaraBullet();
};

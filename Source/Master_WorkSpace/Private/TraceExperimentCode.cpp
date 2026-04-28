// Fill out your copyright notice in the Description page of Project Settings.


#include "TraceExperimentCode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ATraceExperimentCode::ATraceExperimentCode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATraceExperimentCode::BeginPlay()
{
	Super::BeginPlay();
	
	FireNiagaraBullet();
	
}

// Called every frame
void ATraceExperimentCode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	LineTraceSingle();
}


void ATraceExperimentCode::LineTraceSingle()
{
	FHitResult HitResult;
	
	TArray<AActor*> IgnoreActors;
	
	IgnoreActors.Add(this);
	
	UKismetSystemLibrary::LineTraceSingle(
		//현재 Actor가 존재하는 월드를 기준으로 하기위한 부분
		GetWorld(),
		
		//LineTrace의 시작점
		GetActorLocation(),
		
		//LineTrace를 어디까지 쏴서 추적할건지
		GetActorLocation() + GetActorForwardVector()*1000.f, 
		
		//어떤 채널 쓸거임
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		
		//Complexity
		false,
		
		//무시할 액터
		IgnoreActors,
		
		//몇 프레임동안 표시
		EDrawDebugTrace::ForOneFrame,
		
		//저장
		HitResult,
		
		true,
		
		FLinearColor::Red,
		
		FLinearColor::Green
		);
	
	
}

void ATraceExperimentCode::FireNiagaraBullet()
{
	if (BulletEffect)
	{
		UE_LOG(LogTemp, Warning, TEXT("나이아가라 발사 성공!"));
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		   GetWorld(),
		   BulletEffect,
		   GetActorLocation(),
		   GetActorRotation()
		);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("에러: BulletEffect 에셋이 할당되지 않았습니다!"));
	}
}


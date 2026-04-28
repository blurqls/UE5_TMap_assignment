#include "BaseGun.h"
#include "Kismet/KismetSystemLibrary.h"


ABaseGun::ABaseGun() : Recoil(0.0f), Ammo(100)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseGun::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ABaseGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseGun::GunTrace()
{
	//Default is Single Trace
	
	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	
	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector()* 100.f,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForOneFrame,
		HitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green);
	
}


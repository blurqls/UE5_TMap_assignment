#include "Rifle.h"
#include "Kismet/KismetSystemLibrary.h"

ARifle::ARifle()
{
    PrimaryActorTick.bCanEverTick = true;

    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    SetRootComponent(RootScene);

    GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
    GunMesh->SetupAttachment(RootScene);
	
	Recoil = 1.5f;
}

void ARifle::GunTrace()
{
    const float TraceDistance = 5000.0f; // 라이플이므로 사거리를 길게 설정

    FVector MuzzleLocation = GunMesh->GetSocketLocation(TEXT("MuzzleSocket"));
    // 소총은 부채꼴 확산 없이 정면(Forward)으로 한 발만 발싸
    FVector ShotDir = GetActorForwardVector();
    FVector TraceEnd = MuzzleLocation + (ShotDir * TraceDistance);

    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(this);

    FHitResult HitResult;

    // Single Trace 사용
    bool bHit = UKismetSystemLibrary::LineTraceSingle(
        GetWorld(),
        MuzzleLocation,
        TraceEnd,
        UEngineTypes::ConvertToTraceType(ECC_Visibility),
        false,
        ActorsToIgnore,
        EDrawDebugTrace::ForDuration, 
        HitResult,
        true,
        FLinearColor::Blue, // 라이플은 파란색으로 구분
        FLinearColor::Yellow,
        1.0f
    );

    if (bHit)
    {
        // 히트 시 로직
        UE_LOG(LogTemp, Log, TEXT("Rifle Hit: %s"), *HitResult.GetActor()->GetName());
    }
}

void ARifle::ApplyRecoil()
{
    // 발사 시마다 누적되는 반동
    CurrentPitch += Recoil;

    FRotator NewRotation = GetActorRotation();
    NewRotation.Pitch += Recoil;
    SetActorRotation(NewRotation);

    bIsRecovering = true;
}

void ARifle::RecoverRecoil(float DeltaSeconds)
{
   
    float PreviousPitch = CurrentPitch;
    CurrentPitch = FMath::FInterpTo(CurrentPitch, 0.0f, DeltaSeconds, RecoverSpeed);
    
    // 줄어든 만큼 실제 액터의 회전값에서 빼줌
    float PitchDelta = PreviousPitch - CurrentPitch;
    
    FRotator NewRotation = GetActorRotation();
    NewRotation.Pitch -= PitchDelta;
    SetActorRotation(NewRotation);

    if (FMath::IsNearlyZero(CurrentPitch, 0.05f))
    {
        CurrentPitch = 0.0f;
        bIsRecovering = false;
    }
}

void ARifle::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    FireTimer += DeltaSeconds;

    // 자동 연사 로직
    if (FireTimer >= FireInterval)
    {
        FireTimer = 0.0f;
        GunTrace();
        ApplyRecoil();
    }

    // 반동 복귀 로직
    if (bIsRecovering)
    {
        RecoverRecoil(DeltaSeconds);
    }
}
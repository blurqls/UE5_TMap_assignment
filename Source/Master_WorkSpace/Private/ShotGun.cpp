#include "ShotGun.h"
#include "Kismet/KismetSystemLibrary.h"

AShotGun::AShotGun()
{
    PrimaryActorTick.bCanEverTick = true;
    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    SetRootComponent(RootScene);
    
    GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
    GunMesh->SetupAttachment(RootScene);
}


void AShotGun::GunTrace()
{
    const int32 PelletCount    = 10;
    const float SpreadAngleDeg = 60.0f;  
    const float TraceDistance  = 500.0f;

    FVector Forward        = GetActorForwardVector();
    FVector MuzzleLocation = GunMesh->GetSocketLocation(TEXT("MuzzleSocket"));

    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(this);

    for (int32 i = 0; i < PelletCount; ++i)
    {
        float RandomAngle = FMath::RandRange(-SpreadAngleDeg / 2.0f, SpreadAngleDeg / 2.0f);
        FVector ShotDir   = Forward.RotateAngleAxis(RandomAngle, FVector::UpVector);
        FVector TraceEnd  = MuzzleLocation + ShotDir * TraceDistance;

        FHitResult HitResult;

        UKismetSystemLibrary::LineTraceSingle(
            GetWorld(),
            MuzzleLocation,
            TraceEnd,
            UEngineTypes::ConvertToTraceType(ECC_Visibility),
            false,
            ActorsToIgnore,
            EDrawDebugTrace::ForOneFrame,
            HitResult,
            true,
            FLinearColor::Red,
            FLinearColor::Green,
            3.0f
        );
    }
}


void AShotGun::ApplyRecoil()
{
 
    CurrentPitch += Recoil; 

    FRotator NewRotation = GetActorRotation();
    NewRotation.Pitch = CurrentPitch;
    SetActorRotation(NewRotation);

    UE_LOG(LogTemp, Warning, TEXT("[ShotGun] 반동 적용: %.1f"), CurrentPitch);
}


void AShotGun::RecoverRecoil(float DeltaSeconds)
{
    if (FMath::IsNearlyZero(CurrentPitch, 0.1f))
    {
        CurrentPitch = 0.0f;
        return;
    }

    // 천천히 0도로 복귀
    CurrentPitch = FMath::FInterpTo(CurrentPitch, 0.0f, DeltaSeconds, RecoverSpeed);

    FRotator NewRotation = GetActorRotation();
    NewRotation.Pitch = CurrentPitch;
    SetActorRotation(NewRotation);
}

// 3초마다 발사 + 반동 복귀
void AShotGun::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    FireTimer += DeltaSeconds;

    if (FireTimer >= FireInterval)
    {
        FireTimer = 0.0f;
        bFired    = true;

        GunTrace();
        ApplyRecoil(); 
    }

    if (bFired)
    {
        RecoverRecoil(DeltaSeconds);

        // 완전히 복귀하면 다음 발사 대기
        if (FMath::IsNearlyZero(CurrentPitch, 0.1f))
        {
            bFired = false;
        }
    }
}
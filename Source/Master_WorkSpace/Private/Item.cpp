#include "Item.h"
#include "TesterCharacter.h"
#include "InvenComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AItem::AItem() : isInvenSave(true)
{
    PrimaryActorTick.bCanEverTick = false; // 특별한 로직이 없다면 틱은 끄는 게 성능에 좋습니다.
    
    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    SetRootComponent(RootScene);
    
    Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
    Collider->SetupAttachment(RootScene);
    Collider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(RootScene);
    
    Collider->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnItemOverlap);
    Collider->OnComponentEndOverlap.AddDynamic(this, &AItem::OnItemEndOverlap);
    
    // 구조체 초기화
    ItemInfo.Name = TEXT("Collectable Item");
    ItemInfo.TitleName = TEXT("First Item Receiver");
    ItemInfo.RequiredTitle = TEXT("");
}

void AItem::OnItemOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->ActorHasTag(TEXT("Player")))
    {
        UE_LOG(LogTemp, Display, TEXT("Player Tag Detected! Calling ActivateItem..."));
        ActivateItem(OtherActor);
    }
}

void AItem::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AItem::ActivateItem(AActor* Activator)
{
    ATesterCharacter* MainCharacter = Cast<ATesterCharacter>(Activator);
    
    if (MainCharacter && MainCharacter->CharacterInven)
    {
        
        MainCharacter->CharacterInven->AddItem(this->ItemInfo);
        
        
        MainCharacter->CharacterInven->AddTitle(this->ItemInfo.TitleName);
        
      
        UE_LOG(LogTemp, Display, TEXT("성공: [%s] 아이템이 인벤토리에 추가됨!"), *ItemInfo.Name);
        UE_LOG(LogTemp, Display, TEXT("성공: [%s] 칭호가 획득됨!"), *ItemInfo.TitleName);
        
       
        if (GEngine)
        {
            FString InvenMsg = FString::Printf(TEXT("%s 아이템을 획득했다!"), *ItemInfo.Name);
            GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, InvenMsg);

            FString TitleMsg = FString::Printf(TEXT("새로운 칭호: [%s]"), *ItemInfo.TitleName);
            GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, TitleMsg);
        }
        
        
        Destroy();
    }
}

FString AItem::GetItemName()
{
    return ItemInfo.Name;
}
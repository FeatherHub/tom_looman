#include "RoguePotionBase.h"

#include "Components/SphereComponent.h"
#include "Core/RogueGameType.h"
#include "Kismet/GameplayStatics.h"


ARoguePotionBase::ARoguePotionBase()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	PickupSoundEffect = CreateDefaultSubobject<USoundBase>(TEXT("PickupSoundEffect"));
	
	RootComponent = SphereComp;
	MeshComp->SetupAttachment(SphereComp);

	SphereComp->SetCollisionProfileName(RogueCollision::Profile::Pickup);
}

void ARoguePotionBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
}


void ARoguePotionBase::PlayPickupEffect()
{
	UGameplayStatics::PlaySoundAtLocation(this, PickupSoundEffect, GetActorLocation(), FRotator::ZeroRotator);
}
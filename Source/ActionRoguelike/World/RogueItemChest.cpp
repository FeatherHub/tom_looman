#include "RogueItemChest.h"


ARogueItemChest::ARogueItemChest()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
	BaseMeshComp->SetCollisionProfileName(TEXT("Interaction"));
	RootComponent = BaseMeshComp;

	LidMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMeshComp"));
	LidMeshComp->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	LidMeshComp->SetupAttachment(BaseMeshComp);
}

void ARogueItemChest::BeginPlay()
{
	Super::BeginPlay();

	AnimationPitchCurrent = LidMeshComp->GetRelativeRotation().Pitch;
}

void ARogueItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FRotator NewRotator = FMath::RInterpConstantTo(FRotator{AnimationPitchCurrent, 0.f, 0.f}, FRotator{AnimationPitchMax, 0.f, 0.f}, DeltaTime, AnimationPitchSpeed);
	AnimationPitchCurrent = NewRotator.Pitch;

	LidMeshComp->SetRelativeRotation(NewRotator);
	
	if (FMath::IsNearlyEqual(AnimationPitchCurrent, AnimationPitchMax))
	{
		SetActorTickEnabled(false);
		OnItemChestOpenAnimationComplete();
	}
}

void ARogueItemChest::Interact_Implementation()
{
	SetActorTickEnabled(true);
}

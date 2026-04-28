#include "RogueItemChest.h"


ARogueItemChest::ARogueItemChest()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
	RootComponent = BaseMeshComp;

	LidMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMeshComp"));
	LidMeshComp->SetupAttachment(BaseMeshComp);
}

void ARogueItemChest::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.SetTickFunctionEnable(true);
}

void ARogueItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRotator = FMath::RInterpConstantTo(FRotator{AnimationPitchCurrent, 0.f, 0.f}, FRotator{AnimationPitchMax, 0.f, 0.f}, DeltaTime, AnimationPitchSpeed);
	AnimationPitchCurrent = NewRotator.Pitch;

	LidMeshComp->SetRelativeRotation(NewRotator);
	
	if (FMath::IsNearlyEqual(AnimationPitchCurrent, AnimationPitchMax))
	{
		PrimaryActorTick.SetTickFunctionEnable(false);
	}
}

#include "RogueInteractionComponent.h"


URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URogueInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APlayerController* OwnerPC = CastChecked<APlayerController>(GetOwner());
	AActor* OwnerActor = OwnerPC->GetPawn();
	
	DrawDebugBox(OwnerActor->GetWorld(), OwnerActor->GetActorLocation(), FVector{50, 50, 50}, FColor::Cyan, false);
}


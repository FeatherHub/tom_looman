#include "RogueInteractionComponent.h"

#include "Engine/OverlapResult.h"


URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URogueInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APlayerController* PC = CastChecked<APlayerController>(GetOwner());
	FVector PlayerLocation = PC->GetPawn()->GetActorLocation();
	
	TArray<FOverlapResult> Overlaps;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(InteractionRadius);
	GetWorld()->OverlapMultiByChannel(Overlaps, PlayerLocation, FQuat::Identity,  ECC_Visibility, CollisionShape);

	const float DEBUG_BOX_EXTENT = 50.f;
	
	float BestDotResult = -1;
	AActor* BestActor = nullptr;
	
	for (FOverlapResult& Overlap : Overlaps)
	{
		FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();
		
		FVector ControllerDirection = PC->GetControlRotation().Vector();
		FVector TargetDirection = (OverlapLocation - PlayerLocation).GetSafeNormal();
		
		float DotResult = FVector::DotProduct(ControllerDirection, TargetDirection);

		if (DotResult > BestDotResult)
		{
			BestDotResult = DotResult;
			BestActor = Overlap.GetActor();
		}		
		
		DrawDebugBox(GetWorld(), OverlapLocation, FVector{DEBUG_BOX_EXTENT}, FColor::Red, false);
		FString DebugString = FString::Printf(TEXT("%f"), DotResult);
		DrawDebugString(GetWorld(), OverlapLocation, DebugString, nullptr, FColor::White, 0, true);
	}	
	
	if (BestActor)
	{
		DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector{DEBUG_BOX_EXTENT + 10.f}, FColor::Green, false);
	}
	
	DrawDebugSphere(GetWorld(), PlayerLocation, InteractionRadius, 16.f, FColor::White, false);
}


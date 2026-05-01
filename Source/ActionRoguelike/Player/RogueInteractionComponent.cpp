#include "RogueInteractionComponent.h"

#include "Core/RogueGameType.h"
#include "Core/RogueInteractionInterface.h"
#include "Engine/OverlapResult.h"


TAutoConsoleVariable<bool> CVarInteractionDebugDraw{
	TEXT("rogue.interaction.Debugdraw"), true,
	TEXT("Enable interation debug draw. (0 = Off, 1 = On)"), ECVF_Cheat
};

const float DEBUG_BOX_EXTENT = 50.f;

URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	InteractionRadius = 800.f;
	DistanceWeightScale = 2.f;
	DirectionWeightScale = 1.f;
}

void URogueInteractionComponent::Interact()
{
	if (SelectedActor)
	{
		IRogueInteractionInterface::Execute_Interact(SelectedActor);
	}
}

void URogueInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APlayerController* PC = CastChecked<APlayerController>(GetOwner());
	APawn* PlayerPawn = PC->GetPawn();
	if (!IsValid(PlayerPawn))
	{
		return;
	}

	const bool bDebugEnabled = CVarInteractionDebugDraw.GetValueOnGameThread();

	FVector ControllerDirection = PC->GetControlRotation().Vector();
	FVector EyeLocation = PC->PlayerCameraManager->GetCameraLocation();
	float MaxDistanceSqrd = InteractionRadius * InteractionRadius;

	TArray<FOverlapResult> Overlaps;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(InteractionRadius);
	GetWorld()->OverlapMultiByChannel(Overlaps, EyeLocation, FQuat::Identity, RogueCollision::Trace::Interaction, CollisionShape);

	// Weight range is [0,1]
	float HighestWeight = 0;
	AActor* BestCandidate = nullptr;

	for (FOverlapResult& Overlap : Overlaps)
	{
		FVector OverlapLocation;
		FVector OverlapExtent;
		Overlap.GetActor()->GetActorBounds(true, OverlapLocation, OverlapExtent);

		float Distance = FVector::DistSquared(PlayerPawn->GetActorLocation(), OverlapLocation);

		// normalize to [0,1]. closer distance gets the higher value
		float NormalizedDistance = 1.f - (Distance / MaxDistanceSqrd);

		FVector TargetDirection = (OverlapLocation - EyeLocation).GetSafeNormal();
		float Dot = FVector::DotProduct(ControllerDirection, TargetDirection);

		// normalize to [0,1]
		float NormalizedDot = Dot * 0.5f + 0.5f;

		float Weight = (NormalizedDot * DirectionWeightScale) + (NormalizedDistance * DistanceWeightScale);

		if (Weight > HighestWeight)
		{
			HighestWeight = Weight;
			BestCandidate = Overlap.GetActor();
		}
		
#if !UE_BUILD_SHIPPING
		if (bDebugEnabled)
		{
			DrawDebugBox(GetWorld(), OverlapLocation, FVector{DEBUG_BOX_EXTENT}, FColor::Red, false);
			
			DrawDebugString(GetWorld(), OverlapLocation, FString::Printf(TEXT("Weight: %f Dot: %f Dist: %f"), Weight, NormalizedDot, NormalizedDistance), 
				nullptr, FColor::White, 0, true);
		}
#endif
	}

	SelectedActor = BestCandidate;
	
#if !UE_BUILD_SHIPPING
	if (bDebugEnabled)
	{
		if (SelectedActor)
		{
			FVector Origin;
			FVector Extent;
			SelectedActor->GetActorBounds(true, Origin, Extent);
			DrawDebugBox(GetWorld(), Origin, FVector{DEBUG_BOX_EXTENT + 10.f}, FColor::Green, false);
		}

		DrawDebugSphere(GetWorld(), EyeLocation, InteractionRadius, 16.f, FColor::White, false);
	}
#endif
}

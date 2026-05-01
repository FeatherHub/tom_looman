#include "RogueInteractionComponent.h"

#include "Core/RogueGameType.h"
#include "Core/RogueInteractionInterface.h"
#include "Engine/OverlapResult.h"


TAutoConsoleVariable<bool> CVarInteractionDebugDraw{TEXT("rogue.interaction.Debugdraw"), false, TEXT("Enable interation debug draw. (0 = Off, 1 = On)"), ECVF_Cheat};
const float DEBUG_BOX_EXTENT = 50.f;

URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URogueInteractionComponent::Interact()
{
	// To call purely C++ interface
	// IRogueInteractionInterface* InteractionInterface = Cast<IRogueInteractionInterface>(SelectedActor);
	// if (InteractionInterface)
	// {
	// 	InteractionInterface->Interact();
	// }
	
	
	// To call BlueprintNativeEvent interface
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
	
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	
	TArray<FOverlapResult> Overlaps;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(InteractionRadius);
	GetWorld()->OverlapMultiByChannel(Overlaps, PlayerLocation, FQuat::Identity,  RogueCollision::Trace::Interaction, CollisionShape);
	
	const bool bDebugEnabled = CVarInteractionDebugDraw.GetValueOnGameThread();
	
	float HighestDotResult = -1;
	AActor* BestActor = nullptr;
	
	for (FOverlapResult& Overlap : Overlaps)
	{
		FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();
		
		FVector ControllerDirection = PC->GetControlRotation().Vector();
		FVector TargetDirection = (OverlapLocation - PlayerLocation).GetSafeNormal();
		
		float DotResult = FVector::DotProduct(ControllerDirection, TargetDirection);

		if (DotResult > HighestDotResult)
		{
			HighestDotResult = DotResult;
			BestActor = Overlap.GetActor();
		}		
		
		if (bDebugEnabled)
		{
			DrawDebugBox(GetWorld(), OverlapLocation, FVector{DEBUG_BOX_EXTENT}, FColor::Red, false);
			FString DebugString = FString::Printf(TEXT("%f"), DotResult);
			DrawDebugString(GetWorld(), OverlapLocation, DebugString, nullptr, FColor::White, 0, true);
		}
	}	
	
	SelectedActor = BestActor;
	
	if (bDebugEnabled)
	{
		if (SelectedActor)
		{
			DrawDebugBox(GetWorld(), SelectedActor->GetActorLocation(), FVector{DEBUG_BOX_EXTENT + 10.f}, FColor::Green, false);
		}
	
		DrawDebugSphere(GetWorld(), PlayerLocation, InteractionRadius, 16.f, FColor::White, false);
	}
}


#include "RogueInteractionComponent.h"

#include "Core/RogueGameType.h"
#include "Core/RogueInteractionInterface.h"
#include "Engine/OverlapResult.h"


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
	GetWorld()->OverlapMultiByChannel(Overlaps, PlayerLocation, FQuat::Identity,  COLLISION_INTERACTION, CollisionShape);
	
	const float DEBUG_BOX_EXTENT = 50.f;
	
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
		
		DrawDebugBox(GetWorld(), OverlapLocation, FVector{DEBUG_BOX_EXTENT}, FColor::Red, false);
		FString DebugString = FString::Printf(TEXT("%f"), DotResult);
		DrawDebugString(GetWorld(), OverlapLocation, DebugString, nullptr, FColor::White, 0, true);
	}	
	
	if (BestActor)
	{
		DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector{DEBUG_BOX_EXTENT + 10.f}, FColor::Green, false);
	}
	SelectedActor = BestActor;
	
	DrawDebugSphere(GetWorld(), PlayerLocation, InteractionRadius, 16.f, FColor::White, false);
}


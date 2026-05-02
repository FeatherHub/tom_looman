#include "RogueBTService_WithinRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Core/RogueDebug.h"

void URogueBTService_WithinRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	AAIController* AIController = OwnerComp.GetAIOwner();

	AActor* AIActor = AIController->GetPawn();
	check(AIActor)

	AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject(TargetActorKey.SelectedKeyName));
	if (TargetActor)
	{
		float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIActor->GetActorLocation());

		bool bIsWithinRange = DistanceTo < MaxRange;
		bool bHasLOS = AIController->LineOfSightTo(TargetActor);

		BBComp->SetValueAsBool(WithinRangeKey.SelectedKeyName, bIsWithinRange && bHasLOS);
	}

	if (CVarMinionRangedDrawDebug.GetValueOnGameThread())
	{
		FRotationTranslationMatrix CircleMatrix{
			FRotator{90.f, 0.f, 0.f},
			AIActor->GetActorLocation()
		};
		DrawDebugCircle(GetWorld(), CircleMatrix, MaxRange, 64, FColor::Black, false, Interval, 0, 1);
	}
}

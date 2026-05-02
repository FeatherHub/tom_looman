#include "RogueBTService_WithinRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void URogueBTService_WithinRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	AAIController* AIController = OwnerComp.GetAIOwner();
	
	AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject(TargetActorKey.SelectedKeyName));
	if (TargetActor)
	{
		AActor* AIActor = AIController->GetPawn();
		check(AIActor)

		float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIActor->GetActorLocation());
		
		bool bIsWithinRange = DistanceTo < MaxRange;
		bool bHasLOS = AIController->LineOfSightTo(TargetActor);

		BBComp->SetValueAsBool(WithinRangeKey.SelectedKeyName, bIsWithinRange && bHasLOS);
	}
}

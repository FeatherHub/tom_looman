#include "RogueBTTask_HealSelf.h"

#include "AIController.h"
#include "ActionSystem/RogueActionSystemComponent.h"

EBTNodeResult::Type URogueBTTask_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();

	URogueActionSystemComponent* ASC = AIPawn->GetComponentByClass<URogueActionSystemComponent>();

	ASC->ApplyHealthChange(HealAmount);

	return EBTNodeResult::Succeeded;
}

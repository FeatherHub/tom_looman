#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "RogueBTService_WithinRange.generated.h"

UCLASS()
class ACTIONROGUELIKE_API URogueBTService_WithinRange : public UBTService
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector WithinRangeKey;

	UPROPERTY(EditAnywhere)
	float MaxRange = 500.f;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};

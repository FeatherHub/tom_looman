#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "RogueBTService_CheckHealthLow.generated.h"


UCLASS()
class URogueBTService_CheckHealthLow: public UBTService
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category=AI)
	float HealthLowRatio;

	UPROPERTY(EditAnywhere, Category=AI)
	FBlackboardKeySelector IsHealthLowKey;

public:
	URogueBTService_CheckHealthLow();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};

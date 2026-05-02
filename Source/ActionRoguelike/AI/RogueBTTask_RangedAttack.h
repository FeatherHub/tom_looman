#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RogueBTTask_RangedAttack.generated.h"

class ARogueProjectileBase;

UCLASS()
class ACTIONROGUELIKE_API URogueBTTask_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category=Attack)
	FName MuzzleSocketName;
	 
	UPROPERTY(EditAnywhere, Category=Attack)
	FBlackboardKeySelector TargetActorKey;
	
	UPROPERTY(EditAnywhere, Category=Attack)
	TSubclassOf<ARogueProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, Category=Attack)
	float BulletSpreadDegree = 10.f;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

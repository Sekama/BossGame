// Richard Hill

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTTask_StopMovement.generated.h"

UCLASS(Blueprintable)
class UBTTask_StopMovement : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_StopMovement(FObjectInitializer const& ObjectInitializer);

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

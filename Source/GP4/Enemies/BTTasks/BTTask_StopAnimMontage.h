// Gabriel Ling Andersson

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_StopAnimMontage.generated.h"

UCLASS(Blueprintable)
class UBTTask_StopAnimMontage : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_StopAnimMontage(FObjectInitializer const& ObjectInitializer);

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TArray<UAnimMontage*> AnimMontage;
	
};

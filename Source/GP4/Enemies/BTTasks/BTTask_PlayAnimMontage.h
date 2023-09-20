// Richard Hill

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_PlayAnimMontage.generated.h"

UCLASS(Blueprintable)
class UBTTask_PlayAnimMontage : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_PlayAnimMontage(FObjectInitializer const& ObjectInitializer);

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<UAnimMontage*> AnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float InPlayRate = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FName StartSection = NAME_None;
};

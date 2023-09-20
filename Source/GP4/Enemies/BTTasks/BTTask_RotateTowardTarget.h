// Richard Hill

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_RotateTowardTarget.generated.h"

class ABaseEnemy;

UCLASS(Blueprintable)
class UBTTask_RotateTowardTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_RotateTowardTarget(FObjectInitializer const& ObjectInitializer);

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	// virtual uint16 GetInstanceMemorySize() const override;

	UPROPERTY()
	APawn* PlayerPawn;
	UPROPERTY()
	ABaseEnemy* AICharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float AcceptanceRotation = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float InterpSpeed = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float MaxTime = 4;

	float Timer = 0;
};

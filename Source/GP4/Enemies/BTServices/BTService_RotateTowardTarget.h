// Richard Hill

#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_RotateTowardTarget.generated.h"

class APlayerCharacter;
UCLASS(Blueprintable)
class UBTService_RotateTowardTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_RotateTowardTarget();

private:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY()
	AAIController* AIController;
	UPROPERTY()
	UBlackboardComponent* BBComponent;
	UPROPERTY()
	APawn* AIPawn;
	UPROPERTY()
	APlayerCharacter* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float DistanceMultiplier = 0.01;

	float MaxDeltaFrames = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float InterpSpeed = 10;

	FRotator SetTargetRotation();
};

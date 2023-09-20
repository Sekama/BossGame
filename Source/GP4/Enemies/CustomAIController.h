// Richard Hill

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CustomAIController.generated.h"

class UAISenseConfig_Hearing;
class UAISenseConfig_Sight;
class UBehaviorTreeComponent;
class UBehaviorTree;
class UBlackboardComponent;
class UAIPerceptionComponent;

UCLASS()
class ACustomAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACustomAIController();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AI)
	UBehaviorTree* BehaviorTree;
	
	UFUNCTION()
	UBlackboardComponent* GetBlackboard();
	void SetBehaviorTree(UBehaviorTree* BehaveTree);

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI, meta=(AllowPrivateAccess = true))
	UBehaviorTreeComponent* BehaviorTreeComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI, meta=(AllowPrivateAccess = true))
	UBlackboardComponent* BlackboardComponent;
};

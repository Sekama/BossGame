// Richard Hill


#include "CustomAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ACustomAIController::ACustomAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void ACustomAIController::SetBehaviorTree(UBehaviorTree* BehaveTree)
{
	if (IsValid(BehaveTree))
	{
		RunBehaviorTree(BehaveTree);
		BehaviorTreeComponent->StartTree(*BehaveTree);
	}
}

UBlackboardComponent* ACustomAIController::GetBlackboard()
{
	return BlackboardComponent;
}

void ACustomAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACustomAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(Blackboard) && IsValid(BehaviorTree))
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}


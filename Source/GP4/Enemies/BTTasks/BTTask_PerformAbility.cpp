﻿// Richard Hill


#include "BTTask_PerformAbility.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GP4/Enemies/BaseEnemy.h"

UBTTask_PerformAbility::UBTTask_PerformAbility(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Perform Ability");
}

EBTNodeResult::Type UBTTask_PerformAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get AI Controller & Pawn
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BBComponent = AIController->GetBlackboardComponent();
	ABaseEnemy* AICharacter = Cast<ABaseEnemy>(AIController->GetCharacter());

	if (IsValid(AICharacter))
	{
		BBComponent->SetValueAsFloat(BlackboardKey.SelectedKeyName, AICharacter->GetAttackTime());
		AICharacter->PerformAttack();
	}

	// Signal the behavior tree component that the task is finished with success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

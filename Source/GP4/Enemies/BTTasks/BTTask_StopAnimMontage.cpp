// Gabriel Ling Andersson


#include "BTTask_StopAnimMontage.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GP4/Enemies/BaseEnemy.h"

UBTTask_StopAnimMontage::UBTTask_StopAnimMontage(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Stop Animation Montage");

	// Accept only floats
	BlackboardKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_StopAnimMontage, BlackboardKey));
}

EBTNodeResult::Type UBTTask_StopAnimMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get AI Controller & Pawn
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BBComponent = AIController->GetBlackboardComponent();
	ABaseEnemy* AICharacter = Cast<ABaseEnemy>(AIController->GetCharacter());

	
	AICharacter->StopAnimMontage(AICharacter->GetCurrentMontage());

	

	// Signal the behavior tree component that the task is finished with success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

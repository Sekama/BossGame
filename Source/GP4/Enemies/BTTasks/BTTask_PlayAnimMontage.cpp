// Richard Hill


#include "BTTask_PlayAnimMontage.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GP4/Enemies/BaseEnemy.h"

UBTTask_PlayAnimMontage::UBTTask_PlayAnimMontage(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Play Animation Montage");

	// Accept only floats
	BlackboardKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_PlayAnimMontage, BlackboardKey));
}

EBTNodeResult::Type UBTTask_PlayAnimMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get AI Controller & Pawn
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BBComponent = AIController->GetBlackboardComponent();
	ABaseEnemy* AICharacter = Cast<ABaseEnemy>(AIController->GetCharacter());

	int const Random = FMath::RandRange(0, AnimMontage.Num() - 1);

	if (AnimMontage[Random])
	{
		float const PlayTime = AICharacter->PlayAnimationMontage(AnimMontage[Random], InPlayRate, StartSection);
		BBComponent->SetValueAsFloat(BlackboardKey.SelectedKeyName, PlayTime);
	}

	// Signal the behavior tree component that the task is finished with success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

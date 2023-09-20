// Richard Hill


#include "BTTask_RotateTowardTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GP4/Enemies/BaseEnemy.h"


UBTTask_RotateTowardTarget::UBTTask_RotateTowardTarget(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Rotate Toward Target");

	bNotifyTick = true;
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_RotateTowardTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bCreateNodeInstance = true;
	
	// Get AI Controller & Pawn
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BBComponent = AIController->GetBlackboardComponent();
	AICharacter = Cast<ABaseEnemy>(AIController->GetCharacter());
	Timer = 0;

	// Get Player Location
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	return EBTNodeResult::InProgress;
}

void UBTTask_RotateTowardTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	Timer += DeltaSeconds;
	
	if (PlayerPawn)
	{
		FVector const PlayerLocation = PlayerPawn->GetActorLocation();

		FRotator const TargetRotation = UKismetMathLibrary::FindLookAtRotation(AICharacter->GetActorLocation(), PlayerLocation);

		// Only rotate Yaw
		FRotator const NewRot = FRotator(AICharacter->GetActorRotation().Pitch, TargetRotation.Yaw, AICharacter->GetActorRotation().Roll);
		
		AICharacter->SetActorRotation(FMath::RInterpTo(AICharacter->GetActorRotation(), NewRot, DeltaSeconds, InterpSpeed));

		float const YawDiff = AICharacter->GetActorRotation().Yaw - TargetRotation.Yaw;

		if (YawDiff <= AcceptanceRotation && YawDiff >= -AcceptanceRotation)
		{
			// Signal the behavior tree component that the task is finished with success
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		
		if (Timer >= MaxTime)
		{
			// Signal the behavior tree component that the task is finished with success
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}

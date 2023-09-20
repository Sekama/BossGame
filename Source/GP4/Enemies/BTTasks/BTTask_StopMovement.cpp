// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_StopMovement.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GP4/Enemies/CustomAIController.h"


UBTTask_StopMovement::UBTTask_StopMovement(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Stop Movement");
}

EBTNodeResult::Type UBTTask_StopMovement::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get AI Controller
	ACustomAIController* const AIController = Cast<ACustomAIController>(OwnerComp.GetAIOwner());
	FVector const OwnerLocation = AIController->GetPawn()->GetActorLocation();
	
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIController, OwnerLocation);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

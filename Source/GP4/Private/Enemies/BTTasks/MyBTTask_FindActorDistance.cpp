// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemies/BTTasks/MyBTTask_FindActorDistance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "Math/Vector.h"

UBTTask_FindActorDistance::UBTTask_FindActorDistance(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Actor Distance");
}


EBTNodeResult::Type UBTTask_FindActorDistance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	// Get AI Controller
	AAIController* AIController = OwnerComp.GetAIOwner();
	const APawn* AIPawn {AIController->GetPawn()};

	// Get Player Location
	APawn* const PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector const PlayerLocation = PlayerPawn->GetActorLocation();
	
	// Set ActorDistance
	AIController->GetBlackboardComponent()->SetValueAsFloat(BlackboardKey.SelectedKeyName,
		FVector::Distance(PlayerPawn->GetActorLocation(), AIPawn->GetActorLocation()));
	

	// Signal the behavior tree component that the task is finished with success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

FString UBTTask_FindActorDistance::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
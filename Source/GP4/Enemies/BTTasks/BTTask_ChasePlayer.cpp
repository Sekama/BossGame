﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChasePlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GP4/Enemies/CustomAIController.h"


UBTTask_ChasePlayer::UBTTask_ChasePlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get AI Controller
	ACustomAIController* const AIController = Cast<ACustomAIController>(OwnerComp.GetAIOwner());
	FVector const PlayerLocation = AIController->GetBlackboard()->GetValueAsVector(TEXT("TargetLocation"));
	
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIController, PlayerLocation);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_ChasePlayer::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}

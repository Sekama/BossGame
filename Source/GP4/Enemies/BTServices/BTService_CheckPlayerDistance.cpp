// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckPlayerDistance.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_CheckPlayerDistance::UBTService_CheckPlayerDistance()
{
	
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Check Player Distance");
}

void UBTService_CheckPlayerDistance::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	// Get Player Location
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void UBTService_CheckPlayerDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (!PlayerPawn)
	{
		PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	}
	
	float const DistanceToPlayer = OwnerComp.GetAIOwner()->GetPawn()->GetDistanceTo(PlayerPawn);
	
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), DistanceToPlayer);
}

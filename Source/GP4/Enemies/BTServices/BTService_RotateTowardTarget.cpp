// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_RotateTowardTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GP4/Player/PlayerCharacter.h"

UBTService_RotateTowardTarget::UBTService_RotateTowardTarget()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Rotate Toward Target");
}

void UBTService_RotateTowardTarget::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{	
	// Get AI Controller & Pawn
	AIController = OwnerComp.GetAIOwner();
	BBComponent = AIController->GetBlackboardComponent();
	AIPawn = AIController->GetPawn();
	
	// Get Player
	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
}

void UBTService_RotateTowardTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (!AIPawn) return;
	if (!Player) return;

	if (Player)
	{
		FRotator const NewRot = SetTargetRotation();
		
		AIPawn->SetActorRotation(FMath::RInterpTo(AIPawn->GetActorRotation(), NewRot, DeltaSeconds, InterpSpeed));
	}
	
}

FRotator UBTService_RotateTowardTarget::SetTargetRotation()
{
	FVector const PlayerLocation = Player->GetActorLocation();
	FRotator LookAtRotation = FRotator::ZeroRotator;	
	FRotator TargetRotation = FRotator::ZeroRotator;

	if (DistanceMultiplier > 0)
	{
		float const DistanceToPlayer = AIPawn->GetDistanceTo(Player);
		float const InDeltaFrames = FMath::Clamp(DistanceToPlayer * DistanceMultiplier, 0, MaxDeltaFrames); 
		LookAtRotation = UKismetMathLibrary::FindLookAtRotation(AIPawn->GetActorLocation(), Player->GetPlayerFuturePos(InDeltaFrames));
		TargetRotation = FRotator(AIPawn->GetActorRotation().Pitch, LookAtRotation.Yaw, AIPawn->GetActorRotation().Roll);
	}
	else
	{
		LookAtRotation = UKismetMathLibrary::FindLookAtRotation(AIPawn->GetActorLocation(), PlayerLocation);
		TargetRotation = FRotator(AIPawn->GetActorRotation().Pitch, LookAtRotation.Yaw, AIPawn->GetActorRotation().Roll);
	}

	return TargetRotation;
}

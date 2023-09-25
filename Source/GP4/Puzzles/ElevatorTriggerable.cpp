// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorTriggerable.h"

AElevatorTriggerable::AElevatorTriggerable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ElevatorRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Elevator Root"));
	SetRootComponent(ElevatorRoot);

	ElevatorPlatform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Elevator Platform"));
	ElevatorPlatform->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	EndLocation = CreateDefaultSubobject<USceneComponent>(TEXT("End Location"));
	EndLocation->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AElevatorTriggerable::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = ElevatorPlatform->GetRelativeLocation();
	SetTargetLocation(EndLocation->GetRelativeLocation());
}

void AElevatorTriggerable::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(!bIsTriggered) return;

	Timer += DeltaSeconds * ElevatorSpeed;
	ElevatorPlatform->SetRelativeLocation(FMath::Lerp(StartLocation, TargetLocation, Timer));

	if (Timer >= 1)
	{
		OnTriggerDone();
		bIsTriggered = false;
	}
}

/**
 * @brief Sets the target location of the elevator.
 * @param Location new target location.
 */
void AElevatorTriggerable::SetTargetLocation(FVector Location)
{
	TargetLocation = Location;
}

/**
 * @brief Reverses the direction of the elevator path.
 */
void AElevatorTriggerable::ReverseDirection()
{
	const auto Temp = TargetLocation;
	SetTargetLocation(StartLocation);
	StartLocation = Temp;
}
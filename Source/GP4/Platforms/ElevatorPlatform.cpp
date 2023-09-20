// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorPlatform.h"

AElevatorPlatform::AElevatorPlatform()
{
	End = CreateDefaultSubobject<USceneComponent>(TEXT("End Position"));
	End->SetupAttachment(Root);
}

void AElevatorPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartPos = GetActorLocation();
	EndPos = End->GetRelativeLocation() + GetActorLocation();
	Move(0);
	if (!ManualTrigger)
		bActivated = true;	
}

void AElevatorPlatform::OnBeginOverlap(AActor* OtherActor)
{
	if (ManualTrigger && OtherActor == PlayerRef)
	{
		bIsTriggered = true;
		bActivated = true;
	}
}

void AElevatorPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ManualTrigger)
	{
		if (bIsTriggered)
		{
			if (ManualWaitTime)
			{
				if (StopTime < WaitTime)
					Wait(DeltaTime);
				else
					Travel(DeltaTime);
			}
			else
			{
				Travel(DeltaTime);
			}
		}
	}
	else
	{
		if (StopTime < WaitTime)
			Wait(DeltaTime);
		else
			Travel(DeltaTime);
	}
}

void AElevatorPlatform::Wait(float DeltaTime)
{
	StopTime += DeltaTime;
}

void AElevatorPlatform::Move(float t)
{
	FVector TravelDistance = FMath::Lerp(StartPos,EndPos, t);
	SetActorLocation(TravelDistance);
}

void AElevatorPlatform::Travel(float DeltaTime)
{
	CurrentTime += Direction * DeltaTime;
	

	if (CurrentTime >= TravelTime)
	{
		Direction = -1;
		StopTime = 0;
		bIsTriggered = false;
		OnDestinationReached();
	}
	else if (CurrentTime <= 0)
	{
		Direction = 1;
		StopTime = 0;
		bIsTriggered = false;
		OnDestinationReached();
	}
	float Distance = CurrentTime / TravelTime;;
	Move(Distance);
}





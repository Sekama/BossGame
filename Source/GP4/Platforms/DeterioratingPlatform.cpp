// Fill out your copyright notice in the Description page of Project Settings.


#include "DeterioratingPlatform.h"


ADeterioratingPlatform::ADeterioratingPlatform()
{

}

void ADeterioratingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartPos = Mesh->GetRelativeLocation();
	ResetPos = GetActorLocation();
	ShakeFrequency = 1.0f / ShakeFrequency;
}

void ADeterioratingPlatform::TriggerDeteriorating()
{
	Status = true;
	bActivated = true;
}

void ADeterioratingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Falling)
	{
		FallDistance += FallSpeed * DeltaTime;
		FVector NewPos = GetActorLocation() + (FVector::DownVector * FallSpeed) * DeltaTime;
		SetActorLocation(NewPos);
		if (FallDistance > DespawnDistance)
		{
			SetActorHiddenInGame(true);
			Mesh->SetCollisionProfileName("NoCollision");
			Falling = false;
		}
	}
	else if (Status)
	{
		ShakeTimer += DeltaTime;
		FrequencyTimer += DeltaTime;
		if (FrequencyTimer >= ShakeFrequency)
		{
			Shake();
			FrequencyTimer -= ShakeFrequency;
		}
		if (ShakeTimer > DeterioratingTime)
		{
			Falling = true;
			Status = false;
			Mesh->SetRelativeLocation(StartPos);
		}
	}
}

void ADeterioratingPlatform::OnBeginOverlap(AActor* OtherActor)
{	
	if (PlayerSpecific && OtherActor != PlayerRef)
		return;
	Status = true;
	bActivated = true;
	
}

void ADeterioratingPlatform::Shake()
{
	
	FVector ShakeVect = FVector(FMath::RandRange(-1, 1), FMath::RandRange(-1, 1), 0);
	ShakeVect *= ShakeVect.GetSafeNormal() * ShakeStrength;
	FVector Diff = StartPos - (Mesh->GetRelativeLocation() + ShakeVect);
	if (Diff.Size() > ShakeStrength)
	{
		ShakeVect = Diff.GetSafeNormal() * ShakeStrength;
	}
	Mesh->AddLocalOffset(ShakeVect);
}





// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlatform.h"
#include "ElevatorPlatform.generated.h"

class UBoxComponent;

UCLASS()
class AElevatorPlatform : public ABasePlatform
{
	GENERATED_BODY()

public:
	AElevatorPlatform();

	UPROPERTY(EditAnywhere)
	float TravelTime = 0;
	UPROPERTY(EditAnywhere)
	bool ManualTrigger = false;
	UPROPERTY(EditAnywhere)
	bool ManualWaitTime = false;
	UPROPERTY(EditAnywhere)
	float WaitTime = 0;
	UPROPERTY(EditAnywhere)
	USceneComponent* End;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDestinationReached();
	

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnBeginOverlap(AActor* OtherActor) override;
	bool bIsTriggered = false;
	float StopTime = 0;
	float Direction = 1;
	float CurrentTime = 0;
	FVector StartPos;
	FVector EndPos;

	void Wait(float DeltaTime);
	void Travel(float DeltaTime);
	void Move(float t);
};

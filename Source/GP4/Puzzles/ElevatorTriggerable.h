// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Triggerable.h"
#include "ElevatorTriggerable.generated.h"

/**
 * 
 */
UCLASS()
class GP4_API AElevatorTriggerable : public ATriggerable
{
	GENERATED_BODY()

public:
	AElevatorTriggerable();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


	UFUNCTION(BlueprintImplementableEvent)
	void OnTriggerDone();

	UFUNCTION(BlueprintCallable)
	virtual void SetTargetLocation(FVector Location);
	UFUNCTION(BlueprintCallable)
	virtual void ReverseDirection();

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ElevatorPlatform;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* ElevatorRoot;

	UPROPERTY(EditAnywhere)
	USceneComponent* EndLocation;
	FVector StartLocation;

	FVector TargetLocation;

	UPROPERTY(EditAnywhere)
	float ElevatorSpeed = 1.0f;

	float Timer = 0;
};

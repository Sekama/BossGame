// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasePlatform.h"
#include "DeterioratingPlatform.generated.h"

class UBoxComponent;

UCLASS()
class ADeterioratingPlatform : public ABasePlatform
{
	GENERATED_BODY()

public:
	ADeterioratingPlatform();

	UPROPERTY(EditAnywhere)
	float DeterioratingTime = 5;
	UPROPERTY(EditAnywhere)
	float ShakeStrength = 5;
	UPROPERTY(EditAnywhere)
	float ShakeFrequency = 10;
	UPROPERTY(EditAnywhere)
	float FallSpeed = 10;
	UPROPERTY(EditAnywhere)
	float DespawnDistance = 350;

	UFUNCTION(BlueprintCallable)
	void TriggerDeteriorating();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	bool Status = false;
	bool Falling = false;
	float ShakeTimer = 0;
	float FrequencyTimer = 0;
	float FallDistance = 0;
	FVector ResetPos;
	FVector StartPos;
	void Shake();
	virtual void OnBeginOverlap(AActor* OtherActor) override;
};

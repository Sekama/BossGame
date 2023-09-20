// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trigger.h"
#include "Components/BoxComponent.h"
#include "PressurePlate.generated.h"

/**
 * 
 */
UCLASS()
class GP4_API APressurePlate : public ATrigger
{
	GENERATED_BODY()

public:
	APressurePlate();
	virtual void Trigger() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* Root;
};

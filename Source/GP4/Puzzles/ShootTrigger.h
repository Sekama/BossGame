// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trigger.h"
#include "ShootTrigger.generated.h"

/**
 * 
 */
UCLASS()
class GP4_API AShootTrigger : public ATrigger
{
	GENERATED_BODY()

	AShootTrigger();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* Root;
};

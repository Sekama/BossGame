// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Arrangement.generated.h"

/**
 * 
 */
UCLASS()
class GP4_API UArrangement : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Volume1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Volume2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Volume3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Volume4;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Volume5;
	
	 
};

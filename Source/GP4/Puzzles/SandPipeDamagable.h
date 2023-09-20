// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damagable.h"
#include "Triggerable.h"
#include "SandPipeDamagable.generated.h"

/**
 * 
 */
UCLASS()
class GP4_API ASandPipeDamagable : public ADamagable
{
	GENERATED_BODY()

protected:
	virtual void Destroy() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ATriggerable* Triggerable;
};

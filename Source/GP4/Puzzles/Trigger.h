// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GP4/Puzzles/Triggerable.h"
#include "GameFramework/Actor.h"
#include "Trigger.generated.h"


UCLASS()
class GP4_API ATrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrigger();

	UFUNCTION(BlueprintCallable)
	virtual void Trigger();

protected:
	/* Should trigger be able to be triggered endlessly? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEndlessTrigger = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsTriggered = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATriggerable* Triggerable;
};

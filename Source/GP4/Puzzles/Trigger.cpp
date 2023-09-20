// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger.h"

// Sets default values
ATrigger::ATrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

/**
 * @brief Triggers the triggerable object.
 */
void ATrigger::Trigger()
{
	if(!IsValid(Triggerable))
	{
		UE_LOG(LogTemp, Error, TEXT("Triggerable is not valid"));
		return;
	}

	if(bIsTriggered && !bEndlessTrigger) return;

	bIsTriggered = true;
	Triggerable->Trigger();
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "SandPipeDamagable.h"

void ASandPipeDamagable::Destroy()
{
	Super::Destroy();

	if (!IsValid(Triggerable))
	{
		UE_LOG(LogTemp, Warning, TEXT("SandPipeDamagable: Triggerable is not valid!"));
		return;
	}

	Triggerable->Trigger();
}
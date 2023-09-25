// Copyright Epic Games, Inc. All Rights Reserved.


#include "GP4GameModeBase.h"


void AGP4GameModeBase::SetBossActive(AActor* Boss, bool Active)
{
	if (!IsValid(Boss)) return;

	Cast<ACharacter>(Boss)->GetCharacterMovement()->GravityScale = Active ? 1.f : 0.f;
}

void AGP4GameModeBase::SetBossHidden(AActor* Boss, bool Hidden)
{
	if (!IsValid(Boss)) return;

	Boss->SetActorEnableCollision(!Hidden);
	Boss->SetActorHiddenInGame(Hidden);
}

void AGP4GameModeBase::SetBossEnableCollision(AActor* Boss, bool Enabled)
{
	if (!IsValid(Boss)) return;

	Boss->SetActorEnableCollision(Enabled);
}
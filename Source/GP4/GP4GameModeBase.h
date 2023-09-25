// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameModeBase.h"
#include "GP4GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GP4_API AGP4GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetBossActive(AActor* Boss, bool Active);

	UFUNCTION(BlueprintCallable)
	void SetBossHidden(AActor* Boss, bool Hidden);

	UFUNCTION(BlueprintCallable)
	void SetBossEnableCollision(AActor* Boss, bool Enable);
};

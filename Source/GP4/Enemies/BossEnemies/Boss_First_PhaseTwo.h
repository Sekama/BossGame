// Richard Hill

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GP4/Enemies/BaseEnemy.h"
#include "Components/ActorComponent.h"
#include "Boss_First_PhaseTwo.generated.h"

class APlayerCharacter;
class UBaseAbilityComponent;
class UAbility_SunBeams;

UCLASS()
class ABoss_First_PhaseTwo : public ABaseEnemy
{
	GENERATED_BODY()

public:
	ABoss_First_PhaseTwo();

	virtual void PerformAttack() override;
	
	UPROPERTY(EditAnywhere, Category = AbilityComponents)
	UAbility_SunBeams* SunbeamComponent;
	
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	

	
};
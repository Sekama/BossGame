// Richard Hill

#pragma once

#include "CoreMinimal.h"
#include "BaseAbilityComponent.h"
#include "Components/ActorComponent.h"
#include "Ability_SunBeams.generated.h"


class APlayerCharacter;
class ABaseEnemy;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UAbility_SunBeams : public UBaseAbilityComponent
{
	GENERATED_BODY()

public:
	UAbility_SunBeams();

	virtual void PerformAbility() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ASunbeam> SunBeamClass;

	UPROPERTY(EditAnywhere)
	float SpawnInterval = 1;
	UPROPERTY(EditAnywhere)
	float Cooldown = 15;
	UPROPERTY(EditAnywhere)
	float MaxRandomRangeFromPlayer = 1000;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void CheckAttackTime(float DeltaTime);
	void CheckCooldown(float DeltaTime);
	void SpawnSunbeam() const;

	float AttackTimer = 0;
	float CooldownTimer = 0;
	bool bOnCooldown = true;
	bool bIsActive = false;
	FTimerHandle SpawnSunbeamTimerHandle;
};

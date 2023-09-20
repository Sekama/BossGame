// Richard Hill

#pragma once

#include "CoreMinimal.h"
#include "BaseAbilityComponent.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "Ability_Stomp.generated.h"


class APlayerCharacter;
class ABaseEnemy;
class UBoxComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UAbility_Stomp : public UBaseAbilityComponent
{
	GENERATED_BODY()

public:
	UAbility_Stomp();

	virtual void PerformAbility() override;

	bool stomp_Anim = false;
	
	UPROPERTY()
	UStaticMeshComponent* AttackVisual;
	UPROPERTY()
	UBoxComponent* CollisionBox;

	UPROPERTY()
	USphereComponent* StompCollider;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void CheckAttackTime(float DeltaTime);
	
	float AttackTimer;
	bool bAttackActive = false;
};

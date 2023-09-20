// Richard Hill

#pragma once

#include "CoreMinimal.h"
#include "BaseAbilityComponent.h"
#include "Components/ActorComponent.h"
#include "Ability_LaserRay.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UAbility_LaserRay : public UBaseAbilityComponent
{
	GENERATED_BODY()

public:
	UAbility_LaserRay();

	virtual void PerformAbility() override;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RotateTowardPlayer() const;
	void CheckAttackTime(float DeltaTime);
	
	UPROPERTY()
	UStaticMeshComponent* LaserMesh;

	bool bRotateTowardPlayer = false;
	bool bAttackIsActive = false;
	float AttackTimer;
};

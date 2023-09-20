// Richard Hill

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseAbilityComponent.generated.h"


class APlayerCharacter;
class ABaseEnemy;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType)
class UBaseAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBaseAbilityComponent();

	virtual void PerformAbility();

	UPROPERTY(EditAnywhere)
	float AttackTime = 2;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	ABaseEnemy* EnemyOwner;
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;
};

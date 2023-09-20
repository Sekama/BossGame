// Richard Hill

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GP4/Enemies/BaseEnemy.h"
#include "Components/ActorComponent.h"
#include "Boss_First.generated.h"

class APlayerCharacter;
class UBaseAbilityComponent;
class UAbility_SunBeams;
class UAbility_Stomp;
class USphereComponent;

UCLASS()
class ABoss_First : public ABaseEnemy
{
	GENERATED_BODY()

public:
	ABoss_First();

	virtual void PerformAttack() override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool pInRange = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool stomp_Anim = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int attackCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int bossHealth = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FootCollisionRadius = 50.f;

	UPROPERTY(EditAnywhere, Category = AbilityComponents)
	UAbility_Stomp* StompComponent;

	UPROPERTY(EditAnywhere, Category = AbilityComponents)
	UAbility_SunBeams* SunbeamComponent;
	
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class UBoxComponent * AtColBox;
	

	UFUNCTION(BlueprintCallable)
	void ActivateCollider();
	
};
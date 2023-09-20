// Richard Hill

#pragma once

#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTakeDamageDelegate, float, Damage, bool, bIsCrit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGainHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS(meta=(BlueprintSpawnableComponent))
class UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float CurrentHealth = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Health")
	float ImmunityTime = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Health")
	bool bIsPlayer = false;
	
	void TakeDamageInternal(float IncomingHealth);
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float IncomingHealth, bool IsCritHit);

	UPROPERTY(BlueprintAssignable, Category="Health")
	FOnTakeDamageDelegate OnHit;

	UPROPERTY(BlueprintAssignable, Category="Health")
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable, Category="Health")
	FOnGainHealth OnGainHealth;
	
	UFUNCTION(BlueprintCallable)
	void GainHealth(int IncomingHealth);

	UFUNCTION()
	bool GetIsImmune() const;

	UFUNCTION(BlueprintCallable)
	void Death();

	UFUNCTION(BlueprintCallable)
	void DashImmunity(bool EnableImmunity);
	
	UFUNCTION()
	bool GetIsDead();
	void SetIsDead(bool InBool);
	

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	AActor* Owner;

	UPROPERTY()
	float ImmunityTimer;
	UPROPERTY(BlueprintReadOnly)
	bool bIsImmune;
	UPROPERTY(BlueprintReadOnly)
	bool bIsDead;

	UFUNCTION()
	void HandleImmunityTimer(float DeltaTime);
};

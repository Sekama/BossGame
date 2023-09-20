// Richard Hill

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

class ACustomAIController;
class UCapsuleComponent;
class UHealthComponent;
class UBehaviorTree;
class UStatsComponent;

// UCLASS(HideCategories=(Input, Collision, Rendering, HLOD, WorldPartition, DataLayers, Tags, Replication, Cooking))
UCLASS()
class ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseEnemy();
	
	///// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI)
	UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere)
	UAnimMontage* HitMontage;
	UPROPERTY(EditAnywhere)
	UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName EnemyName = TEXT("Enemy");

	UPROPERTY(EditAnywhere)
	float AttackTime = 2;
	UPROPERTY(EditAnywhere)
	float DeathMaterialFadeInterpSpeed = 0.5f;
	UPROPERTY(EditAnywhere)
	float RespawnTime = 30;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector SpawnLocation;
	
	float GetAttackTime();
	void SetDeathMaterialFade(float DeltaTime);
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;

	UFUNCTION(BlueprintCallable, Category = Combat)
	virtual void PerformAttack();

	UFUNCTION()
	void OnHit(float Damage, bool IsCrit);
	void TriggerDeath();
	void StartDeathMaterialFade();
	void AggroTarget(bool HasAggro);

	UFUNCTION()
	void DisableEnemy();

	UFUNCTION(BlueprintCallable)
	float PlayAnimationMontage(UAnimMontage* Montage, float InPlayRate=1.f, FName StartSectionName=NAME_None, float StartMontageAt=0.f);
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;
	void SpawnEnemy();
	
	bool bHasAggro = false;
	bool bPlayDeathMaterialFade = false;
	bool bPlayReviveMaterialFade = false;
	UPROPERTY()
	ACustomAIController* AIController;
};

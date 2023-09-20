// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Damagable.generated.h"

UCLASS()
class GP4_API ADamagable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamagable();

	UFUNCTION(BlueprintCallable)
	virtual void Damage();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDamage();
	UFUNCTION(BlueprintImplementableEvent)
	void OnDestroy();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Health = 1;
	bool bIsDestroyed = false;

	virtual void Destroy();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* Root;
};

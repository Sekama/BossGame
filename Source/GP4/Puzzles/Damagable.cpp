// Fill out your copyright notice in the Description page of Project Settings.


#include "Damagable.h"

// Sets default values
ADamagable::ADamagable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

/**
 * @brief Damage the object.
 */
void ADamagable::Damage()
{
	if(bIsDestroyed) return;

	Health -= 1;
	OnDamage();
	if(Health <= 0)
	{
		Destroy();
	}
}

/**
 * @brief Logic for when object is destroyed.
 */
void ADamagable::Destroy()
{
	bIsDestroyed = true;
	OnDestroy();
}

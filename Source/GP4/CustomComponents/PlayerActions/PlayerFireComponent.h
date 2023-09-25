// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GP4/Player/PlayerCharacter.h"
#include "PlayerFireComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFire);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GP4_API UPlayerFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerFireComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Fire();
	void Reload();
	void StartReload();
	void SetAimMode(bool Enable);
	FRotator GetAimRotation();

	// Delegates
	UPROPERTY(BlueprintAssignable)
	FOnReloadStart OnReloadStart;
	UPROPERTY(BlueprintAssignable)
	FOnReloadEnd OnReloadEnd;
	UPROPERTY(BlueprintAssignable)
	FOnFire OnFire;

	float OriginalMovementSpeed;

	/* Multiplier for movement speed when reloading. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attacking | Reload")
	float ReloadMovementSpeedMultiplier = 0.5f;
	/* Time it takes to reload. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attacking | Reload")
	float ReloadTime = 3.f;
	/* Current duration left until reload. */
	UPROPERTY(BlueprintReadOnly, Category = "Attacking | Reload")
	float ReloadTimer = -1.f;
	
	float OriginalCameraDistance;
	UPROPERTY(BlueprintReadOnly)
	bool bIsAiming = false;

	UFUNCTION(BlueprintCallable)
	bool IsReloading() const { return ReloadTimer >= 0.f; }
	UFUNCTION(BlueprintCallable)
	bool CanFire() const { return !(IsReloading() || !bHasAmmo); }

	/* Speed of the fired projectile. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attacking | Projectile")
	float ProjectileSpeed = 1000.f;
	/* Whether player currently has ammo. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attacking | Projectile")
	bool bHasAmmo = true;
	/* Blueprint of the projectile. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attacking | Projectile")
	TSubclassOf<class APlayerProjectile> ProjectileClass;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SpawnProjectile();

	UPROPERTY()
	APlayerCharacter* Player;
	UPROPERTY()
	UPlayerCameraComponent* Camera;
};

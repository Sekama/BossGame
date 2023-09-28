// Fill out your copyright notice in the Description page of Project Settings.

#define D(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT(x)));}
#include "PlayerFireComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GP4/Player/PlayerCharacter.h"
#include "GP4/Player/PlayerProjectile.h"
#include "GP4/CustomComponents/Camera/PlayerCameraComponent.h"

// Sets default values for this component's properties
UPlayerFireComponent::UPlayerFireComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPlayerFireComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerCharacter>(GetOwner());
	Camera = Player->CustomCameraComponent;

	Camera->SetAimMode(false);
}


// Called every frame
void UPlayerFireComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (ReloadTimer >= 0)
	{

		ReloadTimer -= DeltaTime;
		if(ReloadTimer <= 0.f) Reload();
	}
}

FRotator UPlayerFireComponent::GetAimRotation()
{
	auto Forward = Camera->GetCamera()->GetForwardVector();
	Forward = FVector(Forward.X, Forward.Y, 0).GetSafeNormal();
	return Forward.Rotation();
}

/**
 * @brief Fires the weapon if possible. If not starts reloading instead.
 */
void UPlayerFireComponent::Fire()
{
	if(!CanFire())
	{
		//StartReload();
		return;
	}

	if(!bIsAiming) return;

	bHasAmmo = false;
	SpawnProjectile();
	StartReload();
}

/**
 * @brief Reloads the weapon.
 */
void UPlayerFireComponent::Reload()
{
	bHasAmmo = true;
	OnReloadEnd.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("Reloaded"));
	Player->MovementSpeed = OriginalMovementSpeed;
}

/**
 * @brief Starts reloading.
 */
void UPlayerFireComponent::StartReload()
{
	if(IsReloading()) return;

	OnReloadStart.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("Start Reload"));
	// Play reload animation
	OriginalMovementSpeed = Player->MovementSpeed;
	Player->MovementSpeed = OriginalMovementSpeed * ReloadMovementSpeedMultiplier;
	ReloadTimer = ReloadTime;
}

/**
 * @brief 
 * @param Enable 
 */
void UPlayerFireComponent::SetAimMode(bool Enable)
{
	if (bIsAiming == Enable) return;

	bIsAiming = Enable;

	Camera->SetAimMode(Enable);
}

/**
 * @brief Spawns and fires the projectile towards the reticle.
 */
void UPlayerFireComponent::SpawnProjectile()
{
	if(!IsValid(ProjectileClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile class is not valid"));
		return;
	}

	// Get direction towards the reticle by tracing a line from the camera
	auto CameraForward = Camera->GetCamera()->GetForwardVector();
	auto CameraPos = Camera->GetCamera()->GetComponentLocation();

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, CameraPos, CameraPos + CameraForward * 10000, ECC_Visibility);

	const FVector SpawnLocation = Player->ProjectileSpawn->GetComponentLocation();
	auto EndLocation = CameraPos + CameraForward * 10000;

	if(IsValid(Hit.GetActor()))
	{
		EndLocation = Hit.ImpactPoint;
	}

	auto VectorToHit = EndLocation - SpawnLocation;
	VectorToHit.Normalize();
	const FRotator SpawnRotation = VectorToHit.Rotation();

	// Spawn the projectile
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetOwner()->GetInstigator();

	APlayerProjectile* Projectile = GetWorld()->SpawnActor<APlayerProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	if(IsValid(Projectile))
	{
		Projectile->Fire(ProjectileSpeed);
		OnFire.Broadcast();
	}
}

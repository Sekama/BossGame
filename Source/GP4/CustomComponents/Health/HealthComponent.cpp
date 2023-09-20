// Richard Hill


#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	ImmunityTimer = ImmunityTime;
	
	CurrentHealth = MaxHealth;
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	HandleImmunityTimer(DeltaTime);
}

void UHealthComponent::HandleImmunityTimer(float DeltaTime)
{
	if (!bIsImmune) return;
	if (bIsDead) return;
	
	ImmunityTimer += DeltaTime;
	if (ImmunityTimer >= ImmunityTime)
	{
		bIsImmune = false;
		ImmunityTimer = ImmunityTime; 
	}
}

void UHealthComponent::TakeDamageInternal(float IncomingHealth)
{
	TakeDamage(IncomingHealth, false);
}

void UHealthComponent::TakeDamage(float IncomingHealth, bool IsCritHit = false)
{
	if (bIsImmune) return;

	float FinalDamage = IncomingHealth;
	if (IsCritHit)
	{
		FinalDamage *= 1.5f;
	}

	if (bIsPlayer)
	{
		CurrentHealth = FMath::Clamp(CurrentHealth - FinalDamage, 0, MaxHealth);
		bIsImmune = true;
		ImmunityTimer = 0;
	}
	else
	{
		CurrentHealth = FMath::Clamp(CurrentHealth - FinalDamage, 0, MaxHealth);
	}
	
	OnHit.Broadcast(FinalDamage, IsCritHit);
	
	if (CurrentHealth <= 0)
	{
		Death();
	}
}

void UHealthComponent::GainHealth(int IncomingHealth)
{
	if (CurrentHealth >= MaxHealth) return;

	OnGainHealth.Broadcast();
	CurrentHealth = FMath::Clamp(CurrentHealth + IncomingHealth, 0, MaxHealth);
}

bool UHealthComponent::GetIsImmune() const
{
	return bIsImmune;
}

void UHealthComponent::Death()
{
	if (bIsDead) return;
	bIsDead = true;
	OnDeath.Broadcast();
}

void UHealthComponent::DashImmunity(bool EnableImmunity)
{
	ImmunityTimer = EnableImmunity ? -9999 : ImmunityTime;
	bIsImmune = EnableImmunity;
}

bool UHealthComponent::GetIsDead()
{
	return bIsDead;
}

void UHealthComponent::SetIsDead(bool InBool)
{
	bIsDead = InBool;
}

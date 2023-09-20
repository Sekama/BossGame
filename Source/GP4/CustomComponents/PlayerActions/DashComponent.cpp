// Richard Hill


#include "DashComponent.h"

#include "GP4/Player/PlayerCharacter.h"


UDashComponent::UDashComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDashComponent::ActivateDash()
{
	if (CooldownTimer < Cooldown) return;
	if (Player->GetInputVector().IsNearlyZero()) return;
	
	DashDuration = CachedDashDuration;
	OnDash.Broadcast(true);
	CooldownTimer = 0;
}

void UDashComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Player = Cast<APlayerCharacter>(GetOwner());
	CachedDashDuration = DashDuration;
}

void UDashComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckCooldown(DeltaTime);
	CheckDash(DeltaTime);
	Dash();
}

void UDashComponent::CheckCooldown(float DeltaTime)
{
	if (CooldownTimer < Cooldown)
	{
		CooldownTimer += DeltaTime;
	}
}

void UDashComponent::CheckDash(float DeltaTime)
{
	DashDuration -= DeltaTime;

	if (DashDuration > 0)
	{
		bIsDashing = true;
	}
	else if (bIsDashing)
	{
		bIsDashing = false;
		OnDash.Broadcast(false);
	}
}

void UDashComponent::Dash()
{
	if (bIsDashing)
	{
		float DashDelta = DashDuration * DashPower;
		DashDelta = FMath::Clamp(DashDelta, MinDashDelta, 99999);
		FVector const MoveVector = Player->GetCustomVelocity() * DashDelta;
		Player->ForceMovePlayer(MoveVector);
	}
}


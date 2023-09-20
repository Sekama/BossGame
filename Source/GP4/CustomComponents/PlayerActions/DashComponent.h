// Richard Hill

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DashComponent.generated.h"

class APlayerCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDash, bool, bIsDashing);
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GP4_API UDashComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDashComponent();

	void ActivateDash();

	UPROPERTY(EditAnywhere)
	float Cooldown = 1;
	UPROPERTY(EditAnywhere)
	float DashDuration = 0.8f;
	UPROPERTY(EditAnywhere)
	float DashPower = 5;
	
	UPROPERTY(BlueprintAssignable)
	FOnDash OnDash;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	APlayerCharacter* Player;
	
	float CachedDashDuration;
	bool bIsDashing = false;
	float MinDashDelta = 0.3f;
	float CooldownTimer = 0;

	void CheckCooldown(float DeltaTime);
	void CheckDash(float DeltaTime);
	void Dash();
};

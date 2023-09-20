// Richard Hill

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GP4/Enemies/BaseEnemy.h"
#include "Boss_Second.generated.h"

class UBaseAbilityComponent;
class APlayerCharacter;

UCLASS()
class ABoss_Second : public ABaseEnemy
{
	GENERATED_BODY()

public:
	ABoss_Second();

	virtual void PerformAttack() override;

	UPROPERTY(EditAnywhere, Category = AbilityComponents)
	UBaseAbilityComponent* LaserRayComponent;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void RotateTowardPlayer();
	
	UPROPERTY()
	APlayerCharacter* Player;




	
	// PID Controller
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Proportion = 0.005f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Integral = 0.0003f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Derivative = 0.00006;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MinOutput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MaxOutput = 100;
	
	float LastError;
	FVector PrevError;
	float Accumulator;
	
	FVector UpdatePID(const FVector& InError, float InDeltaTime);
	float ResetPID(float NewErrorValue, float NewAccumulatorValue);
};
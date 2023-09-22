// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovementStatics.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GP4/Player/PlayerCharacter.h"
#include "PlayerMovementComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGroundStateChangedDelegate, const bool, OnGround, const bool, PreviouslyOnGround);

struct FMovementStatics;

UCLASS()
class UPlayerMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	UPlayerMovementComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FMovementStatics CreateFrameMovement() const;
	void Move(FMovementStatics& FrameMovement, FRotator TargetRotation);

	// Delegate that gets called when the ground state changes (when the component lands on ground or leaves it).
	FGroundStateChangedDelegate OnGroundStateChanged;
	UPROPERTY()
	APawn* Owner;
	UPROPERTY()
	UCapsuleComponent* Capsule;

	// Returns the surface normal value, if standing onh ground and the vector is a valid normal (in case it would be zero).
	UFUNCTION(BlueprintCallable)
	bool GetSurfaceNormal(FVector& OutNormal);
	// Returns the current rate at which the component moves. in U/s.
	UFUNCTION(BlueprintCallable)
	FVector GetVelocity() const { return CompVelocity; }
	UPROPERTY(EditAnywhere)
	APlayerCharacter* PlayerCharacter;
	// If the player is standing on solid ground or not.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bOnGround = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Acceleration = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Gravity = 10;
	UPROPERTY(BlueprintReadWrite)
	bool bApplyGravity = true;

protected:
	// The rate at whih the owner of this actor moves. In U/s.
	UPROPERTY(VisibleAnywhere)
	FVector CompVelocity;
	// The threshold for where slopes start counting as walls.
	UPROPERTY(EditDefaultsOnly)
	float MaxSlopeAngle = 55.f;
	
	// The surface normal of the last ground stood in.
	FVector GroundNormal;
	// Vector that CompVelocity uses as reference in conjunction with input.
	FVector VelocityInput;
	FVector MoveAxes;

	// Movement updates and collision detection are executed in here.
	virtual void ExecuteMovement(FVector& TestVelocity, bool& TestOnGround, float DeltaTime);
	FVector GetMovementDelta(const FMovementStatics& FrameMovement) const;

	// Returns the nextx speed that CompVelocity is supposed to receive, based on the values in MovementData.
	UFUNCTION(BlueprintCallable)
	virtual void CalculateNextVelocity(FVector& TargetVelocity, const FVector& Input, float DeltaTime);
	
	
};

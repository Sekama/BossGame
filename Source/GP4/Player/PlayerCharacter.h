// Author Richard Hill - FutureGames

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter.generated.h"

class UDashComponent;
class UPlayerFireComponent;
class UCapsuleComponent;
class UCameraComponent;
class UInputComponent;
class USkeletalMeshComponent;

class UHealthComponent;
class UPlayerCameraComponent;
class UPlayerMovementComponent;

UCLASS()
class APlayerCharacter : public APawn
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	UPROPERTY(EditAnywhere, Category = Collision)
	UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	UPlayerCameraComponent* CustomCameraComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Dash)
	UDashComponent* DashComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat)
	UPlayerFireComponent* FireComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attacking | Projectile")
	USceneComponent* ProjectileSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	UPlayerMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere)
	APlayerController* PlayerController;
	
	UPROPERTY(BlueprintReadWrite, Category = Movement)
	bool bIsAllowedToMove = true;

	UPROPERTY(EditAnywhere, Category = Movement)
	float TurnRate = 0.3f;
	float MovementSpeed;

	virtual void Tick(float DeltaTime) override;
	void HandleInput(float DeltaTime);
	void MovePlayer(float DeltaTime);

	UFUNCTION()
	float PlayAnimationMontage(UAnimMontage* Montage, float InPlayRate=1.f, FName StartSectionName=NAME_None, float StartMontageAt=0.f);
	UFUNCTION()
	float GetMontagePosition(UAnimMontage* Montage);

	UFUNCTION(BlueprintCallable)
	void ShakeCamera(float Duration, float Intensity);

	UCapsuleComponent* GetCapsule() const { return Capsule; }
	bool GetIsAllowedToMove() const { return bIsAllowedToMove; }
	FVector GetCustomVelocity() const { return Velocity; }
	FVector GetInputVector() const { return InputVector; }
	void ForceMovePlayer(FVector InDelta);
	FVector GetPlayerFuturePos(float InDeltaFrames) const;
	UFUNCTION(BlueprintCallable)
	void SetSensitivity(float InSensitivity);
	UFUNCTION(BlueprintCallable)
	float GetSensitivity() const { return Sensitivity; }
	UFUNCTION(BlueprintCallable)
	void Pause();
	
	//INPUT
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = EnhancedInput)
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = EnhancedInput)
	UInputAction* IA_Movement;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = EnhancedInput)
	UInputAction* IA_PrimaryFire;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = EnhancedInput)
	UInputAction* IA_RotateCamera;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = EnhancedInput)
	UInputAction* IA_Scroll;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = EnhancedInput)
	UInputAction* IA_Shift;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = EnhancedInput)
	UInputAction* IA_Space;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnhancedInput)
	UInputAction* IA_Pause;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly)
	FVector Velocity;
	FVector InputVector = FVector::ZeroVector;
	FVector LookVector = FVector::ZeroVector;
	FRotator CurrentRot;
	FRotator CharRotation;

	float Sensitivity = 1.f;

	void ShowMouseCursor(bool ShowCursor);
	void EnhancedInputMove(const FInputActionValue& Value);
	void EnableCameraRotation(const FInputActionValue& Value);
	void ScrollCamera(const FInputActionValue& Value);
	void EnableShift(const FInputActionValue& Value);
	virtual void PrimaryFire();
	virtual void PrimaryRelease();
	void Dash();
	void RotatePlayer(float DeltaTime);
	void RotatePlayer(float DeltaTime, FRotator Direction);
	void ForceRotatePlayer(FRotator Direction);

	UFUNCTION(BlueprintImplementableEvent)
	void OnPause(bool Pause);

	bool bIsPaused = false;
};

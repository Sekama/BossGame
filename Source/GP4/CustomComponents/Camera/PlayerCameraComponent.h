// Richard Hill

#pragma once

#include "CoreMinimal.h"
#include "GP4/Player/CameraShake.h"
#include "Components/ActorComponent.h"	
#include "PlayerCameraComponent.generated.h"

class USpringArmComponent;
class APlayerCharacter;
class UCameraComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UPlayerCameraComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerCameraComponent();

	UFUNCTION(BlueprintCallable)
	USpringArmComponent* GetSpringArm() const;
	UFUNCTION(BlueprintCallable)
	UCameraComponent* GetCamera() const;
	void SetCameraDistance(float Distance);
	void EnableFoVShift(bool Enable);
	void SetSocketOffset(FVector Offset);
	void SetAimMode(bool Enable);
	UFUNCTION(BlueprintCallable)
	void SetCameraRotationSpeed(float Speed);
	UFUNCTION(BlueprintCallable)
	void SetFov(float Fov);
	void ShakeCamera(float Duration, float Intensity);

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	USpringArmComponent* SpringArm;
	UPROPERTY()
	UCameraComponent* Camera;
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;
	
	UPROPERTY(EditAnywhere, Category = "CameraSettings | Spring Arm")
	float NewArmLength = 3000;
	UPROPERTY(EditAnywhere, Category = "CameraSettings | Spring Arm")
	float CameraDistanceInterpSpeed = 10;
	UPROPERTY(EditAnywhere, Category = "CameraSettings | FOV")
	float NewFoV = 60;
	UPROPERTY(EditAnywhere, Category = "CameraSettings | FOV")
	float MinFoV = 45;
	UPROPERTY(EditAnywhere, Category = "CameraSettings | FOV")
	float MaxFoV = 90;
	UPROPERTY(EditAnywhere, Category = "CameraSettings | FOV")
	float FoVInterpSpeed = 10;
	UPROPERTY(EditAnywhere, Category = "CameraSettings | Pitch")
	double MaxCameraPitchRotation = -84;
	UPROPERTY(EditAnywhere, Category = "CameraSettings | Pitch")
	double MinCameraPitchRotation = -10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraSettings | Aiming")
	float CameraRotationSpeed = 1;
	UPROPERTY(EditAnywhere, Category = "CameraSettings | Aiming")
	float CameraModeChangeSpeed = 10;
	UPROPERTY(EditAnywhere, Category = "CameraSettings | Aiming")
	FVector2D NormalCameraOffset;
	UPROPERTY(EditAnywhere, Category = "CameraSettings | Aiming")
	FVector2D AimCameraOffset;
	UPROPERTY(EditAnywhere, Category = "CameraSettings | Aiming")
	float NormalCameraZoom = 1500;
	UPROPERTY(EditAnywhere, Category = "CameraSettings | Aiming")
	float AimCameraZoom = 0;
	UPROPERTY(EditAnywhere, Category = "CameraSettings | Camera Shake")
	TSubclassOf<UCameraShakeBase> CameraShake;

	bool bHoldingShift = false;

	void UpdateCameraDistance(float DeltaTime);
	void UpdateCameraFoV(float DeltaTime);
	void RotateCamera(float DeltaTime) const;
	void UpdateSocketOffset(float DeltaTime);

	FVector TargetSocketOffset;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};

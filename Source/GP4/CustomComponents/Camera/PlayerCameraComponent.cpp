// Richard Hill


#include "PlayerCameraComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GP4/Player/CameraShake.h"
#include "GP4/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

UPlayerCameraComponent::UPlayerCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

USpringArmComponent* UPlayerCameraComponent::GetSpringArm() const
{
	return SpringArm;
}

UCameraComponent* UPlayerCameraComponent::GetCamera() const
{
	return Camera;
}

void UPlayerCameraComponent::SetCameraDistance(float Distance)
{
	NewArmLength = Distance;
}

void UPlayerCameraComponent::SetSocketOffset(FVector Offset)
{
	TargetSocketOffset = Offset;
}

void UPlayerCameraComponent::EnableFoVShift(bool Enable)
{
	bHoldingShift = Enable;
}

void UPlayerCameraComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	SpringArm = NewObject<USpringArmComponent>(this);
	SpringArm->SetupAttachment(GetOwner()->GetRootComponent());
	SpringArm->RegisterComponent();

	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 15;
	SpringArm->TargetArmLength = 3000;
	SpringArm->bInheritYaw = false;
	SpringArm->bDoCollisionTest = true;
	SpringArm->ProbeChannel = ECC_Camera;
	
	Camera = NewObject<UCameraComponent>(this);
	Camera->SetupAttachment(SpringArm);
	Camera->RegisterComponent();

	Camera->FieldOfView = 45;

}

void UPlayerCameraComponent::UpdateCameraDistance(float DeltaTime)
{
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, NewArmLength, DeltaTime, CameraDistanceInterpSpeed);
}

void UPlayerCameraComponent::UpdateCameraFoV(float DeltaTime)
{
	Camera->FieldOfView = FMath::FInterpTo(Camera->FieldOfView, NewFoV, DeltaTime, FoVInterpSpeed);
}

void UPlayerCameraComponent::UpdateSocketOffset(float DeltaTime)
{
	SpringArm->SocketOffset = FMath::VInterpTo(SpringArm->SocketOffset, TargetSocketOffset, DeltaTime, CameraModeChangeSpeed);
}


void UPlayerCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	RotateCamera(DeltaTime);
	UpdateCameraDistance(DeltaTime);
	UpdateCameraFoV(DeltaTime);
	UpdateSocketOffset(DeltaTime);
}

void UPlayerCameraComponent::RotateCamera(float DeltaTime) const
{
	FVector2D MousePositionDelta = FVector2D(0, 0);
	GetWorld()->GetFirstPlayerController()->GetInputMouseDelta(MousePositionDelta.X, MousePositionDelta.Y);
	auto Sensitivity = PlayerCharacter->GetSensitivity();
	float Pitch = MousePositionDelta.Y * CameraRotationSpeed * Sensitivity;

	if (SpringArm->GetRelativeRotation().Pitch < MaxCameraPitchRotation && Pitch < 0)
	{
		Pitch = 0;
	}
	else if (SpringArm->GetRelativeRotation().Pitch > MinCameraPitchRotation && Pitch > 0)
	{
		Pitch = 0;
	}

	const FRotator TargetRotation = FRotator(Pitch, MousePositionDelta.X * CameraRotationSpeed * Sensitivity, 0);
	const FRotator Rotation = FMath::RInterpConstantTo(FRotator::ZeroRotator, TargetRotation, DeltaTime, 0);
	
	SpringArm->AddRelativeRotation(Rotation);
}

void UPlayerCameraComponent::SetAimMode(bool Enable)
{
	if (Enable)
	{
		SetSocketOffset(FVector(0, AimCameraOffset.X, AimCameraOffset.Y));
		SetCameraDistance(AimCameraZoom);
	}
	else
	{
		SetSocketOffset(FVector(0, NormalCameraOffset.X, NormalCameraOffset.Y));
		SetCameraDistance(NormalCameraZoom);
	}
}

void UPlayerCameraComponent::SetCameraRotationSpeed(float Speed)
{
	CameraRotationSpeed = Speed;
}

void UPlayerCameraComponent::SetFov(float Fov)
{
	NewFoV = Fov;
}

void UPlayerCameraComponent::ShakeCamera(float Duration, float Intensity)
{
	if (!IsValid(CameraShake))
	{
		UE_LOG(LogTemp, Warning, TEXT("CameraShak eee is not valid"));
		return;
	}
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CameraShake, Intensity);
}
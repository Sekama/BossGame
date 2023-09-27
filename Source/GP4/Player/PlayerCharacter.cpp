// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GP4/CustomComponents/Camera/PlayerCameraComponent.h"
#include "GP4/CustomComponents/Health/HealthComponent.h"
#include "GP4/CustomComponents/PlayerActions/DashComponent.h"
#include "GP4/CustomComponents/PlayerMovement/MovementStatics.h"
#include "GP4/CustomComponents/PlayerMovement/PlayerMovementComponent.h"
#include "GP4/CustomComponents/PlayerActions/PlayerFireComponent.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	Capsule->SetCollisionProfileName("BlockAllDynamic");

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character Mesh"));
	Mesh->SetupAttachment(Capsule);
	Mesh->bCastDynamicShadow = true;
	Mesh->CastShadow = true;
	
	MovementComponent = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("Movement Component"));
	MovementComponent->SetUpdatedComponent(Capsule);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	CustomCameraComponent = CreateDefaultSubobject<UPlayerCameraComponent>(TEXT("Camera Component"));

	DashComponent = CreateDefaultSubobject<UDashComponent>(TEXT("Dash Component"));

	FireComponent = CreateDefaultSubobject<UPlayerFireComponent>(TEXT("Fire Component"));
	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn"));
	ProjectileSpawn->SetupAttachment(RootComponent);
}

void APlayerCharacter::ForceMovePlayer(FVector InDelta)
{
	FMovementStatics FrameMovement = MovementComponent->CreateFrameMovement();
	FrameMovement.ShouldApplyGravity();
	FrameMovement.AddDelta(InDelta);
		
	if (bIsAllowedToMove) // Move player unless stunned
	{
		MovementComponent->Move(FrameMovement, CharRotation);
	}
}

FVector APlayerCharacter::GetPlayerFuturePos(float InDeltaFrames) const
{
	return GetActorLocation() + (Velocity * InDeltaFrames);
}

void APlayerCharacter::SetSensitivity(float InSensitivity)
{
	Sensitivity = InSensitivity;
}

void APlayerCharacter::EnhancedInputMove(const FInputActionValue& Value)
{	
	if (!bIsAllowedToMove)
	{
		InputVector = FVector::ZeroVector;
		return;
	}
		
	InputVector.X = Value.Get<FVector2D>().X;
	InputVector.Y = Value.Get<FVector2D>().Y;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = GetWorld()->GetFirstPlayerController();
	
	MovementSpeed = MovementComponent->MovementSpeed;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Movement & Input
	RotatePlayer(DeltaTime);
	HandleInput(DeltaTime);
	MovePlayer(DeltaTime);
}

void APlayerCharacter::HandleInput(float DeltaTime)
{
	if (!InputVector.IsNearlyZero() && CustomCameraComponent->GetCamera())
	{
		const FVector CameraForward = CustomCameraComponent->GetCamera()->GetForwardVector();
		const FVector Forward = FVector(CameraForward.X, CameraForward.Y, 0);
		const FVector ForwardMovement = Forward * InputVector.X;
		const FVector CameraRight = CustomCameraComponent->GetCamera()->GetRightVector();
		const FVector Right = FVector(CameraRight.X,CameraRight.Y, 0);
		const FVector RightMovement = Right * InputVector.Y;
		
		Velocity = (ForwardMovement + RightMovement).GetSafeNormal() * MovementSpeed * DeltaTime;
	}
}

void APlayerCharacter::MovePlayer(float DeltaTime)
{
	if (!InputVector.IsNearlyZero())
	{
		FMovementStatics FrameMovement = MovementComponent->CreateFrameMovement();

		FrameMovement.AddDelta(Velocity);
		
		if (bIsAllowedToMove) // Move player unless stunned
		{
			MovementComponent->Move(FrameMovement, CharRotation);
		}
	}
}

float APlayerCharacter::PlayAnimationMontage(UAnimMontage* Montage, float InPlayRate, FName StartSectionName, float StartMontageAt)
{
	UAnimInstance* AnimInstance = (Mesh)? Mesh->GetAnimInstance() : nullptr; 
	if ( Montage && AnimInstance )
	{
		float Duration = AnimInstance->Montage_Play(Montage, InPlayRate, EMontagePlayReturnType::MontageLength, StartMontageAt);
		if (Duration > 0.f)
		{
			// Start at a given Section.
			if( StartSectionName != NAME_None )
			{
				AnimInstance->Montage_JumpToSection(StartSectionName, Montage);
				int const MontageSectionID = Montage->GetSectionIndex(StartSectionName);
				Duration = Montage->GetSectionLength(MontageSectionID);
			}
			float const DurationModified = (Duration * InPlayRate) - Duration;
			float const ReturnDuration = FMath::Abs(Duration - DurationModified);
			return ReturnDuration;
		}
	}
	return 0;
}

float APlayerCharacter::GetMontagePosition(UAnimMontage* Montage)
{
	UAnimInstance* AnimInstance = (Mesh)? Mesh->GetAnimInstance() : nullptr;

	if (AnimInstance)
	{
		return AnimInstance->Montage_GetPosition(Montage);
	}
	return 0;
}

void APlayerCharacter::ShakeCamera(float Duration, float Intensity)
{
	CustomCameraComponent->ShakeCamera(Duration, Intensity);
}

void APlayerCharacter::ShowMouseCursor(bool ShowCursor)
{
	PlayerController->bShowMouseCursor = ShowCursor;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent)

	// Enhanced input
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(GetNetOwningPlayer()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!InputMappingContext) return;
		
			InputSystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInputComponent->BindAction(IA_Movement, ETriggerEvent::Triggered, this, &APlayerCharacter::EnhancedInputMove);
	EnhancedInputComponent->BindAction(IA_Movement, ETriggerEvent::Completed, this, &APlayerCharacter::EnhancedInputMove);
	EnhancedInputComponent->BindAction(IA_Scroll, ETriggerEvent::Triggered, this, &APlayerCharacter::ScrollCamera);
	EnhancedInputComponent->BindAction(IA_Scroll, ETriggerEvent::Completed, this, &APlayerCharacter::ScrollCamera);
	EnhancedInputComponent->BindAction(IA_PrimaryFire, ETriggerEvent::Started, this, &APlayerCharacter::PrimaryFire);
	EnhancedInputComponent->BindAction(IA_PrimaryFire, ETriggerEvent::Completed, this, &APlayerCharacter::PrimaryRelease);
	EnhancedInputComponent->BindAction(IA_Space, ETriggerEvent::Started, this, &APlayerCharacter::Dash);
	EnhancedInputComponent->BindAction(IA_RotateCamera, ETriggerEvent::Started, this, &APlayerCharacter::EnableCameraRotation);
	EnhancedInputComponent->BindAction(IA_RotateCamera, ETriggerEvent::Completed, this, &APlayerCharacter::EnableCameraRotation);
	EnhancedInputComponent->BindAction(IA_Shift, ETriggerEvent::Started, this, &APlayerCharacter::EnableShift);
	EnhancedInputComponent->BindAction(IA_Shift, ETriggerEvent::Completed, this, &APlayerCharacter::EnableShift);
	EnhancedInputComponent->BindAction(IA_Pause, ETriggerEvent::Started, this, &APlayerCharacter::Pause);
}

void APlayerCharacter::EnableCameraRotation(const FInputActionValue& Value)
{
	if (DashComponent->bIsDashing) return;

	bool const Enable = Value.Get<bool>();

	FireComponent->SetAimMode(Enable);
}

void APlayerCharacter::ScrollCamera(const FInputActionValue& Value)
{

}

void APlayerCharacter::EnableShift(const FInputActionValue& Value)
{
	bool const Enable = Value.Get<bool>();
	CustomCameraComponent->EnableFoVShift(Enable);
}

void APlayerCharacter::PrimaryFire()
{
	FireComponent->Fire();
}

void APlayerCharacter::PrimaryRelease()
{
	
}

void APlayerCharacter::RotatePlayer(float DeltaTime)
{
	if(FireComponent->bIsAiming)
	{
		if (!InputVector.IsNearlyZero())
		{
			RotatePlayer(DeltaTime, FireComponent->GetAimRotation());
		}
		else
		{
			ForceRotatePlayer(FireComponent->GetAimRotation());
		}
		return;
	}

	if (!InputVector.IsNearlyZero())
	{
		RotatePlayer(DeltaTime, Velocity.ToOrientationRotator());
	}
}

void APlayerCharacter::RotatePlayer(float DeltaTime, FRotator Direction)
{
	CurrentRot = GetActorRotation();
	CharRotation = FMath::RInterpTo(CurrentRot, Direction, DeltaTime, TurnRate);

}

void APlayerCharacter::ForceRotatePlayer(FRotator Direction)
{
	auto FrameMovement = MovementComponent->CreateFrameMovement();
	FrameMovement.AddDelta(Direction.Vector() * .0001f);
	MovementComponent->Move(FrameMovement, Direction);
}

void APlayerCharacter::Pause()
{
	bIsPaused = !bIsPaused;
	OnPause(bIsPaused);
}

void APlayerCharacter::Dash()
{
	if (FireComponent->bIsAiming)
	{
		FireComponent->SetAimMode(false);
	}

	DashComponent->ActivateDash();
}







































// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlatform.h"

#include "Components/BoxComponent.h"


ABasePlatform::ABasePlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetEnableGravity(false);
	Mesh->SetGenerateOverlapEvents(false);

	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	TriggerZone->SetupAttachment(Root);
	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &ABasePlatform::OverlapBegin);
	TriggerZone->OnComponentEndOverlap.AddDynamic(this, &ABasePlatform::OverlapEnd);
}

void ABasePlatform::BeginPlay()
{
	Super::BeginPlay();
	PlayerRef = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void ABasePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePlatform::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if (MovePlayer && OtherActor == PlayerRef)
		OtherActor->AttachToComponent(Root, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
	OnBeginOverlap(OtherActor);
}

void ABasePlatform::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (MovePlayer && OtherActor == PlayerRef)
		OtherActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	OnBeginOverlap(OtherActor);
}

void ABasePlatform::OnBeginOverlap(AActor* OtherActor) {}
void ABasePlatform::OnEndOverlap(AActor* OtherActor) {}





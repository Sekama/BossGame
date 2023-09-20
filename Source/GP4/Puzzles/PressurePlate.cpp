// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"

APressurePlate::APressurePlate()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	TriggerBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void APressurePlate::Trigger()
{
	if (bIsTriggered && !bEndlessTrigger) return;

	Mesh->AddRelativeLocation(FVector(0, 0, -5));

	Super::Trigger();
}
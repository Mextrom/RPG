// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable.h"

// Sets default values
AInteractable::AInteractable()
{
	Name = "<noname>";
	Action = "Interact";
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
}

// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "RPGPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "RPGCharacter.h"
#include "Engine/World.h"
#include "Interactable.h"
#include "RPGGameMode.h"

ARPGPlayerController::ARPGPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ARPGPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
    else
    {
        Interact();
    }
}

void ARPGPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ARPGPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ARPGPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ARPGPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ARPGPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &ARPGPlayerController::OnResetVR);

    InputComponent->BindAction("Interact", IE_Pressed, this, &ARPGPlayerController::Interact);
}

void ARPGPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ARPGPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ARPGCharacter* MyPawn = Cast<ARPGCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
            AInteractable* Interactable = Cast<AInteractable>(Hit.GetActor());
            if (Interactable)
            {
                CurrentInteractable = Interactable;
            }
            else
            {
                CurrentInteractable = nullptr;
            }

            // We hit something, move there
            SetNewMoveDestination(Hit.ImpactPoint);
		}
        else
        {
            CurrentInteractable = nullptr;
        }
	}
}

void ARPGPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ARPGPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ARPGPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ARPGPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void ARPGPlayerController::Interact()
{
    if (CurrentInteractable)
    {
        ARPGCharacter* MyPawn = Cast<ARPGCharacter>(GetPawn());
        if (MyPawn)
        {
            float const Distance = FVector::Dist(CurrentInteractable->GetActorLocation(), MyPawn->GetActorLocation());
            if (Distance <= 200.0f)
            {
                CurrentInteractable->Interact(this);
            }
        }
    }
}

void ARPGPlayerController::AddItemToInventory(FName ID)
{
    ARPGGameMode* GameMode = Cast<ARPGGameMode>(GetWorld()->GetAuthGameMode());
    if (GameMode)
    {
        UDataTable* ItemTable = GameMode->GetItemDB();
        if (ItemTable)
        {
            FInventoryItem* ItemToAdd = ItemTable->FindRow<FInventoryItem>(ID, "");
            if (ItemToAdd)
            {
                Inventory.Add(*ItemToAdd);
            }
        }
    }
}

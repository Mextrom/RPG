// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RPGCharacter.h"
#include "RPGPlayerController.generated.h"

UCLASS()
class ARPGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARPGPlayerController();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class AInteractable* CurrentInteractable;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    TArray<FInventoryItem> Inventory;

    UFUNCTION(BlueprintCallable, Category = "Utils")
    void AddItemToInventory(FName ID);

    UFUNCTION(BlueprintCallable, Category = "Utils")
    void CraftItem(FInventoryItem ItemA, FInventoryItem ItemB, ARPGPlayerController* Controller);

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

    void Interact();
};



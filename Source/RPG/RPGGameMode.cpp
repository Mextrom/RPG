// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "RPGGameMode.h"
#include "RPGPlayerController.h"
#include "RPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARPGGameMode::ARPGGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ARPGPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

    static ConstructorHelpers::FObjectFinder<UDataTable> BP_ItemDB(TEXT("DataTable'/Game/Data/ItemDB.ItemDB'"));
    ItemDB = BP_ItemDB.Object;
}

UDataTable* ARPGGameMode::GetItemDB() const
{
    return ItemDB;
}
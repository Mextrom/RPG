#pragma once

#include "CoreMinimal.h"
#include "FCraftingInfo.h"
#include "Engine/Texture2D.h"
#include "Engine/DataTable.h"
#include "FInventoryItem.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItem : public FTableRowBase
{
    GENERATED_BODY()

public:

    FInventoryItem();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<class APickup> ItemPickup;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Action;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Value;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Thumbnail;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FCraftingInfo> CraftCombinations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanBeUsed;

    bool operator==(const FInventoryItem& other) const;
};

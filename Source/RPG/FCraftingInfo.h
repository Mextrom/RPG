#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FCraftingInfo.generated.h"

USTRUCT(BlueprintType)
struct FCraftingInfo : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ComponentID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ProductID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bDestroyItemA;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bDestroyItemB;
};


#include "FInventoryItem.h"

FInventoryItem::FInventoryItem()
{
    Name = FText::FromString("Item");
    Action = FText::FromString("Use");
    Description = FText::FromString("Please neter a description for this item");
    Value = 10;
}

bool FInventoryItem::operator==(const FInventoryItem& other) const
{
    return ItemID == other.ItemID;
}

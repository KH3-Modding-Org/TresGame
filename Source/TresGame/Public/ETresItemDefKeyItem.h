#pragma once
#include "CoreMinimal.h"
#include "ETresItemDefKeyItem.generated.h"

UENUM(BlueprintType)
enum class ETresItemDefKeyItem : uint8 {
    NOTHING,
    ITEM01,
    ITEM02 UMETA(DisplayName = "Gummiphone"),
    ITEM03 UMETA(DisplayName = "AR Device"),
    ITEM04 UMETA(DisplayName = "Prize Postcard"),
    ITEM05 UMETA(DisplayName = "M.O.G. Card"),
    ITEM06 UMETA(DisplayName = "Dream Heartbinder"),
    ITEM07 UMETA(DisplayName = "Pixel Heartbinder"),
    ITEM08 UMETA(DisplayName = "'Ohana Heartbinder"),
    ITEM09 UMETA(DisplayName = "Pride Heartbinder"),
    ITEM10 UMETA(DisplayName = "Ocean Heartbinder"),
    ITEM11 UMETA(DisplayName = "Golden Herc Figure"),
    ITEM12 UMETA(DisplayName = "Proof of Promises"),
    ITEM13 UMETA(DisplayName = "Proof of Times Past"),
    _MAX = 0x18,
};


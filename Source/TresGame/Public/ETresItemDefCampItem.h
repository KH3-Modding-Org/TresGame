#pragma once
#include "CoreMinimal.h"
#include "ETresItemDefCampItem.generated.h"

UENUM(BlueprintType)
enum class ETresItemDefCampItem : uint8 {
    NOTHING,
    TENT UMETA(DisplayName = "Tent"),
    POWERUP UMETA(DisplayName = "Strength Boost"),
    MAGICUP UMETA(DisplayName = "Magic Boost"),
    GUARDUP UMETA(DisplayName = "Defense Boost"),
    APUP UMETA(DisplayName = "AP Boost"),
    _MAX = 0x8,
};


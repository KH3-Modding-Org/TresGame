#pragma once
#include "CoreMinimal.h"
#include "ETresItemDefReport.generated.h"

UENUM(BlueprintType)
enum class ETresItemDefReport : uint8 {
    NOTHING,
    ITEM01,
    ITEM02 UMETA(DisplayName = "Secret Report 1"),
    ITEM03 UMETA(DisplayName = "Secret Report 2"),
    ITEM04 UMETA(DisplayName = "Secret Report 3"),
    ITEM05 UMETA(DisplayName = "Secret Report 4"),
    ITEM06 UMETA(DisplayName = "Secret Report 5"),
    ITEM07 UMETA(DisplayName = "Secret Report 6"),
    ITEM08 UMETA(DisplayName = "Secret Report 7"),
    ITEM09 UMETA(DisplayName = "Secret Report 8"),
    ITEM10 UMETA(DisplayName = "Secret Report 9"),
    ITEM11 UMETA(DisplayName = "Secret Report 10"),
    ITEM12 UMETA(DisplayName = "Secret Report 11"),
    ITEM13 UMETA(DisplayName = "Secret Report 12"),
    ITEM14 UMETA(DisplayName = "Secret Report 13"),
    _MAX = 0x14,
};


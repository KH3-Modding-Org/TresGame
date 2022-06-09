#pragma once
#include "CoreMinimal.h"
#include "GUMISHIP_ENEMY625_METEORO_BONE.generated.h"

UENUM(BlueprintType)
enum class GUMISHIP_ENEMY625_METEORO_BONE : uint8 {
    BACK_GM625_BONE,
    BOTTOM_GM625_BONE,
    CENTER_GM625_BONE,
    FRONT_GM625_BONE,
    LEFT_GM625_BONE,
    RIGHT_GM625_BONE,
    TOP_GM625_BONE,
    NEAR_GM625_BONE,
    GUMISHIP_ENEMY625_METEORO_MAX UMETA(Hidden),
};

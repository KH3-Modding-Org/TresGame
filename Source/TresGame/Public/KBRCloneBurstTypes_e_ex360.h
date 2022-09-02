#pragma once
#include "CoreMinimal.h"
#include "KBRCloneBurstTypes_e_ex360.generated.h"

UENUM(BlueprintType)
enum KBRCloneBurstTypes_e_ex360 {
    TRES_ENEMY_EX360_CLONEBURST_SLASH,
    TRES_ENEMY_EX360_CLONEBURST_CUTUP,
    TRES_ENEMY_EX360_CLONEBURST_CUTDOWN,
    TRES_ENEMY_EX360_CLONEBURST_ONLY_KEYBLADES,
    TRES_ENEMY_EX360_CLONEBURST_CLONE_SLASH,
    TRES_ENEMY_EX360_CLONEBURST_CLONE_CUTUP,
    TRES_ENEMY_EX360_CLONEBURST_CLONE_CUTDOWN,
    TRES_ENEMY_EX360_CLONEBURST_SHOOT_KEYBLADES,
    TRES_ENEMY_EX360_CLONEBURST_MAX UMETA(Hidden),
};

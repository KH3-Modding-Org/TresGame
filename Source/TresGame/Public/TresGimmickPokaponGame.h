#pragma once
#include "CoreMinimal.h"
#include "TresGimmickSkeletalBase.h"
#include "TresGimmickPokaponGame.generated.h"

UCLASS(Blueprintable, Config=Game)
class ATresGimmickPokaponGame : public ATresGimmickSkeletalBase {
    GENERATED_BODY()
public:
    ATresGimmickPokaponGame();
};

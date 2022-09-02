#pragma once
#include "CoreMinimal.h"
#include "TresInterpTrackFaceAnimation.h"
#include "TresInterpTrackLipAnimation.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class TRESGAME_API UTresInterpTrackLipAnimation : public UTresInterpTrackFaceAnimation {
    GENERATED_BODY()
public:
    UTresInterpTrackLipAnimation();
};

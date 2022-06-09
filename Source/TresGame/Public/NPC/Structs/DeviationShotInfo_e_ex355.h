#pragma once
#include "CoreMinimal.h"
#include "DeviationShotInfo_e_ex355.generated.h"

USTRUCT(BlueprintType)
struct FDeviationShotInfo_e_ex355 {
    GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly)
    float fDeviationRate;
    
    UPROPERTY(EditDefaultsOnly)
    float fMaxDeviationTargetVelocity;
    
    UPROPERTY(EditDefaultsOnly)
    bool bNoVerticalDiviation;
    
    TRESGAME_API FDeviationShotInfo_e_ex355();
};

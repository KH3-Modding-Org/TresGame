#pragma once
#include "CoreMinimal.h"
#include "TresGumiShipRailSlideMovementCompoBase.h"
#include "TresGumiShipTrackingMovementCompo.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UTresGumiShipTrackingMovementCompo : public UTresGumiShipRailSlideMovementCompoBase {
    GENERATED_BODY()
public:
    UTresGumiShipTrackingMovementCompo();
};

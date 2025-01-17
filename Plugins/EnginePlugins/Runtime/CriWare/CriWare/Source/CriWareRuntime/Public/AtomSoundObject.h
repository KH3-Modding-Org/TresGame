#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AtomSoundObject.generated.h"

UCLASS(MinimalAPI)
class UAtomSoundObject : public UDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
    bool EnableVoiceLimitScope;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
    bool EnableCategoryCueLimitScope;
    
    UAtomSoundObject();
};


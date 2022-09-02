#pragma once
#include "CoreMinimal.h"
#include "ETresWorldCode.h"
//CROSS-MODULE INCLUDE V2: -ModuleName=CoreUObject -ObjectName=StringAssetReference -FallbackName=StringAssetReference
#include "TresWorldCodeLoadAssetName.generated.h"

USTRUCT(BlueprintType)
struct FTresWorldCodeLoadAssetName {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, GlobalConfig)
    TEnumAsByte<ETresWorldCode> m_WorldCode;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, GlobalConfig, meta=(AllowPrivateAccess=true))
    FStringAssetReference m_AssetName;
    
    TRESGAME_API FTresWorldCodeLoadAssetName();
};

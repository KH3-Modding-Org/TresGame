#pragma once
#include "CoreMinimal.h"
#include "TresClaymoreSwingDownInfo_e_ex355.generated.h"

USTRUCT(BlueprintType)
struct FTresClaymoreSwingDownInfo_e_ex355 {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_fRevolveRadius;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_fRevolveHeight;
    
    TRESGAME_API FTresClaymoreSwingDownInfo_e_ex355();
};

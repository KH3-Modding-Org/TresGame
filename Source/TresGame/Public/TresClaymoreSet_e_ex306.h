#pragma once
#include "CoreMinimal.h"
#include "TresClaymoreSet_e_ex306.generated.h"

class ATresProjectile_e_ex306_Claymore_Idle;

USTRUCT(BlueprintType)
struct FTresClaymoreSet_e_ex306 {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(EditAnywhere)
    TWeakObjectPtr<ATresProjectile_e_ex306_Claymore_Idle> pClaymore;
    
public:
    TRESGAME_API FTresClaymoreSet_e_ex306();
};

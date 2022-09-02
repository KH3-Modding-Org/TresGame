#pragma once
#include "CoreMinimal.h"
#include "ETresGumiShipBattleMissionType.h"
#include "TresGumiShipBattleMisisonBonusWithConditionI.h"
#include "TresGumiShipBattleMissionIndividalParam.generated.h"

USTRUCT(BlueprintType)
struct FTresGumiShipBattleMissionIndividalParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ETresGumiShipBattleMissionType m_eBattleType;
    
    UPROPERTY(EditAnywhere)
    uint32 m_udScoreOfRanks[5];
    
    UPROPERTY(EditAnywhere)
    int32 m_dTimeBonus[8];
    
    UPROPERTY(EditAnywhere)
    FTresGumiShipBattleMisisonBonusWithConditionI m_DefeatedBonus[3];
    
    UPROPERTY(EditAnywhere)
    uint32 m_udTimeLimitSeconds;
    
    UPROPERTY(EditAnywhere)
    uint32 m_udNumbetOfDefeated;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_ItemDataName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString m_InfoMesLabel;
    
    TRESGAME_API FTresGumiShipBattleMissionIndividalParam();
};

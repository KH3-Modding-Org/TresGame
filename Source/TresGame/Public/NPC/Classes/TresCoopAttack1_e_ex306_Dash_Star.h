#pragma once
#include "CoreMinimal.h"
#include "TresAttackDefinitionBase.h"
#include "WaveOneCollInfo_e_ex310.h"
#include "TresCoopAttack1_e_ex306_Dash_Star.generated.h"

UCLASS(HideDropdown)
class UTresCoopAttack1_e_ex306_Dash_Star : public UTresAttackDefinitionBase {
    GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly)
    int32 m_iMaxAttackCount;
    
    UPROPERTY(EditDefaultsOnly)
    float m_fVelocity;
    
    UPROPERTY(EditDefaultsOnly)
    float m_fTurnSpeed;
    
    UPROPERTY(EditDefaultsOnly)
    float m_fTurnExp;
    
    UPROPERTY(EditDefaultsOnly)
    float m_fCloseDistance;
    
    UPROPERTY(EditDefaultsOnly)
    float m_fForwardDistance;
    
    UPROPERTY(EditDefaultsOnly)
    bool m_bUpdateTargetLoc;
    
    UPROPERTY(EditDefaultsOnly)
    bool m_bHomingForward;
    
    UPROPERTY(EditDefaultsOnly)
    float m_fMaxAvoidDistance;
    
    UPROPERTY(EditDefaultsOnly)
    FWaveOneCollInfo_e_ex310 m_OneCollInfo;
    
    UTresCoopAttack1_e_ex306_Dash_Star();
};

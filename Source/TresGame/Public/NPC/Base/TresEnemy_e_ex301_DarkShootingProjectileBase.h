#pragma once
#include "CoreMinimal.h"
#include "TresProjectileBase.h"
#include "TresEnemy_e_ex301_DarkShootingProjectileBase.generated.h"

UCLASS()
class ATresEnemy_e_ex301_DarkShootingProjectileBase : public ATresProjectileBase {
    GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly)
    TArray<float> m_DistExpList;
    
    ATresEnemy_e_ex301_DarkShootingProjectileBase();
};

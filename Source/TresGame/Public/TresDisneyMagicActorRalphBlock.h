#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TresNotifyInterface.h"
#include "TresActorInterface.h"
#include "ETresRalphBlockKind.h"
#include "TresDisneyMagicActorRalphBlock.generated.h"

class UTresBodyCollComponent;
class UParticleSystem;
class UTresAtkCollComponent;
class UTresStaticMeshComponent;
class ATresDisneyMagicActorRalphBlock;

UCLASS(Blueprintable)
class ATresDisneyMagicActorRalphBlock : public AActor, public ITresNotifyInterface, public ITresActorInterface {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(EditAnywhere)
    TEnumAsByte<ETresRalphBlockKind> m_BlockKind;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UParticleSystem* m_EffAssetExplosion;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UParticleSystem* m_EffAssetDisappear;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Export, meta=(AllowPrivateAccess=true))
    UTresStaticMeshComponent* MyMesh;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Export, meta=(AllowPrivateAccess=true))
    UTresAtkCollComponent* MyAtkColl;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Export, meta=(AllowPrivateAccess=true))
    UTresBodyCollComponent* MyBodyColl;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Export, meta=(AllowPrivateAccess=true))
    UTresStaticMeshComponent* MyPenetrationEffectMesh;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<ATresDisneyMagicActorRalphBlock*> m_ChainBlockList;
    
public:
    ATresDisneyMagicActorRalphBlock();
    UFUNCTION(BlueprintCallable)
    void OnChangeGimmickPause(bool bPause);
    
    
    // Fix for true pure virtual functions not being implemented
};

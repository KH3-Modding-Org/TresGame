#pragma once
#include "CoreMinimal.h"
#include "TresGimmickActor.h"
#include "TresGimmickBxStepBanAsset.generated.h"

class UTresStaticMeshComponent;
class AActor;

UCLASS(Blueprintable, Config=Game)
class ATresGimmickBxStepBanAsset : public ATresGimmickActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Export, meta=(AllowPrivateAccess=true))
    UTresStaticMeshComponent* MyMesh;
    
    ATresGimmickBxStepBanAsset();
    UFUNCTION(BlueprintCallable)
    void SetStepBanAssetOwnerActor(AActor* GimmickOwner);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnChangeStepBanAssetOwner(AActor* GimmickOwner);
    
};

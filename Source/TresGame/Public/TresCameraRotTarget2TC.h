#pragma once
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "TresCameraTargetInfo.h"
#include "TresCameraRotTarget.h"
#include "UObject/NoExportTypes.h"
#include "TresCameraRotTarget2TC.generated.h"

class AActor;
class UObject;
class ATresCameraRotTarget2TC;

UCLASS(Blueprintable)
class ATresCameraRotTarget2TC : public ATresCameraRotTarget {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTresCameraTargetInfo m_TargetInfo2;
    
public:
    ATresCameraRotTarget2TC();
    UFUNCTION(BlueprintCallable)
    static ATresCameraRotTarget2TC* BP_SpawnTresCameraRotTarget2TC(UObject* WorldContextObject, TSubclassOf<ATresCameraRotTarget2TC> CameraClass, const FName CameraName);
    
    UFUNCTION(BlueprintCallable)
    void BP_SetTresCamera2TCDistancePlus(bool bDistancePlus);
    
    UFUNCTION(BlueprintCallable)
    void BP_SetTresCamera2ndTargetParam(AActor* Target2, FVector TargetOffset, FVector TargetLocalOffset, FName TargetBoneName);
    
};

#pragma once
#include "CoreMinimal.h"
#include "TresEnemyEx351SpawnInfoL.h"
#include "TresEnemyEx351FreezeShotSpawnWorker.generated.h"

USTRUCT(BlueprintType)
struct FTresEnemyEx351FreezeShotSpawnWorker {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTresEnemyEx351SpawnInfoL SpawnInfo;
    
    TRESGAME_API FTresEnemyEx351FreezeShotSpawnWorker();
};

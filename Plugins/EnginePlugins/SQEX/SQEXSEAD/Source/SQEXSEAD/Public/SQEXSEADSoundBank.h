// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SQEXSEADSoundBank.generated.h"

class UAssetImportData;

/**
 * 
 */
UCLASS(EditInlineNew, MinimalAPI)
class USQEXSEADSoundBank : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SQEXSEADSoundBank")
	UAssetImportData* AssetImportData;

	FByteBulkData RawAudioData;

	USQEXSEADSoundBank();

	virtual void Serialize(FArchive& Ar) override;
};

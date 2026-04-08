// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundWave.h"
#include "Engine/EngineTypes.h"
#include "SQEXSEAD.h"
#include "ESQEXSEADSoundOutputPort.h"
#include "SQEXSEADSound.generated.h"

class USQEXSEADSoundBank;


/**
 * 
 */
UCLASS(Blueprintable, EditInlineNew, MinimalAPI, hidecategories = (Object))
class USQEXSEADSound : public USoundWave
{
	GENERATED_BODY()
public:
	//UNKNOWN IF THIS WORKS
	//UPROPERTY()
	//TArray<uint8> AudioDataArray;
	//

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SQEXSEADSound")
	bool bUseKohrogiAttenuation;

	UPROPERTY(AssetRegistrySearchable, BlueprintReadWrite, Category = "SQEXSEADSound")
	class USQEXSEADSoundBank* ReferenceBank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SQEXSEADSound")
	int SoundIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SQEXSEADSound")
	bool bOverrideStopFadeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SQEXSEADSound")
	float StopFadeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SQEXSEADSound")
	bool bIsUISound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SQEXSEADSound")
	bool bIgnoreEnginePause;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SQEXSEADSound")
	float PauseFadeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SQEXSEADSound")
	bool bIgnoreAudioVolumeAttenuation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SQEXSEADSound")
	bool bIgnoreObstruction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SQEXSEADSound")
	bool bEnableSEADTracingOcclusion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SQEXSEADSound")
	TEnumAsByte<ECollisionChannel> SEADOcclusionTraceChannel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SQEXSEADSound")
	TEnumAsByte<ESQEXSEADSoundOutputPort::Type> SEADSoundOutputPort;
	
	uint32 bUnk;
	TArray<FName> Platforms;
	FByteBulkData Type;

	FSabMabInfo   Header;
	FByteBulkData RawAudioData;


	virtual void Serialize(FArchive& Ar) override; 

	USQEXSEADSound();
};

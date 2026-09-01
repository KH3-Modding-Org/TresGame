// Fill out your copyright notice in the Description page of Project Settings.

#include "SQEXSEADFactory.h"
#include "AudioDeviceManager.h"
#include "Sound/SoundNodeWavePlayer.h"

#include "PackageTools.h"
#include "Misc/MessageDialog.h"
#include "AssetToolsModule.h"

#define LOCTEXT_NAMESPACE "AtomFactory"

struct FSabMabHeaderSection
{
	FString SectionName;
	uint16 UnknownAt4;
	uint16 UnknownAt6;
	uint32 OffsetInInnerFile;
	uint32 UnknownAtC;
};
struct FMaterialUser
{
	FString User;
	int MaterialIndex;
};
struct FMaterialEntry
{
	int EntryIndex;
	int StreamPosition;
	int MaterialHeaderSize;
	int HeaderPosition;
	uint16 MtrlNumber;
	int ExtraDataOffset;
	int PositionOfOffsetFromMtrlSectionOffset;
	uint32 StreamSize;
	int HcaHeaderSize;
	int HcaStreamStartPosition;
	int HcaStreamSize;
	int NoHcaHeaderSize;
	int TrackEndPosition;
	int NoHcaHeaderExtraDataSize;
	uint32 LocalSectionOffset;
	uint32 LoopStart;
	uint32 LoopEnd;
	uint32 ExtraDataSize;
	uint32 SampleRate;
	uint8 ChannelCount;
	uint8 Codec;
	uint16 ExtraDataId;
	bool IsLooping = LoopEnd > 0;

	uint8 HCAFMTChannelCount;
	int HCAFMTSampleRate;
	uint32 HCAFMTFrameCount;
	uint16 HCAFMTInsertedSamples;
	uint16 HCAFMTAppendedSamples;
	int HCAFMTSampleCount;

	uint16 HCACOMPFrameSize;
	uint8 HCACOMPMinResolution;
	uint8 HCACOMPMaxResolution;
	uint8 HCACOMPTrackCount;
	uint8 HCACOMPChannelConfig;
	uint8 HCACOMPTotalBandCount;
	uint8 HCACOMPBaseBandCount;
	uint8 HCACOMPStereoBandCount;
	uint8 HCACOMPBandsPerHfrGroup;

	uint16 HCACIPHEncryptionType;
};

struct FMusicLayer
{
	int Index;
	int Offset;
	uint8 Version;
	uint8 Flags;
	uint16 Size;
	uint16 MaterialIndex;
	uint16 LoopCount;
	uint32 UnknownAt8;
	uint32 EndPointSample;
};

struct FMusicSlice
{
	int Index;
	uint8 Version;
	uint16 Size;
	int SubTableOffset;
	int Offset;
	FString Name;
	uint16 CustomPointsCount;
	uint32 EntryPointsSample;
	uint32 ExitPointsSample;
	uint32 LoopStart;
	uint32 LoopEnd;
	uint32 MeterCount;
	int NameOffset;
	int NameSize;

	TArray<FMusicLayer> Layers;
};
struct FMusicMode
{
	int Offset;
	uint8 Version;
	uint16 Size;
	int NameOffset;
	uint8 NameSize;
	FString Name;
};

struct FCriWareInfo
{
	int StartAddress;
	int EndAddress;
};

struct FSEADAudioData
{
#define WAV_HEADER_SIZE 44
#define BITS_PER_SAMPLE 16

public:
	bool bIsSab;
	TArray<FSabMabHeaderSection> HeaderSections;
	TArray<FMaterialEntry> Entries;
	TArray<TArray<uint8>> AudioData;


	TArray<FCriWareInfo> HCAArray;
	/*
	bool ReadAudioData(const uint8*& Buffer, const uint8* BufferEnd, TArray<uint8> SabMabDataArray, int32 SabMabDataSize, FString* ErrorMessage = NULL, bool InHeaderDataOnly = false, void** OutFormatHeader = NULL)
	{

		if (SabMabDataArray.GetData() <= 0)
			return false;
		const uint8* SabMabData = SabMabDataArray.GetData();
		int StartBufferOffset = 0; //Automatically Changes
		FString FileID = Uint32ToString(BytesToUint32(SabMabData, StartBufferOffset, false));
		uint8 VersionMain = BytesToUint8(SabMabData, StartBufferOffset);
		uint8 VersionSub = BytesToUint8(SabMabData, StartBufferOffset);
		uint16 HeaderUnknownAt6 = BytesToUint16(SabMabData, StartBufferOffset, false);
		uint8 SectionsCount = BytesToUint8(SabMabData, StartBufferOffset);
		uint8 DescriptorLength = BytesToUint8(SabMabData, StartBufferOffset);
		uint16 HeaderUnknownAtA = BytesToUint16(SabMabData, StartBufferOffset, false);
		uint32 FileSize = BytesToUint32(SabMabData, StartBufferOffset, false);

		int bytesNeededToPad = 16 - DescriptorLength % 16;
		int HeaderSize = 16 + DescriptorLength + bytesNeededToPad;

		if (FileID != "mabf")
		{
			if (FileID == "sabf") { bIsSab = true; }
			else
			{
				if (ErrorMessage) { *ErrorMessage = "FILE UNKNOWN: Invalid Sab/Mab file"; }
				return false;
			}
		}
		int InnerFileStartOffset = 0;
		int Position = InnerFileStartOffset + HeaderSize;
		for (int i = 0; i < SectionsCount; i++)
		{
			FSabMabHeaderSection HeaderSection;
			HeaderSection.SectionName = Uint32ToString(BytesToUint32(SabMabData, Position, false));
			HeaderSection.UnknownAt4 = BytesToUint16(SabMabData, Position, false);
			HeaderSection.UnknownAt6 = BytesToUint16(SabMabData, Position, false);
			HeaderSection.OffsetInInnerFile = BytesToUint32(SabMabData, Position, false);
			HeaderSection.UnknownAtC = BytesToUint32(SabMabData, Position, false);
			HeaderSections.Add(HeaderSection);
		}

		for (int i = 0; i < HeaderSections.Num(); i++)
		{
			if (HeaderSections[i].SectionName == "mtrl")
			{
				int InnerFilePositionOfFirstTracks = 0;
				FSabMabHeaderSection SectionDeclaration = HeaderSections[i];
				int MaterialSectionOffset = InnerFileStartOffset + SectionDeclaration.OffsetInInnerFile;
				int MaterialSectionOffsetOffset = MaterialSectionOffset + 2;
				uint16 EntryAddressesSize = BytesToUint16(SabMabData, MaterialSectionOffsetOffset, false);
				uint16 EntryCount = BytesToUint16(SabMabData, MaterialSectionOffsetOffset, false);
				for (int songEntryIndex = 0; songEntryIndex < EntryCount; songEntryIndex++)
				{
					int positionOfOffsetFromMaterialSectionOffset = MaterialSectionOffset + 16 + songEntryIndex * 4;
					int positionOfOffsetFromMaterialSectionOffsetOffset = positionOfOffsetFromMaterialSectionOffset;
					uint32 localEntryOffset = BytesToUint32(SabMabData, positionOfOffsetFromMaterialSectionOffsetOffset, false);
					if (songEntryIndex == 0) { InnerFilePositionOfFirstTracks = SectionDeclaration.OffsetInInnerFile + localEntryOffset; }
					int EntryOffset = MaterialSectionOffset + localEntryOffset + 5;
					int8 Codec = BytesToUint8(SabMabData, EntryOffset);
					if (Codec == 0) { continue; }
					FMaterialEntry Entry;
					Entry.EntryIndex = songEntryIndex;
					Entry.PositionOfOffsetFromMtrlSectionOffset = positionOfOffsetFromMaterialSectionOffset;
					Entry.LocalSectionOffset = BytesToUint32(SabMabData, Entry.PositionOfOffsetFromMtrlSectionOffset, false);
					Entry.HeaderPosition = MaterialSectionOffset + Entry.LocalSectionOffset;
					int HeaderPositionOffset = Entry.HeaderPosition + 4;
					Entry.ChannelCount = BytesToUint8(SabMabData, HeaderPositionOffset);
					Entry.Codec = BytesToUint8(SabMabData, HeaderPositionOffset);
					Entry.MtrlNumber = BytesToUint16(SabMabData, HeaderPositionOffset, false);
					Entry.SampleRate = BytesToUint32(SabMabData, HeaderPositionOffset, false);
					Entry.LoopStart = BytesToUint32(SabMabData, HeaderPositionOffset, false);
					Entry.LoopEnd = BytesToUint32(SabMabData, HeaderPositionOffset, false);
					Entry.ExtraDataSize = BytesToUint32(SabMabData, HeaderPositionOffset, false);
					Entry.StreamSize = BytesToUint32(SabMabData, HeaderPositionOffset, false);
					Entry.ExtraDataId = BytesToUint16(SabMabData, HeaderPositionOffset, false);
					Entry.ExtraDataOffset = Entry.HeaderPosition + 32;
					Entry.StreamPosition = Entry.ExtraDataOffset + Entry.ExtraDataSize;
					Entry.MaterialHeaderSize = Entry.StreamPosition - Entry.HeaderPosition;
					int ExtraDataOffsetOffset = Entry.ExtraDataOffset + 16 + 6;

					//why is this in big endian wtf?
					int hcaHeaderSizeByteBig = BytesToUint8(SabMabData, ExtraDataOffsetOffset);
					int hcaHeaderSizeByteSmall = BytesToUint8(SabMabData, ExtraDataOffsetOffset);
					Entry.HcaHeaderSize = (uint16)((hcaHeaderSizeByteBig << 8) + hcaHeaderSizeByteSmall);

					Entry.NoHcaHeaderExtraDataSize = Entry.ExtraDataSize - Entry.HcaHeaderSize;
					Entry.HcaStreamStartPosition = Entry.ExtraDataOffset + 16;
					Entry.HcaStreamSize = Entry.HcaHeaderSize + Entry.StreamSize;
					Entry.NoHcaHeaderSize = Entry.HcaStreamStartPosition - Entry.HeaderPosition;
					Entry.TrackEndPosition = Entry.HcaStreamStartPosition + Entry.HcaStreamSize;

					int InitalHCAOffset = 0;
					TArray<uint8> hcaFileBytes = SabMabDataArray;
					FString Signature = ListOfBytesToString(&hcaFileBytes.GetData()[Entry.HcaStreamStartPosition], Entry.HcaStreamStartPosition + 4);
					int StartPositionOffsetInit = Entry.HcaStreamStartPosition + 4;
					uint16 Version = BytesToUint16(hcaFileBytes.GetData(), StartPositionOffsetInit, false);
					uint16 HeaderSize = BytesToUint16(hcaFileBytes.GetData(), StartPositionOffsetInit, false);

					if (Signature != "HCA\0")
					{
						if (ErrorMessage) { *ErrorMessage = "Not a valid HCA file"; }
					}
					int StartPosition = Entry.HcaStreamStartPosition + 8;
					FCriWareInfo CriwareInfo;
					CriwareInfo.StartAddress = StartPosition;
					CriwareInfo.EndAddress = HeaderSize;
					HCAArray.Add(CriwareInfo);
					Entries.Add(Entry);
				}
			}
			else { continue; }
		}

		return true;
	}
	*/
};


USQEXSEADMusic* USQEXSEADFactory::FindSEADMusic(FName FileName, FString PackagePath)
{
	FString FileNameString = FileName.ToString();
	USQEXSEADMusic* FileData = (USQEXSEADMusic*)StaticFindObject(USQEXSEADMusic::StaticClass(), ANY_PACKAGE, *FileNameString);
	if ((FileData == nullptr) && (!PackagePath.IsEmpty())) {
		FString PackageName = PackagePath + "/" + FileNameString;
		UPackage* Pkg = FindPackage(nullptr, *PackageName);
		if (Pkg == nullptr) {
			Pkg = LoadPackage(nullptr, *PackageName, LOAD_None);
		}
		FileData = (USQEXSEADMusic*)StaticFindObject(USQEXSEADMusic::StaticClass(), ANY_PACKAGE, *FileNameString);
	}
	if (FileData == nullptr) {
		UPackage* Pkg = FindPackage(nullptr, *FileNameString);
		if (Pkg == nullptr) {
			Pkg = LoadPackage(nullptr, *FileNameString, LOAD_None);
		}
		FileData = (USQEXSEADMusic*)StaticFindObject(USQEXSEADMusic::StaticClass(), ANY_PACKAGE, *FileNameString);
	}
	if (FileData == nullptr) {
		FString AssetFileName = FileName.ToString() + TEXT(".uasset");
		TArray<FString> AssetFiles;
		FString Content = TEXT("/Content");
		IFileManager::Get().FindFilesRecursive(AssetFiles, *(FGenericPlatformMisc::GameDir() + Content), *AssetFileName, true, false);
		for (FString& AssetPath : AssetFiles) {
			UPackage* Package = LoadPackage(nullptr, *AssetPath, LOAD_None);
		}
		FileData = (USQEXSEADMusic*)StaticFindObject(USQEXSEADMusic::StaticClass(), ANY_PACKAGE, *FileNameString);
	}
	return FileData;
}

USQEXSEADSound* USQEXSEADFactory::FindSEADSound(FName FileName, FString PackagePath)
{
	FString FileNameString = FileName.ToString();
	USQEXSEADSound* FileData = (USQEXSEADSound*)StaticFindObject(USQEXSEADSound::StaticClass(), ANY_PACKAGE, *FileNameString);
	if ((FileData == nullptr) && (!PackagePath.IsEmpty())) {
		FString PackageName = PackagePath + "/" + FileNameString;
		UPackage* Pkg = FindPackage(nullptr, *PackageName);
		if (Pkg == nullptr) {
			Pkg = LoadPackage(nullptr, *PackageName, LOAD_None);
		}
		FileData = (USQEXSEADSound*)StaticFindObject(USQEXSEADSound::StaticClass(), ANY_PACKAGE, *FileNameString);
	}
	if (FileData == nullptr) {
		UPackage* Pkg = FindPackage(nullptr, *FileNameString);
		if (Pkg == nullptr) {
			Pkg = LoadPackage(nullptr, *FileNameString, LOAD_None);
		}
		FileData = (USQEXSEADSound*)StaticFindObject(USQEXSEADSound::StaticClass(), ANY_PACKAGE, *FileNameString);
	}
	if (FileData == nullptr) {
		FString AssetFileName = FileName.ToString() + TEXT(".uasset");
		TArray<FString> AssetFiles;
		FString Content = TEXT("/Content");
		IFileManager::Get().FindFilesRecursive(AssetFiles, *(FGenericPlatformMisc::GameDir() + Content), *AssetFileName, true, false);
		for (FString& AssetPath : AssetFiles) {
			UPackage* Package = LoadPackage(nullptr, *AssetPath, LOAD_None);
		}
		FileData = (USQEXSEADSound*)StaticFindObject(USQEXSEADSound::StaticClass(), ANY_PACKAGE, *FileNameString);
	}
	return FileData;
}





USQEXSEADFactory::USQEXSEADFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Formats.Add(TEXT("mab;MAB Data"));
	Formats.Add(TEXT("sab;SAB Data"));
	bCreateNew = false;
	bEditAfterNew = true;
	bEditorImport = true;
	SupportedClass = USQEXSEADMusic::StaticClass();
}
static bool bSoundFactorySuppressImportOverwriteDialog = false;
UObject* USQEXSEADFactory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	TArray<UAudioComponent*> ComponentsToRestart;
	FAudioDeviceManager* AudioDeviceManager = GEngine->GetAudioDeviceManager();

	bSoundFactorySuppressImportOverwriteDialog = false;

	TArray<uint8> RawData;
	RawData.Empty(BufferEnd - Buffer);
	RawData.AddUninitialized(BufferEnd - Buffer);
	FMemory::Memcpy(RawData.GetData(), Buffer, RawData.Num());

	FString ErrorMessage;
	Warn->Logf(ELogVerbosity::Error, TEXT("Unable to read file '%s' _ %d"), Type, _tcscmp(Type, L"mab"));
	FSabMabInfo FileInfo;

	if (_tcscmp(Type, L"mab") == 0 || _tcscmp(Type, L"sab") == 0) // Got mab/sab file, no need to do anything extra, just store it inside RawAudioData
	{
		if (FileInfo.ReadSabMabInfo(RawData.GetData(), RawData.Num(), &ErrorMessage))
		{
			/*if (*FileInfo.pBitsPerSample != 16)
			{
				Warn->Logf(ELogVerbosity::Error, TEXT("Currently, only 16 bit Sab/Mab files are supported (%s)."), *Name.ToString());
				FEditorDelegates::OnAssetPostImport.Broadcast(this, nullptr);
				return nullptr;
			}*/

			Warn->Logf(ELogVerbosity::Error, TEXT("Unable to read Sab/Mab file '%s' - \"%s\""), *Name.ToString(), *ErrorMessage);
			Warn->Logf(ELogVerbosity::Error, TEXT("Header Chunk - numChunks: '%s'"), *FString::FromInt(FileInfo.HeaderChunk.numChunks));

			for (int i = 0; i < FileInfo.TableElementChunk.Num(); i++)
			{
				Warn->Logf(ELogVerbosity::Error, TEXT("Header Section - SectionName: '%s'"), *Uint32ToString(FileInfo.TableElementChunk[i].id)); 
			}
			/*
			for (int i = 0; i < FileInfo.Entries.Num(); i++)
			{
				/*
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - Entry Index: '%s'"), *FString::FromInt(FileInfo.Entries[i].EntryIndex));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - Channel Count: '%s'"), *FString::FromInt(FileInfo.Entries[i].ChannelCount));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - Codec: '%s'"), *FString::FromInt(FileInfo.Entries[i].Codec));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - ExtraDataId: '%s'"), *FString::FromInt(FileInfo.Entries[i].ExtraDataId));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - ExtraDataOffset: '%s'"), *FString::FromInt(FileInfo.Entries[i].ExtraDataOffset));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - ExtraDataSize: '%s'"), *FString::FromInt(FileInfo.Entries[i].ExtraDataSize));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - HcaHeaderSize: '%s'"), *FString::FromInt(FileInfo.Entries[i].HcaHeaderSize));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - HcaStreamSize: '%s'"), *FString::FromInt(FileInfo.Entries[i].HcaStreamSize));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - HcaStreamStartPosition: '%s'"), *FString::FromInt(FileInfo.Entries[i].HcaStreamStartPosition));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - HeaderPosition: '%s'"), *FString::FromInt(FileInfo.Entries[i].HeaderPosition));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - IsLooping: '%s'"), *FString::FromInt(FileInfo.Entries[i].IsLooping));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - LocalSectionOffset: '%s'"), *FString::FromInt(FileInfo.Entries[i].LocalSectionOffset));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - LoopStart: '%s'"), *FString::FromInt(FileInfo.Entries[i].LoopStart));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - LoopEnd: '%s'"), *FString::FromInt(FileInfo.Entries[i].LoopEnd));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - MaterialHeaderSize: '%s'"), *FString::FromInt(FileInfo.Entries[i].MaterialHeaderSize));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - MtrlNumber: '%s'"), *FString::FromInt(FileInfo.Entries[i].MtrlNumber));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - NoHcaHeaderExtraDataSize: '%s'"), *FString::FromInt(FileInfo.Entries[i].NoHcaHeaderExtraDataSize));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - NoHcaHeaderSize: '%s'"), *FString::FromInt(FileInfo.Entries[i].NoHcaHeaderSize));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - PositionOfOffsetFromMtrlSectionOffset: '%s'"), *FString::FromInt(FileInfo.Entries[i].PositionOfOffsetFromMtrlSectionOffset));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - SampleRate: '%s'"), *FString::FromInt(FileInfo.Entries[i].SampleRate));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - StreamPosition: '%s'"), *FString::FromInt(FileInfo.Entries[i].StreamPosition));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - StreamSize: '%s'"), *FString::FromInt(FileInfo.Entries[i].StreamSize));
				Warn->Logf(ELogVerbosity::Error, TEXT("Material Entry - TrackEndPosition: '%s'"), *FString::FromInt(FileInfo.Entries[i].TrackEndPosition));
			}

			for (int i = 0; i < FileInfo.MusicEntries.Num(); i++)
			{
				Warn->Logf(ELogVerbosity::Error, TEXT("Music Entry - Name: '%s'"), *FileInfo.MusicEntries[i].Name);
				for (int z = 0; z < FileInfo.MusicEntries[i].Slices.Num(); z++)
				{
					Warn->Logf(ELogVerbosity::Error, TEXT("Music Slice - Name: '%s'"), *FileInfo.MusicEntries[i].Slices[z].Name);
				}
				for (int z = 0; z < FileInfo.MusicEntries[i].Modes.Num(); z++)
				{
					Warn->Logf(ELogVerbosity::Error, TEXT("Music Modes - Name: '%s'"), *FileInfo.MusicEntries[i].Modes[z].Name);
				}
			}

			for (int i = 0; i < FileInfo.Instruments.Num(); i++)
			{
				Warn->Logf(ELogVerbosity::Error, TEXT("Instrument - Name: '%s'"), *FileInfo.Instruments[i].Name);
			}
			*/
		}
		else
		{
			Warn->Logf(ELogVerbosity::Error, TEXT("Unable to read Sab/Mab file '%s' - \"%s\""), *Name.ToString(), *ErrorMessage);
			FEditorDelegates::OnAssetPostImport.Broadcast(this, nullptr);
			return nullptr;
		}
	}
	else if (_tcscmp(Type, L"hca") == 0) // Got HCA, need to serialize mab/sab header and then append the HCA raw buffer onto it
	{

	}
	else if (_tcscmp(Type, L"wav") == 0) // Got WAV, need to serialize mab/sab header and then encode it into HCA
	{

	}
	USQEXSEADMusic* MABAsset = NewObject<USQEXSEADMusic>(InParent, Name, Flags);

	//MABAsset->Platforms.Add(FName(TEXT("Windows")));
	MABAsset->Header = FileInfo;

	//MABAsset->Platform = "Windows";
	//strlen(MABAsset->Platforms[0].ToString);

	/*
	MABAsset->Type.Lock(LOCK_READ_WRITE);
	void* LockedDataStr = MABAsset->Type.Realloc(8);
	FMemory::Memcpy(LockedDataStr, Buffer, 6);
	MABAsset->Type.Unlock();
	*/

	MABAsset->bUnk = 1;
	MABAsset->RawAudioData.Lock(LOCK_READ_WRITE);
	void* LockedData = MABAsset->RawAudioData.Realloc(BufferEnd - Buffer);
	FMemory::Memcpy(LockedData, Buffer, BufferEnd - Buffer);
	MABAsset->RawAudioData.Unlock();


	//SQEX Bypass


	//MABAsset->bProcedural = true;


	//MABAsset->bCanProcessAsync = true;
	//MABAsset->bStreaming = true;


	//MABAsset->DecompressionType = DTYPE_Procedural; //DTYPE_Procedural


	//MABAsset->HasCompressedData = false;
	//

	MABAsset->AssetImportData->Update(CurrentFilename);
	MABAsset->InvalidateCompressedData();

	/*
	FByteBulkData* BulkData = &MABAsset->CompressedFormatData.GetFormat(FName("None"));
	BulkData->Lock(LOCK_READ_WRITE);
	FMemory::Memmove(BulkData->Realloc(RawData.Num()), RawData.GetData(), RawData.Num());
	BulkData->Unlock();
	*/


	//MABAsset->RawData.Lock(LOCK_READ_WRITE);
	//void* LockedData = MABAsset->RawData.Realloc(BufferEnd - Buffer);
	//FMemory::Memcpy(LockedData, Buffer, BufferEnd - Buffer);
	//MABAsset->RawData.Unlock();

	//RAW PCM DATA INFO
	//MABAsset->RawPCMDataSize = FileInfo.SampleDataSize;
	//MABAsset->RawPCMData = static_cast<uint8*>(FMemory::Malloc(BufferEnd - Buffer));
	//FMemory::Memcpy(MABAsset->RawPCMData, Buffer, BufferEnd - Buffer);
	//



	//MABAsset->CompressedFormatData = *(reinterpret_cast<FFormatContainer*> (RawData.GetData()));

	//int32 DurationDiv = *FileInfo.pChannels * *FileInfo.pBitsPerSample * *FileInfo.pSamplesPerSec;

	/*MABAsset->DecompressionType = EDecompressionType::DTYPE_Procedural;
	MABAsset->SoundGroup = ESoundGroup::SOUNDGROUP_Default;
	MABAsset->NumChannels = *FileInfo.pChannels;
	MABAsset->Duration = *FileInfo.pSabMabDataSize * 8.0f / DurationDiv;
	MABAsset->RawPCMDataSize = FileInfo.SampleDataSize;
	MABAsset->SampleRate = *FileInfo.pSamplesPerSec;
	MABAsset->InvalidateCompressedData();*/

	//MABAsset->RawData.Lock(LOCK_READ_WRITE);

	//Entry.NoHcaHeaderSize = Entry.HcaStreamStartPosition - Entry.HeaderPosition;
	//Entry.TrackEndPosition = Entry.HcaStreamStartPosition + Entry.HcaStreamSize;

	//void* LockedData = MABAsset->RawData.Realloc(BufferEnd - Buffer);
	//FMemory::Memcpy(LockedData, Buffer, BufferEnd - Buffer);

	/*MABAsset->RawPCMData = (uint8*)FMemory::Malloc(BufferEnd - Buffer);
	FMemory::Memcpy(MABAsset->RawPCMData, Buffer, BufferEnd - Buffer);*/

	//MABAsset->RawData.Unlock();


	/*if (DurationDiv)
	{
		//MABAsset->Duration = *FileInfo.pSabMabDataSize * 8.0f / DurationDiv;
		MABAsset->Duration = (FileInfo.SampleDataSize * 8.0f / DurationDiv) * 10000;
	}
	else { MABAsset->Duration = 0.0f; }*/

	//MABAsset->Duration = FileInfo.Entries[0].NoHcaHeaderSize / FileInfo.Entries[0].SampleRate;
	MABAsset->Duration = 72.837563f;

	//MABAsset->bLooping = FileInfo.Entries[0].IsLooping;
	//MABAsset->SampleRate = FileInfo.Entries[0].SampleRate;
	//MABAsset->NumChannels = FileInfo.Entries[0].ChannelCount;
	MABAsset->Volume = 0.48;

	FEditorDelegates::OnAssetPostImport.Broadcast(this, MABAsset);
	for (int32 ComponentIndex = 0; ComponentIndex < ComponentsToRestart.Num(); ++ComponentIndex) { ComponentsToRestart[ComponentIndex]->Play(); }
	return MABAsset;
}
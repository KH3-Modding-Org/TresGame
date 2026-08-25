// Fill out your copyright notice in the Description page of Project Settings.

#include "ScaleformUI/ScaleformUIEd/Public/ScaleformUI_Factory.h"

#include "AssetTypeCategories.h"
#include "FileManager.h"
#include "Package.h"
#include "PackageName.h"
#include "Paths.h"
#include "SwfMovie.h"

UScaleformUI_Factory::UScaleformUI_Factory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Formats.Add(TEXT("swf;SWF Movie"));
	Formats.Add(TEXT("gfx;SWF Movie (Stripped)"));
	bEditorImport = true;
	SupportedClass = USwfMovie::StaticClass();
}

UObject* UScaleformUI_Factory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	USwfMovie* ImportedAsset = NewObject<USwfMovie>(InParent, Name, Flags);
	ImportedAsset->bUseGFxExport = true;
	ImportedAsset->bSetSRGBOnImportedTextures = false;
	ImportedAsset->TextureRescale = FlashTextureRescale::FlashTextureScale_Mult4;
	ImportedAsset->bPackTextures = true;
	ImportedAsset->PackTextureSize = 1024;
	ImportedAsset->TextureFormat = "TGA";
	FString FilePath = FPaths::GetPath(CurrentFilename);
	FPaths::MakePathRelativeTo(FilePath, *FPaths::GameDir());
	ImportedAsset->SourceFile = FilePath + "/" + FPaths::GetCleanFilename(CurrentFilename);
	ImportedAsset->SourceFileTimestamp = IFileManager::Get().GetTimeStamp(*UFactory::CurrentFilename).ToString();
	ImportedAsset->RawData.Empty(BufferEnd - Buffer);
	ImportedAsset->RawData.AddUninitialized(BufferEnd - Buffer);
	FMemory::Memcpy(ImportedAsset->RawData.GetData(), Buffer, ImportedAsset->RawData.Num());
	return ImportedAsset;
}
bool UScaleformUI_Factory::CanReimport(UObject* Obj, TArray<FString>& OutFilenames)
{
	USwfMovie* ImportedAsset = Cast<USwfMovie>(Obj);
	if (ImportedAsset)
	{
		OutFilenames.Add(FPaths::ConvertRelativePathToFull(FPaths::GameDir(), ImportedAsset->SourceFile));
		return true;
	}
	return false;
}
void UScaleformUI_Factory::SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths)
{
	USwfMovie* ImportedAsset = Cast<USwfMovie>(Obj);
	if (ImportedAsset && ensure(NewReimportPaths.Num() == 1))
	{
		FString FilePath = FPaths::GetPath(NewReimportPaths[0]);
		FPaths::MakePathRelativeTo(FilePath, *FPaths::GameDir());
		ImportedAsset->SourceFile = FilePath + "/" + FPaths::GetCleanFilename(NewReimportPaths[0]);
	}
}
EReimportResult::Type UScaleformUI_Factory::Reimport(UObject* Obj)
{
	USwfMovie* ImportedAsset = Cast<USwfMovie>(Obj);
	if (!ImportedAsset) { return EReimportResult::Failed; }
	const FString Filename = FPaths::ConvertRelativePathToFull(FPaths::GameDir(), ImportedAsset->SourceFile);
	bool OutCanceled = false; 
	TArray<FString> OldRef = ImportedAsset->ReferencedAssetNames;
	if (FPaths::GetExtension(Filename).Equals(TEXT("gfx"), ESearchCase::IgnoreCase) || FPaths::GetExtension(Filename).Equals(TEXT("swf"), ESearchCase::IgnoreCase))
	{
		if (ImportObject(ImportedAsset->GetClass(), ImportedAsset->GetOuter(), *ImportedAsset->GetName(), RF_Public | RF_Standalone, Filename, nullptr, OutCanceled) != nullptr)
		{
			ImportedAsset->Modify();
			ImportedAsset->MarkPackageDirty();
			ImportedAsset->SourceFileTimestamp = IFileManager::Get().GetTimeStamp(*UFactory::CurrentFilename).ToString();
			ImportedAsset->ReferencedAssetNames = OldRef;
			
			return EReimportResult::Succeeded;
		}
		else
		{
			if (OutCanceled) { UE_LOG(LogTemp, Warning, TEXT("SWF Movie Import Canceled!")); }
			else { UE_LOG(LogTemp, Warning, TEXT("SWF Movie Import Failed!")); }
			return EReimportResult::Failed;
		}
	}
	else { return EReimportResult::Failed; }
}
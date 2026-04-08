#include "SQEXSEADSound.h"
#include "SQEXSEADSoundBank.h"

void USQEXSEADSound::Serialize(FArchive & Ar)
{
	Super::Serialize(Ar);

	//if (!this->NumChannels)
	//{}

	Ar << bUnk;

	BYTE v30;
	int32 v36;
	BYTE a1;
	int32 a2;
	short a3;

	a1 = 2;
	v30 = 0;
	v36 = 0;
	a3 = 0;
	a2 = RawAudioData.GetBulkDataSizeOnDisk();

	// Serialize 1
	//Ar->Serialize(Ar, a1, 4);
	Ar << a1;

	// Serialize 2
	//Ar->Serialize(Ar, &v30, 4);
	Ar << v30;

	// Serialize 3
	//Ar->Serialize(Ar, &v31, 4);
	Ar << v30;

	// Serialize 4
	//Ar->Serialize(Ar, &v32, 4);
	Ar << v30;

	// Serialize 5 aka the one that serializes @áG ???
	//Ar->Serialize(Ar, &v33, 4);
	Ar << a2;

	// Serialize 6
	//Ar->Serialize(Ar, &v34, 4);
	Ar << v30;

	// Serialize 7
	//Ar->Serialize(Ar, &v35, 4);
	Ar << v30;

	// Serialize 8
	//FUntypedBulkData::Serialize(v18, Ar, a3, -1);
	Ar << v36;

	// Serialize 9
	//Ar->Serialize(Ar, a1, 4);
	Ar << v36;

	// Serialize 10
	//Ar->Serialize(Ar, a1 + 30, 4);
	Ar << v36;

	// Serialize 11
	//Ar->Serialize(Ar, a1 + 60, 4);
	Ar << a3;

	// Serialize 12
	//Ar->Serialize(Ar, a1 + 90, 4);
	Ar << v30;

	// Serialize 13
	//Ar->Serialize(Ar, a1 + 120, 4);
	Ar << v30;

	// Serialize 14
	//Ar->Serialize(Ar, a1 + 150, 4);
	Ar << v30;

	// Serialize 15
	//Ar->Serialize(Ar, a1 + 180, 4);
	Ar << v30;

	// Serialize 16
	/*
	if (a1[30] > 0)
		FUntypedBulkData::Serialize(a1 + 2, Ar, a3, -1);
	if (a1[60] > 0)
		FUntypedBulkData::Serialize(a1 + 32, Ar, a3, -1);
	if (*v22 > 0)
		FUntypedBulkData::Serialize(a1 + 62, Ar, a3, -1);
	if (a1[120] > 0)
		FUntypedBulkData::Serialize(a1 + 92, Ar, a3, -1);
	if (a1[150] > 0)
		FUntypedBulkData::Serialize(a1 + 122, Ar, a3, -1);
	if (*v26 > 0)
		FUntypedBulkData::Serialize(a1 + 152, Ar, a3, -1);
		*/
	

	Header.Serialize(Ar, this);
	//RawAudioData.Serialize(Ar, this);

}

void USQEXSEADSoundBank::Serialize(FArchive & Ar)
{
	Super::Serialize(Ar);

	//if (!this->NumChannels)
	//{}
	

	BYTE v30;
	int32 v36;
	BYTE a1;
	int32 a2;
	short a3;

	a1 = 2;
	v30 = 0;
	v36 = 0;
	a3 = 0;
	a2 = RawAudioData.GetBulkDataSizeOnDisk();

	// Serialize 1
	//Ar->Serialize(Ar, a1, 4);
	Ar << a1;

	// Serialize 2
	//Ar->Serialize(Ar, &v30, 4);
	Ar << v30;

	// Serialize 3
	//Ar->Serialize(Ar, &v31, 4);
	Ar << v30;

	// Serialize 4
	//Ar->Serialize(Ar, &v32, 4);
	Ar << v30;

	// Serialize 5 aka the one that serializes @áG ???
	//Ar->Serialize(Ar, &v33, 4);
	Ar << a2;

	// Serialize 6
	//Ar->Serialize(Ar, &v34, 4);
	Ar << v30;

	// Serialize 7
	//Ar->Serialize(Ar, &v35, 4);
	Ar << v30;

	// Serialize 8
	//FUntypedBulkData::Serialize(v18, Ar, a3, -1);
	Ar << v36;

	// Serialize 9
	//Ar->Serialize(Ar, a1, 4);
	Ar << v36;

	// Serialize 10
	//Ar->Serialize(Ar, a1 + 30, 4);
	Ar << v36;

	// Serialize 11
	//Ar->Serialize(Ar, a1 + 60, 4);
	Ar << a3;

	// Serialize 12
	//Ar->Serialize(Ar, a1 + 90, 4);
	Ar << v30;

	// Serialize 13
	//Ar->Serialize(Ar, a1 + 120, 4);
	Ar << v30;

	// Serialize 14
	//Ar->Serialize(Ar, a1 + 150, 4);
	Ar << v30;

	// Serialize 15
	//Ar->Serialize(Ar, a1 + 180, 4);
	Ar << v30;

	// Serialize 16
	/*
	if (a1[30] > 0)
		FUntypedBulkData::Serialize(a1 + 2, Ar, a3, -1);
	if (a1[60] > 0)
		FUntypedBulkData::Serialize(a1 + 32, Ar, a3, -1);
	if (*v22 > 0)
		FUntypedBulkData::Serialize(a1 + 62, Ar, a3, -1);
	if (a1[120] > 0)
		FUntypedBulkData::Serialize(a1 + 92, Ar, a3, -1);
	if (a1[150] > 0)
		FUntypedBulkData::Serialize(a1 + 122, Ar, a3, -1);
	if (*v26 > 0)
		FUntypedBulkData::Serialize(a1 + 152, Ar, a3, -1);
		*/

		// Header.Serialize(Ar, this);
	RawAudioData.Serialize(Ar, this);

}

void FSabMabInfo::Serialize(FArchive & Ar, UObject* Owner)
{

	// mabf/sabf header
	BYTE id[5];
	//id.AddUninitialized(5);
	//StringToBytes("nvtjd", id, 5);
	uint8 zero = 0;
	FMemory::Memcpy(&id,"music", 5);


	//This should display MABF or SABF
	Ar << HeaderChunk.id;


	Ar << HeaderChunk.version; //Displays the Main version of the Mab/Sab (Usually Displays 2)
	Ar << HeaderChunk.flgs; //Displays the Sub version of the Mab/Sab. Can display 0, 1, or 2 (Mab/Sab have version 2.0, 2.1, 2.2)
	Ar << HeaderChunk.structSize; // ??? Need Documenting | Displays 0x10 which coincides with the length of the header
	Ar << HeaderChunk.numChunks; // Amount of Sections to loop through
	Ar << HeaderChunk.reserved2; // Length of Descriptor
	Ar << HeaderChunk.number; // ??? Need Documenting | Always FF FF so likely allocation for the File Size
	Ar << HeaderChunk.fileSize; // Size of the Mab/Sab file

	// Ar << HeaderChunk.name;
	Ar.Serialize(id,5);

	for (int i = 0; i < 11; i++)
	{
		Ar << zero;
	}

	// musc header
	
	for (int i = 0; i < TableElementChunk.Num(); i++)
	{
		Ar << TableElementChunk[i].id;
		Ar << TableElementChunk[i].version;
		Ar << TableElementChunk[i].reserved;
		Ar << TableElementChunk[i].structSize;
		Ar << TableElementChunk[i].offset;
		Ar << TableElementChunk[i].reserved2;
	}

	// Serialize MAB/Music (musc) Chunk
	/*
	MAB_CHUNK_HEADER a = MAB_CHUNK_HEADER::MAB_CHUNK_HEADER();
	Ar << a;
	*/

	for (int i = 0; i < MabEntries.Num(); i++)
	{
		Ar << MabEntries[i];
	}
	// Serialize Instruments (inst) Chunk
	/*
	MAB_INSTRUMENT_CHUNK_HEADER b = MAB_INSTRUMENT_CHUNK_HEADER::MAB_INSTRUMENT_CHUNK_HEADER();
	Ar << b;
	*/

	for (int i = 0; i < InstEntries.Num(); i++)
	{
		Ar << InstEntries[i];
	}
	// Serialize Materials (mtrl) Chunk
	/*
	SABMATERIALCHUNKHEADER c = SABMATERIALCHUNKHEADER::SABMATERIALCHUNKHEADER();
	Ar << c;
	*/

	for (int i = 0; i < MtrlEntries.Num(); i++)
	{
		Ar << MtrlEntries[i];
	}
}
/*
FSabMabInfo::FSabMabInfo()
{
	;
}
*/

USQEXSEADSound::USQEXSEADSound() {
	this->bUseKohrogiAttenuation = false;
	this->ReferenceBank = NULL;
	this->SoundIndex = 0;
	this->bOverrideStopFadeTime = false;
	this->StopFadeTime = 0.50f;
	this->bIsUISound = false;
	this->bIgnoreEnginePause = false;
	this->PauseFadeTime = 0.00f;
	this->bIgnoreAudioVolumeAttenuation = false;
	this->bIgnoreObstruction = false;
	this->bEnableSEADTracingOcclusion = false;
	this->SEADOcclusionTraceChannel = ECC_Visibility;
	this->SEADSoundOutputPort = ESQEXSEADSoundOutputPort::AUTO;
}
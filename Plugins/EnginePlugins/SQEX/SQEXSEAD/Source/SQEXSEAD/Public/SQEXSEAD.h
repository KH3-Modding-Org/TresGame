#pragma once

#include "CoreMinimal.h"

static uint8 BytesToUint8(const uint8* Data, int index)
{
	uint8 value = 0;
	value |= Data[index];
	return value;
}
static uint16 BytesToUint16(const uint8* Data, int index)
{
	uint32 value = 0;
	value |= Data[index + 1] << 8;
	value |= Data[index];
	return value;
}
static int16 BytesToInt16(const uint8* Data, int index)
{
	int32 value = 0;
	value |= Data[index + 1] << 8;
	value |= Data[index];
	return value;
}
static uint32 BytesToUint32(const uint8* Data, int index)
{
	uint32 value = 0;
	value |= Data[index + 3] << 24;
	value |= Data[index + 2] << 16;
	value |= Data[index + 1] << 8;
	value |= Data[index];
	return value;
}
static float BytesToFloat(const uint8* Data, int index)
{
	uint32 value = 0;
	float val = 0;
	value |= Data[index + 3] << 24;
	value |= Data[index + 2] << 16;
	value |= Data[index + 1] << 8;
	value |= Data[index];
	FMemory::Memcpy(&val, &value, sizeof(val));
	return val;
}
static FString Uint8ToString(uint8 Input)
{
	uint8 Byte1 = Input;
	FString CombinedString = BytesToString(&Byte1, 1);
	CombinedString[0] = CombinedString[0] - 1;
	return CombinedString;
}
static FString Uint16ToString(uint16 Input)
{
	uint8 Byte1 = Input;
	uint8 Byte2 = Input >> 8;
	FString CombinedString = BytesToString(&Byte1, 1) += BytesToString(&Byte2, 1);
	CombinedString[0] = CombinedString[0] - 1;
	CombinedString[1] = CombinedString[1] - 1;
	return CombinedString;
}
static FString Uint32ToString(uint32 Input)
{
	uint8 Byte1 = Input;
	uint8 Byte2 = Input >> 8;
	uint8 Byte3 = Input >> 16;
	uint8 Byte4 = Input >> 24;
	FString CombinedString = BytesToString(&Byte1, 1) += BytesToString(&Byte2, 1) += BytesToString(&Byte3, 1) += BytesToString(&Byte4, 1);
	for (int i = 0; i < CombinedString.Len(); i++) { CombinedString[i] = CombinedString[i] - 1; }
	return CombinedString;
}
static FString ListOfBytesToString(const uint8* Input, int Count)
{
	FString NewString = BytesToString(Input, Count);
	for (int i = 0; i < NewString.Len(); i++) { NewString[i] = NewString[i] - 1; }
	return NewString;
}

// FastHCADecoder

struct stHeader {
	unsigned int hca;              // 'HCA'
	unsigned short version;  
	unsigned short dataOffset;     
};
struct stFormat {
	unsigned int fmt;              // 'fmt'
	unsigned short channelCount;
	unsigned short samplingRate;
	unsigned int blockCount;       
	unsigned short muteHeader;     
	unsigned short muteFooter;     
};
struct stCompress {
	unsigned int comp;             // 'comp'
	unsigned short blockSize;      
	unsigned char r01;             
	unsigned char r02;             
	unsigned char r03;             
	unsigned char r04;             
	unsigned char r05;             
	unsigned char r06;             
	unsigned char r07;             
	unsigned char r08;             
	unsigned char reserve1;        
	unsigned char reserve2;        
};
struct stDecode {
	unsigned int dec;              // 'dec'
	unsigned short blockSize;      
	unsigned char r01;             
	unsigned char r02;             
	unsigned char count1;          
	unsigned char count2;          
	unsigned char r03 : 4;         
	unsigned char r04 : 4;         
	unsigned char enableCount2;    
};
struct stVBR {
	unsigned int vbr;              // 'vbr'
	unsigned short r01;            
	unsigned short r02;            
};
struct stATH {
	unsigned int ath;              // 'ath'
	unsigned short type;
};
struct stLoop {
	unsigned int loop;             // 'loop'
	unsigned int start;            
	unsigned int end;              
	unsigned short count;          
	unsigned short r01;            
};
struct stCipher {
	unsigned int ciph;             // 'ciph'
	unsigned short type;
};
struct stRVA {
	unsigned int rva;              // 'rva'
	float volume;                  
};
struct stComment {
	unsigned int comm;             // 'comm'
	unsigned char len;             
								   
};
struct stPadding {
	unsigned int pad;              // 'pad'
};

struct SABFILEHEADER
{
	uint32 id;
	uint8 version;
	uint8 flgs;
	uint16 structSize;
	uint8 numChunks;
	uint8 reserved2;
	uint16 number;
	unsigned int fileSize;
	uint32 name;
};

// SOUND HEADER (snd)

struct SABSOUNDSEQUENCEINFO
{
	uint8 version;
	uint8 reserved;
	uint16 structSize;
	uint16 sequenceIndex;
	uint16 sequenceID;
	unsigned int reserved3[2];
};

struct SABSOUNDSWITCHPARAM
{
	uint8 version;
	uint8 attachParamNamelen;
	uint16 structSize;
	unsigned int reserved2[3];
};

struct SABSOUNDZEROONEPARAM_STEPLIMIT
{
	float up;
	float down;
};

union SABSOUNDZEROONEPARAM_SLOPEPARAM
{
	unsigned int paddin[4];
	SABSOUNDZEROONEPARAM_STEPLIMIT stepLimit;
};

struct SABSOUNDZEROONEPARAM
{
	uint8 version;
	uint8 slopeType;
	uint16 structSize;
	int reserved2[3];
	SABSOUNDZEROONEPARAM_SLOPEPARAM slopeParam;
};

struct SABSOUNDHEADER
{
	uint8 version;
	uint8 work;
	uint16 structSize;
	uint8 type;
	uint8 numSequences;
	uint8 category;
	uint8 priority;
	uint16 number;
	uint8 startMacro;
	uint8 stopMacro;
	float volume;
	unsigned int cycleIntervalLow;
	unsigned int cycleIntervalHigh;
	uint8 cycleMaxPlayGroups;
	uint8 flgs;
	uint16 sequenceOffset;
	float audibleRange;
	uint8 output;
	uint8 distanceAttenuationCurve;
	uint8 port;
	uint8 reserved2;
	float playLength;
	float interiorFactor;
	float innerRange;
	char auxSendBusses[4];
	float auxSendVolumes[4];
	char numAuxSends;
	uint8 numEffects;
	char reserved4[2];
	float dopplerFactor;
	unsigned int reserved5;
	char name[16];
};


struct SABSOUNDCHUNKHEADER
{
	uint8 version;
	uint8 reserved;
	uint16 structSize;
	uint16 numSounds;
	uint16 reserved2;
	unsigned int reserved3[2];
	SABSOUNDZEROONEPARAM b;
	SABSOUNDHEADER a;
	SABSOUNDSWITCHPARAM c;
	SABSOUNDSEQUENCEINFO d;
};


// MUSIC HEADER (musc)

struct MAB_END_METHOD_FADEOUT
{
	float time;
	uint8 curveType;
	uint8 reserved[3];
	unsigned int reserved2[2];
};

struct MAB_END_METHOD_SECTION
{
	uint8 index;
	uint8 reserved[3];
	unsigned int reserved2[3];
};

struct MAB_END_METHOD_REVERB
{
	float reverbInTime;
	float fadeOutTime;
	uint8 sendIndex;
	uint8 reserved[3];
	unsigned int reserved2;
};

union MAB_END_METHOD_DETAIL
{
	MAB_END_METHOD_FADEOUT fadeout;
	MAB_END_METHOD_SECTION section;
	MAB_END_METHOD_REVERB reverb;
};

struct MAB_END_METHOD
{
	uint8 version;
	uint8 type;
	uint16 structSize;
	uint16 number;
	uint16 reserved;
	unsigned int reserved2[2];
	MAB_END_METHOD_DETAIL detail;
};


struct MAB_METER_HEADER_ORIGIN
{
	uint8 unitPerBeat;
	uint8 unitPerBar;
};

struct MAB_METER_HEADER_CONTINUOUS
{
	uint8 startBeat;
	uint8 startUnit;
};

union MAB_METER_HEADER_DETAIL
{
	MAB_METER_HEADER_ORIGIN origin;
	MAB_METER_HEADER_CONTINUOUS continuous;
	uint16 reserved;
};

struct MAB_METER_HEADER
{
	uint8 version;
	uint8 flgs;
	uint16 structSize;
	uint16 detail; // MAB_METER_HEADER_DETAIL
	uint16 startBar;
	float tempo;
	unsigned int startSample;
};




struct MAB_LAYER_HEADER
{
	uint8 version;
	uint8 flgs;
	uint16 structSize;
	uint16 materialIndex;
	uint16 loopCnt;
	unsigned int offset;
	unsigned int endPoint;
};

struct MAB_MUSIC_HEADER
{
	uint8 version;
	uint8 output;
	uint16 structSize;
	uint8 numSections;
	uint8 numModes;
	uint8 category;
	uint8 priority;
	uint16 number;
	uint8 flgs;
	uint8 distanceAttenuationCurve;
	float interiorFactor;
	char name_v8[16];
	float audibleRange;
	float innerRange;
	float volume;
	uint32 auxSendBusses;
	float auxSendVolumes[4];
	char numAuxSends;
	uint8 numEndMethods;
	uint8 numStartMethods;
	uint8 numZeroOnes;
	unsigned int sampleRate;
	uint8 namelen;
	uint8 port;
	uint16 reserved;
	float playLength;
	uint8 reserved2[16];
};

struct MAB_TIMING
{
	uint16 bar;
	uint8 beat;
	uint8 unit;
};

struct MAB_SECTION_HEADER
{
	uint8 version;
	uint8 number;
	uint16 structSize;
	uint8 namelen;
	uint8 numLayers;
	uint16 numCustomPoints;
	unsigned int entryPoint;
	unsigned int exitPoint;
	unsigned int loopStart;
	unsigned int loopEnd;
	uint16 numMeters;
	uint16 loopStartMeterIndex;
	int16 transitionEffectIndex;
	int16 reserved;
	uint8 syncType;
	uint8 fadeCurveType;
	char nextSectionIndex;
	char previousSectionIndex;
	float fadeOutTime;
	float fadeOutOffset;
	uint32 endTiming;
	float volume;
	uint32 loopStartTiming;
	float fadeInTime;
	float fadeInOffset;
};

struct MAB_MODE_PARAM
{
	uint8 version;
	uint8 reserved;
	uint16 structSize;
	float reserved2[3];
	float layerVolumes[8];
};

struct MAB_MODE_HEADER
{
	uint8 version;
	uint8 flgs;
	uint16 structSize;
	uint16 number;
	uint8 namelen;
	uint8 reserved;
	unsigned int transitionParamOffset;
	unsigned int reserved2;
	float volume;
	float pitch;
	float lowpass;
	float speed;
	char name_v2[16];
	MAB_MODE_PARAM ModeParam;
};



struct MAB_CHUNK_HEADER
{
	uint8 version;
	uint8 reserved;
	uint16 structSize;
	uint16 numItems;
	uint16 reserved2;
	unsigned int reserved3[2];
	char padding[16]; // UNK 0x16 padding
	MAB_MUSIC_HEADER MusicHeader;
	char padding2[32]; // MAB FILE NAME
	TArray<MAB_SECTION_HEADER> SectionHeader;
	char padding3[48]; // MAB PROJECT NAME
	TArray<MAB_LAYER_HEADER> LayerHeader;
	TArray<MAB_METER_HEADER> MeterHeader;
	TArray<MAB_MODE_HEADER> ModeHeader;
	char padding4[16]; // MODE 0

	MAB_CHUNK_HEADER()
	{

		version = 0;
		reserved = 0;
		structSize = 0x10;
		numItems = 1;
		reserved2 = 0;
		reserved3[0] = 0;
		reserved3[1] = 0;
		

		
		// MUSIC HEADER
		MusicHeader.version = 0x0D;
		MusicHeader.output = 0;
		MusicHeader.structSize = 0x60;
		MusicHeader.numSections = 1;
		MusicHeader.numModes = 1;
		MusicHeader.category = 0;
		MusicHeader.priority = 0;
		MusicHeader.number = 0;
		MusicHeader.flgs = 0;
		MusicHeader.distanceAttenuationCurve = 0;

		MusicHeader.interiorFactor = 0;
		// 16 Bytes of random ass padding for name_v8[16];
		MusicHeader.audibleRange = 0;
		MusicHeader.innerRange = 0;
		MusicHeader.volume = 1;
		MusicHeader.auxSendBusses = 0;
		// 16 Bytes of random ass padding for auxSendVolumes[4];
		MusicHeader.auxSendVolumes[0] = 0;
		MusicHeader.auxSendVolumes[1] = 0;
		MusicHeader.auxSendVolumes[2] = 0;
		MusicHeader.auxSendVolumes[3] = 0;


		MusicHeader.numAuxSends = 0;
		MusicHeader.numEndMethods = 0;
		MusicHeader.numStartMethods = 0;
		MusicHeader.numZeroOnes = 0;
		MusicHeader.sampleRate = 0;
		MusicHeader.namelen = 0;
		MusicHeader.port = 0;
		MusicHeader.reserved = 0;
		MusicHeader.playLength = 0;


		// 16 Bytes offset for file name
		MAB_SECTION_HEADER Slice;
		Slice.version = 0;
		Slice.number = 0;
		Slice.structSize = 0;
		Slice.namelen = 0;
		Slice.numLayers = 1;
		Slice.numCustomPoints = 0;
		Slice.entryPoint = 0;
		Slice.exitPoint = 0;
		Slice.loopStart = 0;
		Slice.loopEnd = 0;
		Slice.numMeters = 1;
		Slice.loopStartMeterIndex = 0;
		Slice.transitionEffectIndex = 0;
		Slice.reserved = 0;
		Slice.syncType = 0;
		Slice.fadeCurveType = 0;
		Slice.nextSectionIndex = 0;
		Slice.previousSectionIndex = 0;
		Slice.fadeOutTime = 0;
		Slice.fadeOutOffset = 0;
		Slice.endTiming = 0;
		Slice.volume = 1;
		Slice.loopStartTiming = 0;
		Slice.fadeInTime = 0;
		Slice.fadeInOffset = 0;


		// Project Name


		// Skip unknown 16 byte chunk

		MAB_LAYER_HEADER MusicSectionlayer;
		MusicSectionlayer.version = 1;
		MusicSectionlayer.flgs = 0;
		MusicSectionlayer.structSize = 0x10;
		MusicSectionlayer.materialIndex = 0;
		MusicSectionlayer.loopCnt = 0;
		MusicSectionlayer.offset = 0;
		MusicSectionlayer.endPoint = 0;
		
		LayerHeader.Add(MusicSectionlayer);

		MAB_METER_HEADER MeterSectionlayer;
		MeterSectionlayer.version = 0;
		MeterSectionlayer.flgs = 3;
		MeterSectionlayer.structSize = 0x10;
		MeterSectionlayer.detail = 0;
		MeterSectionlayer.startBar = 0;
		MeterSectionlayer.tempo = 120;
		MeterSectionlayer.startSample = 0;
		
		MeterHeader.Add(MeterSectionlayer);


		SectionHeader.Add(Slice);
	

		MAB_MODE_HEADER Section;

		Section.version = 3;
		Section.flgs = 2;
		Section.structSize = 0x30;
		Section.number = 0;
		Section.namelen = 5;
		Section.reserved = 0;
		Section.transitionParamOffset = 112;
		Section.reserved2 = 0;
		Section.volume = 1;
		Section.pitch = 0;
		Section.lowpass = 1;
		Section.speed = 1;

		// Skip Padding
		
		// Name Skip

		Section.ModeParam.version = 0;
		Section.ModeParam.reserved = 0;
		Section.ModeParam.structSize = 0x30;
		for (int i = 0; i < 3; i++)
		{
			Section.ModeParam.reserved2[i] = 0;
		}
		for (int i = 0; i < 8; i++)
		{
			Section.ModeParam.layerVolumes[i] = 0;
		}

		ModeHeader.Add(Section);

	}


	MAB_CHUNK_HEADER(const uint8* SabMabData, int MusicSectionOffset, int EntryIndex, int InitialOffset)
	{
		// MAB CHUNK HEADER
		int Index = EntryIndex;
		int Offset = MusicSectionOffset;
		int NameOffset = 0;
		int NameSize = 0;
		FString Name;

		version = BytesToUint8(SabMabData, Offset);
		reserved = BytesToUint8(SabMabData, Offset + 1);
		structSize = BytesToUint16(SabMabData, Offset + 2);
		numItems = BytesToUint8(SabMabData, Offset + 4);
		reserved2 = BytesToUint8(SabMabData, Offset + 5);
		reserved3[0] = 0;
		reserved3[1] = 0;
		NameSize = BytesToUint8(SabMabData, Offset + 72);
		Name = ListOfBytesToString(&SabMabData[NameOffset], NameSize);
		//TableOffset = (NameOffset + NameSize + 15) - ((NameOffset + NameSize + 15) - (InitialOffset - 16)) % 16;
		

		Offset = MusicSectionOffset + BytesToUint32(SabMabData, MusicSectionOffset + 16 + EntryIndex * 4);

		// MUSIC HEADER
		MusicHeader.version = BytesToUint8(SabMabData, Offset);
		MusicHeader.output = BytesToUint8(SabMabData, Offset + 1);
		MusicHeader.structSize = BytesToUint16(SabMabData, Offset + 2);
		MusicHeader.numSections = BytesToUint8(SabMabData, Offset + 4);
		MusicHeader.numModes = BytesToUint8(SabMabData, Offset + 5);
		MusicHeader.category = BytesToUint8(SabMabData, Offset + 6);
		MusicHeader.priority = BytesToUint8(SabMabData, Offset + 7);
		MusicHeader.number = BytesToUint16(SabMabData, Offset + 8);
		MusicHeader.flgs = BytesToUint8(SabMabData, Offset + 10);
		MusicHeader.distanceAttenuationCurve = BytesToUint8(SabMabData, Offset + 11);

		MusicHeader.interiorFactor = BytesToFloat(SabMabData, Offset + 12);
		// 16 Bytes of random ass padding for name_v8[16];
		MusicHeader.audibleRange = BytesToFloat(SabMabData, Offset + 32);
		MusicHeader.innerRange = BytesToFloat(SabMabData, Offset + 36);
		MusicHeader.volume = BytesToFloat(SabMabData, Offset + 40);
		MusicHeader.auxSendBusses = BytesToUint32(SabMabData, Offset + 44);
		// 16 Bytes of random ass padding for auxSendVolumes[4];
		MusicHeader.auxSendVolumes[0] = BytesToFloat(SabMabData, Offset + 48);
		MusicHeader.auxSendVolumes[1] = BytesToFloat(SabMabData, Offset + 52);
		MusicHeader.auxSendVolumes[2] = BytesToFloat(SabMabData, Offset + 56);
		MusicHeader.auxSendVolumes[3] = BytesToFloat(SabMabData, Offset + 60);


		MusicHeader.numAuxSends = BytesToUint8(SabMabData, Offset + 64);
		MusicHeader.numEndMethods = BytesToUint8(SabMabData, Offset + 65);
		MusicHeader.numStartMethods = BytesToUint8(SabMabData, Offset + 66);
		MusicHeader.numZeroOnes = BytesToUint8(SabMabData, Offset + 67);
		MusicHeader.sampleRate = BytesToUint32(SabMabData, Offset + 68);
		MusicHeader.namelen = BytesToUint8(SabMabData, Offset + 72);
		MusicHeader.port = BytesToUint8(SabMabData, Offset + 73);
		MusicHeader.reserved = BytesToUint16(SabMabData, Offset + 74);
		MusicHeader.playLength = BytesToFloat(SabMabData, Offset + 76);


		NameOffset = Offset + 80;
		NameSize = 15;
		Name = ListOfBytesToString(&SabMabData[NameOffset], NameSize);


		// 16 Bytes offset for file name
		NameOffset = Offset + 95;
		NameSize = 15;
		Name = ListOfBytesToString(&SabMabData[NameOffset], NameSize);

		Offset = ((NameOffset + (NameSize + 1)) + 16) + 1;

		for (int SliceIndex = 0; SliceIndex < MusicHeader.numSections; SliceIndex++)
		{
			MAB_SECTION_HEADER Slice;
			Index = SliceIndex;
			Slice.version = BytesToUint8(SabMabData, Offset);
			Slice.number = BytesToUint8(SabMabData, Offset + 1);
			Slice.structSize = BytesToUint16(SabMabData, Offset + 2);
			Slice.namelen = BytesToUint8(SabMabData, Offset + 4);
			Slice.numLayers = BytesToUint8(SabMabData, Offset + 5);
			Slice.numCustomPoints = BytesToUint16(SabMabData, Offset + 6);
			Slice.entryPoint = BytesToUint32(SabMabData, Offset + 8);
			Slice.exitPoint = BytesToUint32(SabMabData, Offset + 12);
			Slice.loopStart = BytesToUint32(SabMabData, Offset + 16);
			Slice.loopEnd = BytesToUint32(SabMabData, Offset + 20);
			Slice.numMeters = BytesToUint16(SabMabData, Offset + 24);
			Slice.loopStartMeterIndex = BytesToUint16(SabMabData, Offset + 26);
			Slice.transitionEffectIndex = BytesToInt16(SabMabData, Offset + 28);
			Slice.reserved = BytesToInt16(SabMabData, Offset + 30);
			Slice.syncType = BytesToUint8(SabMabData, Offset + 32);
			Slice.fadeCurveType = BytesToUint8(SabMabData, Offset + 33);
			Slice.nextSectionIndex = BytesToUint8(SabMabData, Offset + 34);
			Slice.previousSectionIndex = BytesToUint8(SabMabData, Offset + 35);
			Slice.fadeOutTime = BytesToFloat(SabMabData, Offset + 36);
			Slice.fadeOutOffset = BytesToFloat(SabMabData, Offset + 40);
			Slice.endTiming = BytesToUint32(SabMabData, Offset + 44);
			Slice.volume = BytesToFloat(SabMabData, Offset + 48);
			Slice.loopStartTiming = BytesToUint32(SabMabData, Offset + 52);
			Slice.fadeInTime = BytesToFloat(SabMabData, Offset + 56);
			Slice.fadeInOffset = BytesToFloat(SabMabData, Offset + 60);

			/*
			int LayerCount = 0;
			if (Slice.Version <= 7)
			{
				// 4: meter count
				LayerCount = BytesToUint8(SabMabData, Slice.Offset + 5);
				Slice.CustomPointsCount = BytesToUint16(SabMabData, Slice.Offset + 6);
				Slice.EntryPointsSample = BytesToUint32(SabMabData, Slice.Offset + 8);
				Slice.ExitPointsSample = BytesToUint32(SabMabData, Slice.Offset + 12);
				Slice.LoopStart = BytesToUint32(SabMabData, Slice.Offset + 16);
				Slice.LoopEnd = BytesToUint32(SabMabData, Slice.Offset + 20);
				// 24+: meter transition timing info (offsets, points, curves, etc)
				Slice.NameOffset = 48;
				Slice.NameSize = 15;
				Slice.SubTableOffset = Slice.Offset + Slice.Size;
			}
			else
			{
				Slice.NameSize = BytesToUint8(SabMabData, Slice.Offset + 4);
				LayerCount = BytesToUint8(SabMabData, Slice.Offset + 5);
				Slice.CustomPointsCount = BytesToUint16(SabMabData, Slice.Offset + 6);
				Slice.EntryPointsSample = BytesToUint32(SabMabData, Slice.Offset + 8);
				Slice.ExitPointsSample = BytesToUint32(SabMabData, Slice.Offset + 12);
				Slice.LoopStart = BytesToUint32(SabMabData, Slice.Offset + 16);
				Slice.LoopEnd = BytesToUint32(SabMabData, Slice.Offset + 20);
				Slice.MeterCount = BytesToUint32(SabMabData, Slice.Offset + 24);
				// 0x18: meter count
				// 0x1c+: meter transition timing info (offsets, points, curves, etc)
				Slice.NameOffset = Slice.Offset + Slice.Size;
				Slice.SubTableOffset = (Slice.NameOffset + Slice.NameSize + 15) - ((Slice.NameOffset + Slice.NameSize + 15) - (InitialOffset - 16)) % 16;
			}
			*/

			// Project Name
			NameOffset = Offset + 64;

			//Name = ListOfBytesToString(&SabMabData[NameOffset], (Slice.namelen - 1));
			Offset = (NameOffset + Slice.namelen) + (32 - Slice.namelen % 32);

			// Skip unknown 16 byte chunk
			Offset += 16;

			for (int LayerIndex = 0; LayerIndex < (int)Slice.numLayers; LayerIndex++)
			{
				MAB_LAYER_HEADER MusicSectionlayer;
				Index = LayerIndex;
				MusicSectionlayer.version = BytesToUint8(SabMabData, Offset);
				MusicSectionlayer.flgs = BytesToUint8(SabMabData, Offset + 1);
				MusicSectionlayer.structSize = BytesToUint16(SabMabData, Offset + 2);
				MusicSectionlayer.materialIndex = BytesToUint16(SabMabData, Offset + 4);
				MusicSectionlayer.loopCnt = BytesToUint16(SabMabData, Offset + 6);
				MusicSectionlayer.offset = BytesToUint32(SabMabData, Offset + 8);
				MusicSectionlayer.endPoint = BytesToUint32(SabMabData, Offset + 12);
				LayerHeader.Add(MusicSectionlayer);


				// For Each Layer skip 16 byte chunk
				Offset += (int)MusicSectionlayer.structSize;
			}

			for (int LayerIndex = 0; LayerIndex < Slice.numMeters; LayerIndex++)
			{
				MAB_METER_HEADER MusicSectionlayer;
				Index = LayerIndex;
				MusicSectionlayer.version = BytesToUint8(SabMabData, Offset);
				MusicSectionlayer.flgs = BytesToUint8(SabMabData, Offset + 1);
				MusicSectionlayer.structSize = BytesToUint16(SabMabData, Offset + 2);
				MusicSectionlayer.detail = BytesToUint16(SabMabData, Offset + 4);
				MusicSectionlayer.startBar = BytesToUint16(SabMabData, Offset + 6);
				MusicSectionlayer.tempo = BytesToFloat(SabMabData, Offset + 8);
				MusicSectionlayer.startSample = BytesToUint32(SabMabData, Offset + 12);
				MeterHeader.Add(MusicSectionlayer);


				// For Each Layer skip structSize byte chunk
				Offset += (int)MusicSectionlayer.structSize;
			}

			SectionHeader.Add(Slice);
		}

		for (int ModeIndex = 0; ModeIndex < MusicHeader.numModes; ModeIndex++)
		{
			MAB_MODE_HEADER Section;

			Section.version = BytesToUint8(SabMabData, Offset);
			Section.flgs = BytesToUint8(SabMabData, Offset + 1);
			Section.structSize = BytesToUint16(SabMabData, Offset + 2);
			Section.number = BytesToUint16(SabMabData, Offset + 4);
			Section.namelen = BytesToUint8(SabMabData, Offset + 6);
			Section.reserved = BytesToUint8(SabMabData, Offset + 7);
			Section.transitionParamOffset = BytesToUint32(SabMabData, Offset + 8);
			Section.reserved2 = BytesToUint32(SabMabData, Offset + 12);
			Section.volume = BytesToFloat(SabMabData, Offset + 16);
			Section.pitch = BytesToFloat(SabMabData, Offset + 20);
			Section.lowpass = BytesToFloat(SabMabData, Offset + 24);
			Section.speed = BytesToFloat(SabMabData, Offset + 28);

			NameOffset = Offset + 32;
			// Skip Padding
			NameOffset += 16;

			//Section.name_v2 = ListOfBytesToString(&SabMabData[NameOffset], Section.namelen);

			Offset = (NameOffset + 16); // Name Skip

			Section.ModeParam.version = BytesToUint8(SabMabData, Offset);
			Offset += sizeof(uint8);
			Section.ModeParam.reserved = BytesToUint8(SabMabData, Offset);
			Offset += sizeof(uint8);
			Section.ModeParam.structSize = BytesToUint16(SabMabData, Offset);
			Offset += sizeof(uint16);
			for (int i = 0; i < 3; i++)
			{
				Section.ModeParam.reserved2[i] = BytesToFloat(SabMabData, Offset);
				Offset += sizeof(float);
			}
			for (int i = 0; i < 8; i++)
			{
				Section.ModeParam.layerVolumes[i] = BytesToFloat(SabMabData, Offset);
				Offset += sizeof(float);
			}

			ModeHeader.Add(Section);

			Offset += (int)Section.structSize * 2;
			Offset += 16; // Padding
		}
		
	}

	friend FArchive& operator<<(FArchive& Ar, MAB_CHUNK_HEADER& MabChunkHeader)
	{
		uint8 zero = 0;

		// MAB CHUNK HEADER
		Ar << MabChunkHeader.version;
		Ar << MabChunkHeader.reserved;
		Ar << MabChunkHeader.structSize;
		Ar << MabChunkHeader.numItems;
		Ar << MabChunkHeader.reserved2;
		Ar << MabChunkHeader.reserved3[0];
		Ar << MabChunkHeader.reserved3[1];
		
		// 16 Bytes of padding
		for (int i = 0; i < 16; i++)
		{
			Ar << zero;
		}


		// MUSIC HEADER
		Ar << MabChunkHeader.MusicHeader.version;
		Ar << MabChunkHeader.MusicHeader.output;
		Ar << MabChunkHeader.MusicHeader.structSize;
		Ar << MabChunkHeader.MusicHeader.numSections;
		Ar << MabChunkHeader.MusicHeader.numModes;
		Ar << MabChunkHeader.MusicHeader.category;
		Ar << MabChunkHeader.MusicHeader.priority;
		Ar << MabChunkHeader.MusicHeader.number;
		Ar << MabChunkHeader.MusicHeader.flgs;
		Ar << MabChunkHeader.MusicHeader.distanceAttenuationCurve;

		Ar << MabChunkHeader.MusicHeader.interiorFactor;
		// 16 Bytes of random ass padding for name_v8[16];
		for (int i = 0; i < 16; i++)
		{
			Ar << zero;
		}
		Ar << MabChunkHeader.MusicHeader.audibleRange;
		Ar << MabChunkHeader.MusicHeader.innerRange;
		Ar << MabChunkHeader.MusicHeader.volume;
		Ar << MabChunkHeader.MusicHeader.auxSendBusses;

		// 16 Bytes of random ass padding for auxSendVolumes[4];
		for (int i = 0; i < 4; i++)
		{
			Ar << MabChunkHeader.MusicHeader.auxSendVolumes[i];
		}

		Ar << MabChunkHeader.MusicHeader.numAuxSends;
		Ar << MabChunkHeader.MusicHeader.numEndMethods;
		Ar << MabChunkHeader.MusicHeader.numStartMethods;
		Ar << MabChunkHeader.MusicHeader.numZeroOnes;
		Ar << MabChunkHeader.MusicHeader.sampleRate;
		Ar << MabChunkHeader.MusicHeader.namelen;
		Ar << MabChunkHeader.MusicHeader.port;
		Ar << MabChunkHeader.MusicHeader.reserved;
		Ar << MabChunkHeader.MusicHeader.playLength;

		// 16 Bytes padding reserved2
		for (int i = 0; i < 16; i++)
		{
			Ar << zero;
		}

		// 16 Bytes offset for file name TODO: get proper filename and serialize
		for (int i = 0; i < 16; i++)
		{
			Ar << zero;
		}

		// 16 Bytes of Padding idk what for
		for (int i = 0; i < 16; i++)
		{
			Ar << zero;
		}

		// SECTION HEADER

		for (int SectionIndex = 0; SectionIndex < MabChunkHeader.MusicHeader.numSections; SectionIndex++)
		{

			Ar << MabChunkHeader.SectionHeader[SectionIndex].version;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].number;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].structSize;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].namelen;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].numLayers;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].numCustomPoints;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].entryPoint;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].exitPoint;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].loopStart;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].loopEnd;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].numMeters;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].loopStartMeterIndex;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].transitionEffectIndex;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].reserved;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].syncType;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].fadeCurveType;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].nextSectionIndex;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].previousSectionIndex;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].fadeOutTime;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].fadeOutOffset;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].endTiming;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].volume;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].loopStartTiming;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].fadeInTime;
			Ar << MabChunkHeader.SectionHeader[SectionIndex].fadeInOffset;

			/*
			int LayerCount = 0;
			if (SectionHeader[SectionIndex]Version <= 7)
			{
				// 4: meter count
				LayerCount = BytesToUint8(SabMabData, SectionHeader[SectionIndex]Offset + 5);
				SectionHeader[SectionIndex]CustomPointsCount = BytesToUint16(SabMabData, SectionHeader[SectionIndex]Offset + 6);
				SectionHeader[SectionIndex]EntryPointsSample = BytesToUint32(SabMabData, SectionHeader[SectionIndex]Offset + 8);
				SectionHeader[SectionIndex]ExitPointsSample = BytesToUint32(SabMabData, SectionHeader[SectionIndex]Offset + 12);
				SectionHeader[SectionIndex]LoopStart = BytesToUint32(SabMabData, SectionHeader[SectionIndex]Offset + 16);
				SectionHeader[SectionIndex]LoopEnd = BytesToUint32(SabMabData, SectionHeader[SectionIndex]Offset + 20);
				// 24+: meter transition timing info (offsets, points, curves, etc)
				SectionHeader[SectionIndex]NameOffset = 48;
				SectionHeader[SectionIndex]NameSize = 15;
				SectionHeader[SectionIndex]SubTableOffset = SectionHeader[SectionIndex]Offset + SectionHeader[SectionIndex]Size;
			}
			else
			{
				SectionHeader[SectionIndex]NameSize = BytesToUint8(SabMabData, SectionHeader[SectionIndex]Offset + 4);
				LayerCount = BytesToUint8(SabMabData, SectionHeader[SectionIndex]Offset + 5);
				SectionHeader[SectionIndex]CustomPointsCount = BytesToUint16(SabMabData, SectionHeader[SectionIndex]Offset + 6);
				SectionHeader[SectionIndex]EntryPointsSample = BytesToUint32(SabMabData, SectionHeader[SectionIndex]Offset + 8);
				SectionHeader[SectionIndex]ExitPointsSample = BytesToUint32(SabMabData, SectionHeader[SectionIndex]Offset + 12);
				SectionHeader[SectionIndex]LoopStart = BytesToUint32(SabMabData, SectionHeader[SectionIndex]Offset + 16);
				SectionHeader[SectionIndex]LoopEnd = BytesToUint32(SabMabData, SectionHeader[SectionIndex]Offset + 20);
				SectionHeader[SectionIndex]MeterCount = BytesToUint32(SabMabData, SectionHeader[SectionIndex]Offset + 24);
				// 0x18: meter count
				// 0x1c+: meter transition timing info (offsets, points, curves, etc)
				SectionHeader[SectionIndex]NameOffset = SectionHeader[SectionIndex]Offset + SectionHeader[SectionIndex]Size;
				SectionHeader[SectionIndex]SubTableOffset = (SectionHeader[SectionIndex]NameOffset + SectionHeader[SectionIndex]NameSize + 15) - ((SectionHeader[SectionIndex]NameOffset + SectionHeader[SectionIndex]NameSize + 15) - (InitialOffset - 16)) % 16;
			}
			*/

			// Project Name 32 Bytes usually, do check nameLen for avoiding case specific issues TODO: GET and SERIALIZE project name
			for (int i = 0; i < 32; i++)
			{
				Ar << zero;
			}

			// Skip unknown 16 byte chunk
			for (int i = 0; i < 16; i++)
			{
				Ar << zero;
			}

			for (int LayerIndex = 0; LayerIndex < MabChunkHeader.SectionHeader[SectionIndex].numLayers; LayerIndex++)
			{
				Ar << MabChunkHeader.LayerHeader[LayerIndex].version;
				Ar << MabChunkHeader.LayerHeader[LayerIndex].flgs;
				Ar << MabChunkHeader.LayerHeader[LayerIndex].structSize;
				Ar << MabChunkHeader.LayerHeader[LayerIndex].materialIndex;
				Ar << MabChunkHeader.LayerHeader[LayerIndex].loopCnt;
				Ar << MabChunkHeader.LayerHeader[LayerIndex].offset;
				Ar << MabChunkHeader.LayerHeader[LayerIndex].endPoint;
			}

			for (int MeterIndex = 0; MeterIndex < MabChunkHeader.SectionHeader[SectionIndex].numMeters; MeterIndex++)
			{
				
				Ar << MabChunkHeader.MeterHeader[MeterIndex].version;
				Ar << MabChunkHeader.MeterHeader[MeterIndex].flgs;
				Ar << MabChunkHeader.MeterHeader[MeterIndex].structSize;
				Ar << MabChunkHeader.MeterHeader[MeterIndex].detail;
				Ar << MabChunkHeader.MeterHeader[MeterIndex].startBar;
				Ar << MabChunkHeader.MeterHeader[MeterIndex].tempo;
				Ar << MabChunkHeader.MeterHeader[MeterIndex].startSample;
			}
		}

		for (int ModeIndex = 0; ModeIndex < MabChunkHeader.MusicHeader.numModes; ModeIndex++)
		{
			Ar << MabChunkHeader.ModeHeader[ModeIndex].version;
			Ar << MabChunkHeader.ModeHeader[ModeIndex].flgs;
			Ar << MabChunkHeader.ModeHeader[ModeIndex].structSize;
			Ar << MabChunkHeader.ModeHeader[ModeIndex].number;
			Ar << MabChunkHeader.ModeHeader[ModeIndex].namelen;
			Ar << MabChunkHeader.ModeHeader[ModeIndex].reserved;
			Ar << MabChunkHeader.ModeHeader[ModeIndex].transitionParamOffset;
			Ar << MabChunkHeader.ModeHeader[ModeIndex].reserved2;
			Ar << MabChunkHeader.ModeHeader[ModeIndex].volume;
			Ar << MabChunkHeader.ModeHeader[ModeIndex].pitch;
			Ar << MabChunkHeader.ModeHeader[ModeIndex].lowpass;
			Ar << MabChunkHeader.ModeHeader[ModeIndex].speed;
			

			// Skip Padding 16 Bytes, name_v2
			for (int i = 0; i < 16; i++)
			{
				Ar << zero;
			}
			// Name Skip (eg: Mode0) TODO: Serialize Mode0 as without it this might break
			for (int i = 0; i < 16; i++)
			{
				Ar << zero;
			}

			// MODEPARAM CHUNK
			Ar << MabChunkHeader.ModeHeader[ModeIndex].ModeParam.version;
			Ar << MabChunkHeader.ModeHeader[ModeIndex].ModeParam.reserved;
			Ar << MabChunkHeader.ModeHeader[ModeIndex].ModeParam.structSize;
			
			for (int i = 0; i < 3; i++)
			{
				Ar << MabChunkHeader.ModeHeader[ModeIndex].ModeParam.reserved2[i];
				
			}
			for (int i = 0; i < 8; i++)
			{
				Ar << MabChunkHeader.ModeHeader[ModeIndex].ModeParam.layerVolumes[i];
			}

		}

		return Ar;
	}
};

// INSTRUMENT HEADER (inst)

struct MAB_INSTRUMENT_CHUNK_HEADER
{
	uint8 version;
	uint8 reserved;
	uint16 structSize;
	uint16 numItems;
	uint16 reserved2;
	unsigned int reserved3[2];

	friend FArchive& operator<<(FArchive& Ar, MAB_INSTRUMENT_CHUNK_HEADER& MabInstrumentHeader)
	{
		Ar << MabInstrumentHeader.version;
		Ar << MabInstrumentHeader.reserved;
		Ar << MabInstrumentHeader.structSize;
		Ar << MabInstrumentHeader.numItems;
		Ar << MabInstrumentHeader.reserved2;
		Ar << MabInstrumentHeader.reserved3[0];
		Ar << MabInstrumentHeader.reserved3[1];

		return Ar;
	}


	MAB_INSTRUMENT_CHUNK_HEADER(const uint8* SabMabData, int InstrumentSectionOffset, int EntryIndex)
	{
		int Offset = InstrumentSectionOffset;
			//+ BytesToUint32(SabMabData, InstrumentSectionOffset + 16 + EntryIndex * 4);
		version = BytesToUint8(SabMabData, Offset);
		reserved = BytesToUint8(SabMabData, Offset + 1);
		structSize = BytesToUint16(SabMabData, Offset + 2);
		numItems = BytesToUint16(SabMabData, Offset + 4);
		reserved2 = BytesToUint16(SabMabData, Offset + 6);
		reserved3[0] = BytesToUint32(SabMabData, Offset + 8);
		reserved3[1] = BytesToUint32(SabMabData, Offset + 12); // next: 16
		/*
		uint8 MaterialCount = BytesToUint8(SabMabData, Offset + 5);
		Category = BytesToUint8(SabMabData, Offset + 6);
		Priority = BytesToUint8(SabMabData, Offset + 7);
		UnknownAt8 = BytesToUint16(SabMabData, Offset + 8);
		Flags = BytesToUint8(SabMabData, Offset + 10);
		DistanceAttenuationCurve = BytesToUint8(SabMabData, Offset + 11);
		
		InteriorFactor = *reinterpret_cast<float*>(SabMabData[Offset + 12]);
		AudibleRange = *reinterpret_cast<float*>(SabMabData[Offset + 16]);
		InnerRange = *reinterpret_cast<float*>(SabMabData[Offset + 20]);
		PlayLength = *reinterpret_cast<float*>(SabMabData[Offset + 24]);

		NameOffset = Offset + 48;
		NameSize = 15;

		Name = ListOfBytesToString(&SabMabData[NameOffset], NameSize);

		int MaterialOffset = NameOffset + NameSize + 1;
		for (int MaterialIndex = 0; MaterialIndex < MaterialCount; MaterialIndex++)
		{
			FMusicInstrumentMaterial Material;
			Material.Version = BytesToUint8(SabMabData, MaterialOffset);
			Material.UnknownAt1 = BytesToUint8(SabMabData, MaterialOffset + 1);
			Material.MaterialSize = BytesToUint16(SabMabData, MaterialOffset + 2);
			Material.MaterialIndex = BytesToUint16(SabMabData, MaterialOffset + 4);
			Material.Id = BytesToUint16(SabMabData, MaterialOffset + 6);
			Material.Volume = *reinterpret_cast<float*>(SabMabData[MaterialOffset + 8]);
			Material.SyncPoint = BytesToUint32(SabMabData, MaterialOffset + 12);
			Material.SampleRate = BytesToUint32(SabMabData, MaterialOffset + 16);
			MaterialOffset += Material.MaterialSize;
			//Materials.Add(Material); //This was not in the original but this may be what it needs
		*/

		}

	MAB_INSTRUMENT_CHUNK_HEADER()
	{
		version = 0;
		reserved = 0;
		structSize = 0x10;
		numItems = 0;
		reserved2 = 0;
		reserved3[0] = 0;
		reserved3[1] = 0; 
	}

};


// SEQUENCE HEADER (seq)

struct SABSEQUENCECOMMANDHEADER
{
	uint8 version;
	uint8 structSize;
	uint8 type;
	uint8 commandSize;
};

struct SABSEQUENCEKEYONCOMMAND
{
	SABSEQUENCECOMMANDHEADER header;
	unsigned int trackIndex;
	uint8 isLoop;
	uint8 reserved;
	uint16 trackID;
	float playLength;
};


struct SABSEQUENCEHEADER_RANDOM
{
	uint8 value;
	uint8 group;
	uint16 reserved;
	unsigned int reserved2[2];
};

struct SABSEQUENCEHEADER_ORDER
{
	uint8 force;
	uint8 group;
	uint16 reserved;
	unsigned int reserved2[2];
};

struct SABSEQUENCEHEADER_SWITCHING
{
	float low;
	float high;
	unsigned int reserved;
};

union SABSEQUENCEHEADER_DETAIL
{
	SABSEQUENCEHEADER_RANDOM random;
	SABSEQUENCEHEADER_ORDER order;
	SABSEQUENCEHEADER_SWITCHING switching;
	unsigned int reserved[3];
};

struct SABSEQUENCEHEADER
{
	uint8 version;
	uint8 reserved;
	uint16 structSize;
	SABSEQUENCEHEADER_DETAIL detail;
	uint16 number;
	uint16 volZerooneOffset;
	uint16 pitchZerooneOffset;
	uint16 commandOffset;
	int reserved2[2];
};

struct SABSEQUENCECHUNKHEADER
{
	uint8 version;
	uint8 reserved;
	uint16 structSize;
	uint16 numSequences;
	uint16 reserved2;
	unsigned int reserved3[2];
	SABSEQUENCEHEADER a;
};


// TRACK HEADER (trk)

struct SABTRACKHEADER_SOUND
{
	int16 index;
	int16 reserved;
};

struct SABTRACKHEADER_MATERIAL
{
	int16 index;
	int16 bankNumber;
};

union SABTRACKHEADER_DETAIL
{
	SABTRACKHEADER_SOUND sound;
	SABTRACKHEADER_MATERIAL material;
};

struct SABTRACKHEADER
{
	uint8 version;
	uint8 type;
	uint16 structSize;
	SABTRACKHEADER_DETAIL detail;
	uint16 id;
	uint16 childID;
	unsigned int reserved2;
};

struct SABTRACKCHUNKHEADER
{
	uint8 version;
	uint8 reserved;
	uint16 structSize;
	uint16 numTracks;
	uint16 reserved2;
	unsigned int reserved3[2];
	SABTRACKHEADER a;
};


// MATERIAL HEADER (mtrl)

struct SABMATERIALHCAEXTRADATA
{
	uint8 version;
	uint8 structSize;
	uint16 header_size;
	uint16 frame_size;
	uint16 loop_start_frame;
	uint16 loop_end_frame;
	uint16 num_inserted;
	uint8 useMixer;
	uint8 reserved2[3];
};

struct SABMATERIALHEADER
{
	uint8 version;
	uint8 reserved;
	uint16 structSize;
	uint8 channel;
	uint8 format;
	uint16 number;
	unsigned int sampleRate;
	unsigned int loopStart;
	unsigned int loopEnd;
	unsigned int extraBytes;
	unsigned int dataSize;
	uint16 id;
	uint16 reserved3;
};

struct SABMATERIALCHUNKHEADER
{
	uint8 version;
	uint8 reserved;
	uint16 structSize;
	uint16 numMaterials;
	uint16 reserved2;
	unsigned int reserved3[2];
	char padding[16];
	SABMATERIALHEADER MaterialHeader;
	SABMATERIALHCAEXTRADATA MaterialHCAExtraData;

	friend FArchive& operator<<(FArchive& Ar, SABMATERIALCHUNKHEADER& SabMaterialChunkHeader)
	{
		uint8 zero = 0;
		// MTRL CHUNK HEADER
		Ar << SabMaterialChunkHeader.version;
		Ar << SabMaterialChunkHeader.reserved;
		Ar << SabMaterialChunkHeader.structSize;
		Ar << SabMaterialChunkHeader.numMaterials;
		Ar << SabMaterialChunkHeader.reserved2;
		Ar << SabMaterialChunkHeader.reserved3[0];
		Ar << SabMaterialChunkHeader.reserved3[1]; // next: 16

		// Padding 16
		for (int i = 0; i < 16; i++)
		{
			Ar << zero;
		}

		// Material Header Chunk Start
		Ar << SabMaterialChunkHeader.MaterialHeader.version;
		Ar << SabMaterialChunkHeader.MaterialHeader.reserved;
		Ar << SabMaterialChunkHeader.MaterialHeader.structSize;
		Ar << SabMaterialChunkHeader.MaterialHeader.channel;
		Ar << SabMaterialChunkHeader.MaterialHeader.format;
		Ar << SabMaterialChunkHeader.MaterialHeader.number;
		Ar << SabMaterialChunkHeader.MaterialHeader.sampleRate;
		Ar << SabMaterialChunkHeader.MaterialHeader.loopStart;
		Ar << SabMaterialChunkHeader.MaterialHeader.loopEnd;
		Ar << SabMaterialChunkHeader.MaterialHeader.extraBytes;
		Ar << SabMaterialChunkHeader.MaterialHeader.dataSize;
		Ar << SabMaterialChunkHeader.MaterialHeader.id;
		Ar << SabMaterialChunkHeader.MaterialHeader.reserved3;
		
		// EXTRA DATA HCA CHUNK HEADER

		Ar << SabMaterialChunkHeader.MaterialHCAExtraData.version;
		Ar << SabMaterialChunkHeader.MaterialHCAExtraData.structSize;
		Ar << SabMaterialChunkHeader.MaterialHCAExtraData.header_size;
		Ar << SabMaterialChunkHeader.MaterialHCAExtraData.frame_size;
		Ar << SabMaterialChunkHeader.MaterialHCAExtraData.loop_start_frame;
		Ar << SabMaterialChunkHeader.MaterialHCAExtraData.loop_end_frame;
		Ar << SabMaterialChunkHeader.MaterialHCAExtraData.num_inserted;
		Ar << SabMaterialChunkHeader.MaterialHCAExtraData.useMixer;
		Ar << SabMaterialChunkHeader.MaterialHCAExtraData.reserved2[0];
		Ar << SabMaterialChunkHeader.MaterialHCAExtraData.reserved2[1];
		Ar << SabMaterialChunkHeader.MaterialHCAExtraData.reserved2[2];

		return Ar;
	}

	SABMATERIALCHUNKHEADER(const uint8* SabMabData, int MaterialSectionOffset)
	{
		int InnerFilePositionOfFirstTracks = 0;

		uint16 EntryAddressesSize = BytesToUint16(SabMabData, MaterialSectionOffset + 2);
		uint16 EntryCount = BytesToUint16(SabMabData, MaterialSectionOffset + 4);
		for (int songEntryIndex = 0; songEntryIndex < EntryCount; songEntryIndex++)
		{
			// Get Material Header Offset from the Chunk Table Element
			int positionOfOffsetFromMaterialSectionOffset = MaterialSectionOffset + 16 + songEntryIndex * 4;
			//uint32 localEntryOffset = BytesToUint32(SabMabData, positionOfOffsetFromMaterialSectionOffset);
			//if (songEntryIndex == 0) { InnerFilePositionOfFirstTracks = SectionDeclaration.offset + localEntryOffset; }
			//int EntryOffset = MaterialSectionOffset + localEntryOffset;
			//int8 Codec = BytesToUint8(SabMabData, EntryOffset + 5);
			//if (Codec == 0) { continue; }

			int EntryIndex = songEntryIndex;
			int PositionOfOffsetFromMtrlSectionOffset = positionOfOffsetFromMaterialSectionOffset;
			int LocalSectionOffset = BytesToUint32(SabMabData, PositionOfOffsetFromMtrlSectionOffset);
			int HeaderPosition = MaterialSectionOffset + LocalSectionOffset;
			
			// MTRL CHUNK HEADER
			version = BytesToUint8(SabMabData, MaterialSectionOffset);
			reserved = BytesToUint8(SabMabData, MaterialSectionOffset + 1);
			structSize = BytesToUint16(SabMabData, MaterialSectionOffset + 2);
			numMaterials = BytesToUint16(SabMabData, MaterialSectionOffset + 4);
			reserved2 = BytesToUint16(SabMabData, MaterialSectionOffset + 6);
			reserved3[0] = BytesToUint32(SabMabData, MaterialSectionOffset + 8);
			reserved3[1] = BytesToUint32(SabMabData, MaterialSectionOffset + 12); // next: 16
			
			// Padding 16
			HeaderPosition = MaterialSectionOffset + 16;
			HeaderPosition += 16;

			// TODO: for each numMaterial
			// Material Header Chunk Start
			MaterialHeader.version = BytesToUint8(SabMabData, HeaderPosition);
			MaterialHeader.reserved = BytesToUint8(SabMabData, HeaderPosition + 1);
			MaterialHeader.structSize = BytesToUint16(SabMabData, HeaderPosition + 2);
			MaterialHeader.channel = BytesToUint8(SabMabData, HeaderPosition + 4);
			MaterialHeader.format = BytesToUint8(SabMabData, HeaderPosition + 5);
			MaterialHeader.number = BytesToUint16(SabMabData, HeaderPosition + 6);
			MaterialHeader.sampleRate = BytesToUint32(SabMabData, HeaderPosition + 8);
			MaterialHeader.loopStart = BytesToUint32(SabMabData, HeaderPosition + 12);
			MaterialHeader.loopEnd = BytesToUint32(SabMabData, HeaderPosition + 16);
			MaterialHeader.extraBytes = BytesToUint32(SabMabData, HeaderPosition + 20);
			MaterialHeader.dataSize = BytesToUint32(SabMabData, HeaderPosition + 24);
			MaterialHeader.id = BytesToUint16(SabMabData, HeaderPosition + 28);
			MaterialHeader.reserved3 = BytesToUint16(SabMabData, HeaderPosition + 30);
			unsigned int StreamPosition = MaterialHeader.extraBytes + MaterialHeader.dataSize;
			int MaterialHeaderSize = StreamPosition - HeaderPosition;
			
			int Offset = HeaderPosition + 32;

			//why is this in big endian wtf?
			//int hcaHeaderSizeByteBig = BytesToUint8(SabMabData, MaterialHeader.reserved3 + 16 + 6);
			//int hcaHeaderSizeByteSmall = BytesToUint8(SabMabData, MaterialHeader.reserved3 + 16 + 7);
			//MaterialHCAExtraData.header_size = (uint16)((hcaHeaderSizeByteBig << 8) + hcaHeaderSizeByteSmall);
			
			MaterialHCAExtraData.version = BytesToUint8(SabMabData, Offset);
			MaterialHCAExtraData.structSize = BytesToUint8(SabMabData, Offset + 1);
			MaterialHCAExtraData.header_size = BytesToUint16(SabMabData, Offset + 2);
			MaterialHCAExtraData.frame_size = BytesToUint16(SabMabData, Offset + 4);
			MaterialHCAExtraData.loop_start_frame = BytesToUint16(SabMabData, Offset + 6);
			MaterialHCAExtraData.loop_end_frame = BytesToUint16(SabMabData, Offset + 8);
			MaterialHCAExtraData.num_inserted = BytesToUint16(SabMabData, Offset + 10);
			MaterialHCAExtraData.useMixer = BytesToUint8(SabMabData, Offset + 12);
			MaterialHCAExtraData.reserved2[0] = BytesToUint8(SabMabData, Offset + 13);
			MaterialHCAExtraData.reserved2[1] = BytesToUint8(SabMabData, Offset + 14);
			MaterialHCAExtraData.reserved2[2] = BytesToUint8(SabMabData, Offset + 15);

			/*
			int NoHcaHeaderExtraDataSize = MaterialHeader.extraBytes - MaterialHCAExtraData.header_size;
			int HcaStreamStartPosition = MaterialHeader.reserved3 + 16;
			int HcaStreamSize = MaterialHCAExtraData.header_size + MaterialHeader.dataSize;
			int NoHcaHeaderSize = HcaStreamStartPosition - HeaderPosition;
			int TrackEndPosition = HcaStreamStartPosition + HcaStreamSize;*/
		}
	}

	SABMATERIALCHUNKHEADER()
	{
		// MTRL CHUNK HEADER
		version = 0;
		reserved = 0;
		structSize = 0x10;
		numMaterials = 1;
		reserved2 = 0;
		reserved3[0] = 0;
		reserved3[1] = 0; 

		// Padding 16

		
		// Material Header Chunk Start
		MaterialHeader.version = 0;
		MaterialHeader.reserved = 0;
		MaterialHeader.structSize = 0;
		MaterialHeader.channel = 0;
		MaterialHeader.format = 0;
		MaterialHeader.number = 0;
		MaterialHeader.sampleRate = 0;
		MaterialHeader.loopStart = 0;
		MaterialHeader.loopEnd = 0;
		MaterialHeader.extraBytes = 0;
		MaterialHeader.dataSize = 0;
		MaterialHeader.id = 0;
		MaterialHeader.reserved3 = 0;
		
	
		MaterialHCAExtraData.version = 1;
		MaterialHCAExtraData.structSize = 0x10;
		MaterialHCAExtraData.header_size = 0;
		MaterialHCAExtraData.frame_size = 0;
		MaterialHCAExtraData.loop_start_frame = 0;
		MaterialHCAExtraData.loop_end_frame = 0;
		MaterialHCAExtraData.num_inserted = 0;
		MaterialHCAExtraData.useMixer = 0;
		MaterialHCAExtraData.reserved2[0] = 0;
		MaterialHCAExtraData.reserved2[1] = 0;
		MaterialHCAExtraData.reserved2[2] = 0;

	}

};

struct SABSOUNDCHUNKTABLEELEMENT
{
	uint8 id[4];
	uint8 version;
	uint8 reserved;
	uint16 structSize;
	SABSOUNDCHUNKHEADER *a;
	unsigned int reserved2;
};


struct SABMUSICCHUNKTABLEELEMENT
{
	uint8 id[4];
	uint8 version;
	uint8 reserved;
	uint16 structSize;
	MAB_CHUNK_HEADER *a;
	unsigned int reserved2;
};

struct SABINSTRUMENTCHUNKTABLEELEMENT
{
	uint8 id[4];
	uint8 version;
	uint8 reserved;
	uint16 structSize;
	MAB_INSTRUMENT_CHUNK_HEADER *a;
	unsigned int reserved2;
};


struct SABSEQUENCECHUNKTABLEELEMENT
{
	uint8 id[4];
	uint8 version;
	uint8 reserved;
	uint16 structSize;
	SABSEQUENCECHUNKHEADER *a;
	unsigned int reserved2;
};

struct SABTRACKCHUNKTABLEELEMENT
{
	uint8 id[4];
	uint8 version;
	uint8 reserved;
	uint16 structSize;
	SABTRACKCHUNKHEADER *a;
	unsigned int reserved2;
};

struct SABMATERIALCHUNKTABLEELEMENT
{
	uint8 id[4];
	uint8 version;
	uint8 reserved;
	uint16 structSize;
	SABMATERIALCHUNKHEADER *a;
	unsigned int reserved2;
};

struct SABCHUNKTABLEELEMENT
{
	uint32 id;
	uint8 version;
	uint8 reserved;
	uint16 structSize;
	unsigned int offset;
	unsigned int reserved2;
};





struct SQEXSEAD_API FSabMabInfo
{
public:
	SABFILEHEADER HeaderChunk;
	TArray<SABCHUNKTABLEELEMENT> TableElementChunk;
	TArray<SABMATERIALCHUNKHEADER> MtrlEntries;
	TArray<MAB_INSTRUMENT_CHUNK_HEADER> InstEntries;
	TArray<MAB_CHUNK_HEADER> MabEntries;
	bool bIsSab = false;

	void Serialize(FArchive& Ar, UObject* Owner);

	size_t bytes_to_samples(size_t bytes, int channels, int bits_per_sample)
	{
		if (channels <= 0 || bits_per_sample <= 0) return 0;
		return ((int64_t)bytes * 8) / channels / bits_per_sample;
	}
	
	FSabMabInfo()
	{
		FMemory::Memcpy(&HeaderChunk.id, "mabf", 4);

		HeaderChunk.version = 2; 
		HeaderChunk.flgs = 1; 
		HeaderChunk.structSize = 0x10;
		HeaderChunk.numChunks = 3;
		HeaderChunk.reserved2 = 0;
		HeaderChunk.number = 0; 
		HeaderChunk.fileSize = 0;


		MAB_CHUNK_HEADER MuscHeader = MAB_CHUNK_HEADER::MAB_CHUNK_HEADER();
		MabEntries.Add(MuscHeader);
		MAB_INSTRUMENT_CHUNK_HEADER InstHeader = MAB_INSTRUMENT_CHUNK_HEADER::MAB_INSTRUMENT_CHUNK_HEADER();
		InstEntries.Add(InstHeader);
		SABMATERIALCHUNKHEADER MtrlHeader = SABMATERIALCHUNKHEADER::SABMATERIALCHUNKHEADER();
		MtrlEntries.Add(MtrlHeader);
	}

	bool ReadSabMabInfo(const uint8* SabMabData, int32 SabMabDataSize, FString* ErrorMessage = NULL, bool InHeaderDataOnly = false, void** OutFormatHeader = NULL)
	{
		// Version 3 Reader
		int InitialOffset = 0;
		// Mab/Sab Header
		HeaderChunk.id = BytesToUint32(SabMabData, InitialOffset);	// This should display MABF or SABF
		InitialOffset += 4;
		HeaderChunk.version = BytesToUint8(SabMabData, InitialOffset); // Displays the Main version of the Mab/Sab (Usually Displays 2)
		InitialOffset += 1;
		HeaderChunk.flgs = BytesToUint8(SabMabData, InitialOffset); // Displays the Sub version of the Mab/Sab. Can display 0, 1, or 2 (Mab/Sab have version 2.0, 2.1, 2.2)
		InitialOffset += 1;
		HeaderChunk.structSize = BytesToUint16(SabMabData, InitialOffset); // Size of this header
		InitialOffset += 2;
		HeaderChunk.numChunks = BytesToUint8(SabMabData, InitialOffset); // Amount of Sections to loop through
		InitialOffset += 1;
		HeaderChunk.reserved2 = BytesToUint8(SabMabData, InitialOffset); // Length of Descriptor
		InitialOffset += 1;
		HeaderChunk.number = BytesToUint16(SabMabData, InitialOffset); // ??? Need Documenting
		InitialOffset += 2;
		HeaderChunk.fileSize = BytesToUint32(SabMabData, InitialOffset); // Size of the Mab/Sab file
		InitialOffset += 4;
		//HeaderChunk.name = BytesToLongDouble(SabMabData, InitialOffset); // Descriptor
		HeaderChunk.name = BytesToUint32(SabMabData, InitialOffset);	// This should display MABF or SABF
		
		//
		int bytesNeededToPad = 16 - HeaderChunk.reserved2 % 16;
		int HeaderSize = 16 + HeaderChunk.reserved2 + bytesNeededToPad;

		// Determine if it is a Mab or Sab file
		bool bIsSab = false;
		if (Uint32ToString(HeaderChunk.id) != "mabf")
		{
			if (Uint32ToString(HeaderChunk.id) == "sabf") { bIsSab = true; }
			else
			{
				if (ErrorMessage) { *ErrorMessage = "FILE UNKNOWN: Invalid Sab/Mab file"; }
				return false;
			}
		}
		//

		// Handle Section Reading
		int SectionPosition = (InitialOffset - 16) + HeaderSize; // We subtract 16 because the header is 16 bytes - we have to ignore the additions
		for (int i = 0; i < HeaderChunk.numChunks; i++)
		{
			SABCHUNKTABLEELEMENT HeaderSection;

			// Sab/Mab Header Section
			HeaderSection.id = BytesToUint32(SabMabData, SectionPosition);
			SectionPosition += 4;
			HeaderSection.version = BytesToUint8(SabMabData, SectionPosition);
			SectionPosition += 1;
			HeaderSection.reserved = BytesToUint8(SabMabData, SectionPosition);
			SectionPosition += 1;
			HeaderSection.structSize = BytesToUint16(SabMabData, SectionPosition);
			SectionPosition += 2;
			HeaderSection.offset = BytesToUint32(SabMabData, SectionPosition);
			SectionPosition += 4;
			HeaderSection.reserved2 = BytesToUint32(SabMabData, SectionPosition);
			SectionPosition += 4;
			//
			TableElementChunk.Add(HeaderSection); // It now displays all sections correctly
		}

		// Handle Material Reading
		for (int i = 0; i < TableElementChunk.Num(); i++)
		{
			if (Uint32ToString(TableElementChunk[i].id) == "mtrl")
			{
				SABCHUNKTABLEELEMENT SectionDeclaration = TableElementChunk[i];
				int MaterialSectionOffset = (InitialOffset - 16) + SectionDeclaration.offset;

				SABMATERIALCHUNKHEADER Entry = SABMATERIALCHUNKHEADER::SABMATERIALCHUNKHEADER(SabMabData, MaterialSectionOffset);
				MtrlEntries.Add(Entry);

			}
			else { continue; }
		}

		// Handle Section Parsing
		if (bIsSab)
		{

		}
		else
		{
			// Handle Mab Parsing
			int MusicSectionOffset = 0;
			int InstrumentSectionOffset = 0;
			for (int i = 0; i < TableElementChunk.Num(); i++)
			{
				if (Uint32ToString(TableElementChunk[i].id) == "musc")
				{
					MusicSectionOffset = (InitialOffset - 16) + TableElementChunk[i].offset;
				}
				else if (Uint32ToString(TableElementChunk[i].id) == "inst")
				{
					InstrumentSectionOffset = (InitialOffset - 16) + TableElementChunk[i].offset;
				}
			}

			// TODO: Move both for loop inside the construct
			uint16 TrackEntryCount = BytesToUint16(SabMabData, MusicSectionOffset + 4);
			for (int EntryIndex = 0; EntryIndex < TrackEntryCount; EntryIndex++)
			{
				MAB_CHUNK_HEADER Entry = MAB_CHUNK_HEADER::MAB_CHUNK_HEADER(SabMabData, MusicSectionOffset, EntryIndex, InitialOffset);
				MabEntries.Add(Entry);
			}

			//uint16 instrumentEntryCount = BytesToUint16(SabMabData, InstrumentSectionOffset + 4);
			//for (int InstrumentIndex = 0; InstrumentIndex < instrumentEntryCount; InstrumentIndex++)
			//{
				MAB_INSTRUMENT_CHUNK_HEADER Instrument = MAB_INSTRUMENT_CHUNK_HEADER::MAB_INSTRUMENT_CHUNK_HEADER(SabMabData, InstrumentSectionOffset, 0);
				InstEntries.Add(Instrument);
			//}
			
			/*
			for (FMusicEntry Entry : MusicEntries)
			{
				for (FMusicSlice Slice : Entry.Slices)
				{
					for (FMusicLayer Layer : SectionHeader[SectionIndex]Layers)
					{
						FMaterialUser User;
						//MaterialSection.AddUser(new MusicLayerMaterialUser(slice, layer), layer.MaterialIndex);
						User.User = "CANNOT READ NAMES YET";
						User.MaterialIndex = Layer.MaterialIndex;
						Users.Add(User);
					}
				}
			}
			for (FMusicInstrument Instrument : Instruments)
			{
				for (FMusicInstrumentMaterial Material : Instrument.Materials)
				{
					FMaterialUser User;
					//MaterialSection.AddUser(instrument, material.MaterialIndex);
					User.User = "CANNOT READ NAMES YET";
					User.MaterialIndex = Material.MaterialIndex;
					Users.Add(User);
				}
			}
		*/
		}

		int endOfInnerFile = (InitialOffset - 16) + HeaderChunk.fileSize;
		/*BytesBeforeFile = fileBytes.SubArray(0, (InitialOffset - 16));
		BytesAfterFile = fileBytes.SubArray(endOfInnerFile, fileBytes.Length - endOfInnerFile);
		InnerFileBytes = fileBytes.SubArray((InitialOffset - 16), FileSize);*/

		return true;
	}
	
};
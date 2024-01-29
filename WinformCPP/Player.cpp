#include <iostream>
#include "Player.h"

HINSTANCE g_hVorbisFileDLL = NULL;

// Functions
void InitVorbisFile();
void ShutdownVorbisFile();
unsigned long DecodeOggVorbis(OggVorbis_File* psOggVorbisFile, char* pDecodeBuffer, unsigned long ulBufferSize, unsigned long ulChannels);
void Swap(short& s1, short& s2);

size_t ov_read_func(void* ptr, size_t size, size_t nmemb, void* datasource);
int ov_seek_func(void* datasource, ogg_int64_t offset, int whence);
int ov_close_func(void* datasource);
long ov_tell_func(void* datasource);

// Function pointers
typedef int (*LPOVCLEAR)(OggVorbis_File* vf);
typedef long (*LPOVREAD)(OggVorbis_File* vf, char* buffer, int length, int bigendianp, int word, int sgned, int* bitstream);
typedef ogg_int64_t(*LPOVPCMTOTAL)(OggVorbis_File* vf, int i);
typedef vorbis_info* (*LPOVINFO)(OggVorbis_File* vf, int link);
typedef vorbis_comment* (*LPOVCOMMENT)(OggVorbis_File* vf, int link);
typedef int (*LPOVOPENCALLBACKS)(void* datasource, OggVorbis_File* vf, char* initial, long ibytes, ov_callbacks callbacks);

// Variables
LPOVCLEAR			fn_ov_clear = NULL;
LPOVREAD			fn_ov_read = NULL;
LPOVPCMTOTAL		fn_ov_pcm_total = NULL;
LPOVINFO			fn_ov_info = NULL;
LPOVCOMMENT			fn_ov_comment = NULL;
LPOVOPENCALLBACKS	fn_ov_open_callbacks = NULL;

bool g_bVorbisInit = false;



SoundPlayer::SoundPlayer() {
	Init();
}

SoundPlayer::~SoundPlayer() {
	Shutdown();
}

void SoundPlayer::Init() {
	// Initialize Framework
	ALFWInit();

	// Initialize OggVorbis library
	InitVorbisFile();
	if (!g_bVorbisInit) {
		std::cerr << "Failed to find OggVorbis DLLs (vorbisfile.dll, ogg.dll, or vorbis.dll)" << std::endl;
		ALFWShutdown();
		exit(EXIT_FAILURE);
	}

	// Initialize OpenAL
	if (!ALFWInitOpenAL()) {
		std::cerr << "Failed to initialize OpenAL" << std::endl;
		ALFWShutdown();
		exit(EXIT_FAILURE);
	}

	// Set up Ogg callbacks
	sCallbacks.read_func = ov_read_func;
	sCallbacks.seek_func = ov_seek_func;
	sCallbacks.close_func = ov_close_func;
	sCallbacks.tell_func = ov_tell_func;

	// Generate OpenAL Buffers and Source
	alGenBuffers(NUMBUFFERS, uiBuffers);
	alGenSources(1, &uiSource);
}

void SoundPlayer::Shutdown() {
	// Stop the Source and clear the Queue
	if (IsPlaying)
	{
		IsPlaying = false;
		alSourceStop(uiSource);
	}
	alSourcei(uiSource, AL_BUFFER, 0);

	// Clean up Buffers and Source
	alDeleteSources(1, &uiSource);
	alDeleteBuffers(NUMBUFFERS, uiBuffers);

	// Close OggVorbis stream
	fn_ov_clear(&sOggVorbisFile);

	// Shutdown VorbisFile Library
	ShutdownVorbisFile();

	// Shutdown OpenAL
	ALFWShutdownOpenAL();

	// Shutdown Framework
	ALFWShutdown();

	// Free memory
	if (pDecodeBuffer) {
		free(pDecodeBuffer);
		pDecodeBuffer = NULL;
	}
}

using namespace System::IO;
int SoundPlayer::Load(const char* filePath)
{
	Stop();
	CurrentSound.file = filePath;
	// Convertir const char* en System::String^
	System::String^ managedFilePath = gcnew System::String(filePath);

	if (System::IO::Path::GetExtension(managedFilePath)->ToLower() == ".wav")
	{
		CurrentSound.extention = ExtentionType::WAV;
		LoadWav(filePath);
	}
	else if (System::IO::Path::GetExtension(managedFilePath)->ToLower() == ".ogg")
	{
		CurrentSound.extention = ExtentionType::OGG;
		LoadOgg(filePath);
	}

	return 0;
}


int SoundPlayer::LoadOgg(const char* _filePath) {

	// Ouverture du fichier
	char fileName[_MAX_PATH] = { "" };
	for (int i = 0; i < strlen(_filePath); i++)
	{
		fileName[i] = _filePath[i];
	}

	FILE* pOggVorbisFile = fopen(fileName, "rb");

	if (!pOggVorbisFile)
	{
		ALFWprintf("Could not find %s\n", fileName);
		ShutdownVorbisFile();
		ALFWShutdownOpenAL();
		ALFWShutdown();
		return 1;
	}

	// Create an OggVorbis file stream
	if (fn_ov_open_callbacks(pOggVorbisFile, &sOggVorbisFile, NULL, 0, sCallbacks) != 0) {
		std::cerr << "Failed to open OggVorbis file" << std::endl;
		fclose(pOggVorbisFile);
		return 1;
	}

	// Get information about the file (Channels, Format, and Frequency)
	psVorbisInfo = fn_ov_info(&sOggVorbisFile, -1);
	if (!psVorbisInfo) {
		std::cerr << "Failed to get OggVorbis file information" << std::endl;
		return 1;
	}

	ulFrequency = psVorbisInfo->rate;
	ulChannels = psVorbisInfo->channels;

	if (ulChannels == 1) {
		ulFormat = AL_FORMAT_MONO16;
		ulBufferSize = ulFrequency >> 1;
		ulBufferSize -= (ulBufferSize % 2);
	}
	else if (ulChannels == 2) {
		ulFormat = AL_FORMAT_STEREO16;
		ulBufferSize = ulFrequency;
		ulBufferSize -= (ulBufferSize % 4);
	}
	else if (ulChannels == 4) {
		ulFormat = alGetEnumValue("AL_FORMAT_QUAD16");
		ulBufferSize = ulFrequency * 2;
		ulBufferSize -= (ulBufferSize % 8);
	}
	else if (ulChannels == 6) {
		ulFormat = alGetEnumValue("AL_FORMAT_51CHN16");
		ulBufferSize = ulFrequency * 3;
		ulBufferSize -= (ulBufferSize % 12);
	}
	else {
		std::cerr << "Unsupported number of channels" << std::endl;
		return 1;
	}

	// Allocate a buffer for decoded data
	pDecodeBuffer = (char*)malloc(ulBufferSize);
	if (!pDecodeBuffer) {
		std::cerr << "Failed to allocate memory for decoded OggVorbis data" << std::endl;
		fn_ov_clear(&sOggVorbisFile);
		return 1;
	}

	// Fill Buffers with decoded audio data
	for (iLoop = 0; iLoop < NUMBUFFERS; iLoop++) {
		DecodeAndQueueBuffers();
	}

	// Start playing source
	IsPlaying = 0;
	alSourcePlay(uiSource);

	return 0;
}

int SoundPlayer::LoadWav(const char* _filePath) {

	alGenBuffers(1, &uiBuffer);
	// Load Wave file into OpenAL Buffer
	if (!ALFWLoadWaveToBuffer(_filePath, uiBuffer))
	{
		ALFWprintf("Failed to load %s\n", _filePath);
		return 1;
	}
	// Generate a Source to playback the Buffer
	alGenSources(1, &uiSource);

	// Attach Source to Buffer
	alSourcei(uiSource, AL_BUFFER, uiBuffer);
	//pour le volume sonore
	alSourcef(uiSource, AL_GAIN, volume);
	// Play Source

	IsPlaying = true;
	alSourcePlay(uiSource);

	return 0;
}

void SoundPlayer::SetVolume(float _volume) {
	// clamp
	volume = _volume;
	if (volume < 0.f)
		volume = 0.f;
	else if (volume > 1.f)
		volume = 1.f;

	// set volume
	alSourcef(uiSource, AL_GAIN, volume);
}

unsigned long SoundPlayer::Play() {
	IsPlaying = true;
	alSourcePlay(uiSource);
	return 0;
}

void SoundPlayer::Pause() {
	IsPlaying = false;
	alSourcePause(uiSource);
}

void SoundPlayer::Resume() {
	IsPlaying = true;
	alSourcePlay(uiSource);
}

void SoundPlayer::Stop() {
	IsPlaying = false;
	alSourceStop(uiSource);
	alSourcei(uiSource, AL_BUFFER, 0);
}

unsigned long SoundPlayer::DecodeAndQueueBuffers() {
	ulBytesWritten = DecodeOggVorbis(&sOggVorbisFile, pDecodeBuffer, ulBufferSize, ulChannels);
	if (ulBytesWritten) {
		alBufferData(uiBuffers[iLoop], ulFormat, pDecodeBuffer, ulBytesWritten, ulFrequency);
		alSourceQueueBuffers(uiSource, 1, &uiBuffers[iLoop]);
		return ulBytesWritten;
	}
	return 0;
}

void InitVorbisFile()
{
	if (g_bVorbisInit)
		return;

	// Try and load Vorbis DLLs (VorbisFile.dll will load ogg.dll and vorbis.dll)
	g_hVorbisFileDLL = LoadLibrary(_T("vorbisfile.dll"));
	if (g_hVorbisFileDLL)
	{
		fn_ov_clear = (LPOVCLEAR)GetProcAddress(g_hVorbisFileDLL, "ov_clear");
		fn_ov_read = (LPOVREAD)GetProcAddress(g_hVorbisFileDLL, "ov_read");
		fn_ov_pcm_total = (LPOVPCMTOTAL)GetProcAddress(g_hVorbisFileDLL, "ov_pcm_total");
		fn_ov_info = (LPOVINFO)GetProcAddress(g_hVorbisFileDLL, "ov_info");
		fn_ov_comment = (LPOVCOMMENT)GetProcAddress(g_hVorbisFileDLL, "ov_comment");
		fn_ov_open_callbacks = (LPOVOPENCALLBACKS)GetProcAddress(g_hVorbisFileDLL, "ov_open_callbacks");

		if (fn_ov_clear && fn_ov_read && fn_ov_pcm_total && fn_ov_info &&
			fn_ov_comment && fn_ov_open_callbacks)
		{
			g_bVorbisInit = true;
		}
	}
}

void ShutdownVorbisFile()
{
	if (g_hVorbisFileDLL)
	{
		FreeLibrary(g_hVorbisFileDLL);
		g_hVorbisFileDLL = NULL;
	}
	g_bVorbisInit = false;
}

unsigned long DecodeOggVorbis(OggVorbis_File* psOggVorbisFile, char* pDecodeBuffer, unsigned long ulBufferSize, unsigned long ulChannels)
{
	int current_section;
	long lDecodeSize;
	unsigned long ulSamples;
	short* pSamples;

	unsigned long ulBytesDone = 0;
	while (1)
	{
		lDecodeSize = fn_ov_read(psOggVorbisFile, pDecodeBuffer + ulBytesDone, ulBufferSize - ulBytesDone, 0, 2, 1, &current_section);
		if (lDecodeSize > 0)
		{
			ulBytesDone += lDecodeSize;

			if (ulBytesDone >= ulBufferSize)
				break;
		}
		else
		{
			break;
		}
	}

	// Mono, Stereo and 4-Channel files decode into the same channel order as WAVEFORMATEXTENSIBLE,
	// however 6-Channels files need to be re-ordered
	if (ulChannels == 6)
	{
		pSamples = (short*)pDecodeBuffer;
		for (ulSamples = 0; ulSamples < (ulBufferSize >> 1); ulSamples += 6)
		{
			// WAVEFORMATEXTENSIBLE Order : FL, FR, FC, LFE, RL, RR
			// OggVorbis Order            : FL, FC, FR,  RL, RR, LFE
			Swap(pSamples[ulSamples + 1], pSamples[ulSamples + 2]);
			Swap(pSamples[ulSamples + 3], pSamples[ulSamples + 5]);
			Swap(pSamples[ulSamples + 4], pSamples[ulSamples + 5]);
		}
	}

	return ulBytesDone;
}

void Swap(short& s1, short& s2)
{
	short sTemp = s1;
	s1 = s2;
	s2 = sTemp;
}

size_t ov_read_func(void* ptr, size_t size, size_t nmemb, void* datasource)
{
	return fread(ptr, size, nmemb, (FILE*)datasource);
}

int ov_seek_func(void* datasource, ogg_int64_t offset, int whence)
{
	return fseek((FILE*)datasource, (long)offset, whence);
}

int ov_close_func(void* datasource)
{
	return fclose((FILE*)datasource);
}

long ov_tell_func(void* datasource)
{
	return ftell((FILE*)datasource);
}

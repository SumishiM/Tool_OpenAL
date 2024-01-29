#pragma once


#include "framework/Win32/Framework.h"
#include "Vorbis/vorbisfile.h"
#include <tchar.h>

using namespace System;

#define NUMBUFFERS              (4)
#define	SERVICE_UPDATE_PERIOD	(20)

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

class SoundPlayer {
public:
    SoundPlayer();
    ~SoundPlayer();

    int LoadOgg(const char* filePath);
    int LoadWav(const char* filePath);
    void SetVolume(float volume);
    unsigned long Play();
    void Pause();
    void Resume();
    void Stop();

    float volume = 0.5f;
    bool IsPlaying = false;

private:
    ALuint uiBuffers[NUMBUFFERS];
    ALuint uiSource;
    ALuint uiBuffer;
    ALint iState;
    ALint iLoop;
    ALint iBuffersProcessed, iTotalBuffersProcessed, iQueuedBuffers;
    unsigned long ulFrequency;
    unsigned long ulFormat;
    unsigned long ulChannels;
    unsigned long ulBufferSize;
    unsigned long ulBytesWritten;
    char* pDecodeBuffer;

    OggVorbis_File sOggVorbisFile;
    vorbis_info* psVorbisInfo;
    ov_callbacks sCallbacks;

    void Init();
    void Shutdown();
    unsigned long DecodeAndQueueBuffers();
};
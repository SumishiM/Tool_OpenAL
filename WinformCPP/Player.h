#pragma once

#include "Framework.h"
#include "Vorbis\vorbisfile.h"
#include <tchar.h>

using namespace System;

#define NUMBUFFERS              (4)
#define	SERVICE_UPDATE_PERIOD	(20)


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
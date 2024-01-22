#include "Player.h"
#include "../framework/Win32/Framework.h"


int InitWav() {
	// Initialize Framework
	ALFWInit();
	if (!ALFWInitOpenAL())
	{
		ALFWShutdown();
		return 0;
	}
}



int PlayWav(const char* fileName)
{
	ALFWprintf("Play Wav\n");

	ALuint      uiBuffer;
	ALuint      uiSource;
	ALint       iState;

	// Generate an AL Buffer
	alGenBuffers(1, &uiBuffer);

	// Load Wave file into OpenAL Buffer
	if (!ALFWLoadWaveToBuffer((char*)fileName, uiBuffer))
	{
		ALFWprintf("Failed to load %s\n", fileName);
	}

	// Generate a Source to playback the Buffer
	alGenSources(1, &uiSource);

	// Attach Source to Buffer
	alSourcei(uiSource, AL_BUFFER, uiBuffer);
	//pour boucler un son
	alSourcei(uiSource, AL_LOOPING, 1);
	// Play Source
	alSourcePlay(uiSource);

	/*
	do
	{
		Sleep(100);
		ALFWprintf(".");
		// Get Source State
		alGetSourcei(uiSource, AL_SOURCE_STATE, &iState);
	} while (iState == AL_PLAYING);
	*/

	// Clean up by deleting Source(s) and Buffer(s)
	/*
	alSourceStop(uiSource);
	alDeleteSources(1, &uiSource);
	alDeleteBuffers(1, &uiBuffer);

	ALFWShutdownOpenAL();

	ALFWShutdown();
	*/
	return 0;
}

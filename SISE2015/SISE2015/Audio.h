#ifndef _AUDIO_H
#define _AUDIO_H

#include <SDL_mixer.h>

class Audio
{
public:
	Audio();
	~Audio();

	void Play() const;
	void Pause() const;
	void Resume() const;
	void Stop() const;

private:
	Mix_Music* music;
};

#endif

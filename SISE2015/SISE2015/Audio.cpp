#include "Audio.h"

Audio::Audio()
{
	music = Mix_LoadMUS("music.mp3");
}

Audio::~Audio()
{
	if (music != nullptr)
	{
		Mix_FreeMusic(music);
		music = nullptr;
	}
}

void Audio::Play() const
{
	if (music == nullptr) return;

	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(music, -1);
	}
}

void Audio::Pause() const
{
	if (Mix_PlayingMusic() != 0)
	{
		if (Mix_PausedMusic() != 1)
		{
			Mix_PauseMusic();
		}
	}
}

void Audio::Resume() const
{
	if (Mix_PlayingMusic() != 0)
	{
		if (Mix_PausedMusic() == 1)
		{
			Mix_ResumeMusic();
		}
	}
}

void Audio::Stop() const
{
	Mix_HaltMusic();
}

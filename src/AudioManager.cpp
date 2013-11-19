
#include "AudioManager.h"

AudioManager::AudioManager()
: _isLoop(false), _volume(100), _pitch(1)
{
}


AudioManager::~AudioManager(void)
{
}

void AudioManager::addMusic(Audios audio)
{
	_fileNames.insert(std::pair<AudioID, Audios>(audio.getAudioID(), audio));
}

void AudioManager::play(AudioID theme)
{
	Audios t = _fileNames.at(theme);
	std::string filename = t.getPath();

	if (t.getAudioType() == TypeSound)
	{
		if (!_soundbuff.loadFromFile(filename))
			throw std::runtime_error("Sound " + filename + " could not be loaded.");
		_sound.setBuffer(_soundbuff);
		_sound.setLoop(t.getLoop());
		_sound.setVolume(_volume);
		_sound.setPitch(_pitch);
	}
	_sound.play();

	if (t.getAudioType() == TypeMusic)
	{
		if (!_music.openFromFile(filename))
			throw std::runtime_error("Music " + filename + " could not be loaded.");
		_music.setVolume(_volume);
		_music.setPitch(_pitch);
		_music.setLoop(t.getLoop());
	}
	_music.play();

}

void AudioManager::paused(bool ispaused)
{
	if (ispaused)
	{
		_music.pause();
		_sound.pause();
	}
	else
	{
		_music.play();
		_sound.play();
	}
}

void AudioManager::stop()
{
	_music.stop();
	_sound.stop();
}

void AudioManager::setVolume(float hisVolume)
{
	_volume = hisVolume;
}

float	AudioManager::getVolume()
{
	return _volume;
}

void	AudioManager::setLoop(bool loop)
{
	_isLoop = loop;
}

bool	AudioManager::getLoop()
{
	return _isLoop;
}

void	AudioManager::setPitch(float pitch)
{
	_pitch = pitch;
}

float	AudioManager::getPitch()
{
	return _pitch;
}

void AudioManager::refresh()
{
}
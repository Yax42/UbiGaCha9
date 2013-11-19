#include <string>
#include <map>
#include <iterator>
#include <iterator>
#include <iostream>
#include <utility>
#include <SFML\Audio.hpp>
#include "Audios.h"

class Audios;

class AudioManager
{
public:
	AudioManager();
	virtual ~AudioManager();
	void addMusic(Audios);
	void refresh();
	void play(AudioID);
	void paused(bool);
	void stop();
	void setVolume(float);
	float getVolume();
	void setLoop(bool);
	bool getLoop();
	void setPitch(float);
	float getPitch();

private:
	sf::Music _music;
	sf::SoundBuffer _soundbuff;
	sf::Sound _sound;
	std::map<const AudioID, const Audios> _fileNames;
	bool _isLoop;
	float _pitch;
	float _volume;
};
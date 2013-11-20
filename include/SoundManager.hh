#ifndef	_SOUNDMANAGER_HH_
#define _SOUNDMANAGER_HH_

#include	<string>
#include	<map>
#include	<SFML/Audio.hpp>
#include	"UbiException.hh"

typedef std::map<std::string, sf::SoundBuffer *> SoundBufferMap;
typedef std::map<std::string, sf::Sound> SoundMap;
typedef std::pair<std::string, sf::SoundBuffer *> SoundBufferPair;
typedef std::pair<std::string, sf::Sound> SoundPair;

class	SoundManager
{
public:
  ~SoundManager();

  static SoundManager		&getInstance();
  const sf::SoundBuffer		*getBuffer(const std::string &);
  sf::Sound			&getSound(const std::string &);

private:
  SoundManager();

  SoundBufferMap		_manageBuffer;
  SoundMap			_manageSound;
};

#endif	/* _SOUNDMANAGER_HH_ */

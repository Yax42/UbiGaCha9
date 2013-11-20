#include "SoundManager.hh"

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
  for (SoundBufferMap::iterator it = _manageBuffer.begin();
       it != _manageBuffer.end(); ++it)
    delete (it->second);
}

SoundManager &SoundManager::getInstance()
{
  static SoundManager soundManager;

  return (soundManager);
}

const sf::SoundBuffer *SoundManager::getBuffer(const std::string & path)
{
  SoundBufferMap::iterator it = _manageBuffer.find(path);

  if (it == _manageBuffer.end())
    {
      sf::SoundBuffer	*buffer = new sf::SoundBuffer();
      if (!buffer->loadFromFile(path))
	throw UbiException("Can't load sound from file: " + path);
      return (_manageBuffer.insert(SoundBufferPair(path, buffer)).first->second);
    }
  else
    return (it->second);
}

sf::Sound	&SoundManager::getSound(const std::string & path)
{
  SoundMap::iterator it = _manageSound.find(path);

  if (it == _manageSound.end())
    {
      sf::Sound	tmp;
      tmp.setBuffer(*(getBuffer(path)));
      return (_manageSound.insert(SoundPair(path, tmp)).first->second);
    }
  else
    return (it->second);
}

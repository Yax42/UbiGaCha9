#include "Audios.hh"

Audios::Audios(AudioType type, std::string path, AudioID id, bool loop)
: _type(type), _path(path), _id(id), _loop(loop)
{
}

Audios::Audios(const Audios &aud)
: _type(aud._type), _id(aud._id), _path(aud._path), _loop(aud._loop)
{}

Audios::~Audios(){}

std::string Audios::getPath()
{
	return _path;
}

AudioID		Audios::getAudioID()
{
	return _id;
}

AudioType Audios::getAudioType()
{
	return _type;
}

bool Audios::getLoop()
{
	return _loop;
}
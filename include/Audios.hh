#include <string>

typedef enum	e_AudioID
{
	MainMenu,
	GangnamStyle,
	Rayman
}				AudioID;

typedef enum	e_AudioType
{
	TypeSound,
	TypeMusic
}				AudioType;

class Audios
{
public:
	Audios(AudioType, std::string, AudioID, bool);
	Audios(const Audios &);
	virtual ~Audios();
	std::string getPath();
	AudioID getAudioID();
	AudioType getAudioType();
	bool getLoop();

private:
	bool _loop;
	AudioID _id;
	AudioType _type;
	std::string _path;
};
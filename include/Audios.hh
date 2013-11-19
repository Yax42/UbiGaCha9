#include <string>

typedef enum	e_AudioID
{
	Musique_1,
	Musique_2,
	Ambiance_Ville,
	Ambiance_Drone,
	Main_Menu
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
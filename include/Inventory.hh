#include <SFML/Graphics.hpp>

typedef enum	e_WeaponID
{
	STICK,
	SWORD,
	AXE,
	BOW
}				WeaponID;

class Inventory
{
public:
	Inventory();
	~Inventory();

	void addItem(WeaponID);
	void equipped(WeaponID);
	virtual void draw();

private:
	std::map<std::pair<WeaponID, sf::Sprite>, bool> _WeaponUsed;
};
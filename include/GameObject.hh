#ifndef		__GAMEOBJECT_HH__
#define		__GAMEOBJECT_HH__

#include <vector>
#include <SFML/Graphics.hpp>
#include "Asset.hh"
#include "Box.hh"

class GameObject
{
public:
	AGameObject(const Asset & asset, sf::Vector2f &pos, float size, bool collide = true);
	~AGameObject(){}
	const Box	&getBox() const {return (_box);};
	virtual void	update(float dt);
	void		draw();
	void		toBackPosition();
private:
	Asset		_asset;
	Box		_box;
	sf::Vector2f	_direction;
	sf::Vector2f	_backPos;
	float		_angle;
	bool		_collide;
};

typedef std::vector<AGameObject*> AGameObjectVector;

#endif	//	__GAMEOBJECT_HH__
>>>>>>> add quadtree and box for GameObject

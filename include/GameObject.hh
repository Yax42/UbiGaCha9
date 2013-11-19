#ifndef		__GAMEOBJECT_HH__
#define		__GAMEOBJECT_HH__

#include <vector>
#include <SFML/Graphics.hpp>
#include "Asset.hh"

class GameObject
{
public:
	GameObject(const Asset &asset, const sf::Vector2f &pos,
		   const sf::Vector2f &size, bool collide = true);
	~GameObject(){}
	const sf::FloatRect	&getBox() const {return (_box);};
	virtual void		update(float dt);
	void			draw();
	void			toBackPosition();
	void			dirX(float x) { _direction.x = x; }
	void			dirY(float y) { _direction.y = y; }


private:
	Asset			_asset;
	sf::FloatRect	_box;
	sf::Vector2f	_backPos;
	sf::Vector2f	_direction;
	float			_angle;
	bool			_collide;
};

typedef std::vector<GameObject*> GameObjectVector;

#endif	//	__GAMEOBJECT_HH__

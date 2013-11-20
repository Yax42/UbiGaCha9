#ifndef		__GAMEOBJECT_HH__
#define		__GAMEOBJECT_HH__

#include <vector>
#include <SFML/Graphics.hpp>
#include "Asset.hh"

enum EDirection
{
	DOWN,
	UP,
	RIGHT,
	LEFT
};

class GameObject
{
public:
	enum
	{
		DIE,
		STAND,
		WALK,
		ATTACK,
		ATTACK2,
	};

public:
	GameObject(const Asset &asset, const sf::Vector2f &pos,
		   const sf::Vector2f &size, float maxSpeed = 100, bool collide = true);
	~GameObject(){}

	const sf::FloatRect	&getBox() const {return (_box);};
	sf::Vector2f		getPos() const {return sf::Vector2f(_box.left, _box.top);}
	void			setPos(const sf::Vector2f &v) {_box.left = v.x; _box.top = v.y;}
	sf::Vector2f		getSize() const {return sf::Vector2f(_box.width, _box.height);}
	const sf::Vector2f	&getDir() const {return _direction;}
	sf::Vector2f		getCenterPos() const {return getPos() + getSize() / 2.f;}
	void			dirX(float x) { _direction.x = x; }
	void			dirY(float y) { _direction.y = y; }
	virtual bool		isDead();
	void			giveOrder(int order) { _order = order;}
	void			weapon(int v) { if (_state != ATTACK) _weapon = v;}
	int			weapon() { return _weapon;}

	virtual void update(float ft, size_t frameCount);
	virtual void  draw(sf::RenderTexture &window);
	virtual void toBackPosition();
	virtual bool collides(GameObject &obj);

protected:
	virtual void	updateSprite();

	Asset			_asset;
	sf::Vector2f	_backPos;
	sf::Vector2f	_direction;
	int				_orientation;
	float			_angle;
	float			_maxSpeed;
	int				_state;
	int				_stateCount;
	int				_order;
	int				_weapon;
public:

	sf::FloatRect	_box;
	bool			_collide;
	int				_type;//0mur 1gentil 2mechant 3exit
	int				_mobType;
};

typedef std::vector<GameObject*> GameObjectVector;

#endif	//	__GAMEOBJECT_HH__

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
		ATTACK
	};

public:
	GameObject(const Asset &asset, const sf::Vector2f &pos,
		   const sf::Vector2f &size, float maxSpeed = 100, bool collide = true);
	virtual ~GameObject(){}

	const sf::FloatRect	&getBox() const {return (_box);};

	virtual void		update(float dt, size_t frameCount);
	void			draw(sf::RenderTexture &window);
	virtual void			toBackPosition();
	bool			collides(const GameObject &obj) const;

	void			setPos(const sf::Vector2f &v) {_box.left = v.x; _box.top = v.y;}

	sf::Vector2f		getPos() const {return sf::Vector2f(_box.left, _box.top);}
	const sf::Vector2f	&getDir() const {return _direction;}
	void			dirX(float x) { _direction.x = x; }
	void			dirY(float y) { _direction.y = y; }

	virtual void		update(float dt, size_t frameCount);
	void			draw(sf::RenderTexture &window);
	void			toBackPosition();
	bool			collides(const GameObject &obj) const;
	virtual bool			isDead();
	void			giveOrder(int order) { _order = order;}
	void			weapon(int v) { if (_state != ATTACK) _weapon = v;}
	int			weapon() { return _weapon;}

protected:
	virtual void	updateSprite();

	Asset			_asset;
	sf::FloatRect	_box;
	sf::Vector2f	_backPos;
	sf::Vector2f	_direction;
	int				_orientation;
	float			_angle;
	bool			_collide;
	float			_maxSpeed;
	int				_state;
	int				_stateCount;
	int				_order;
	int				_weapon;
public:

	int				_type;//0mur 1gentil 2mechant
	int				_mobType;
};

typedef std::vector<GameObject*> GameObjectVector;

#endif	//	__GAMEOBJECT_HH__

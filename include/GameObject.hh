#ifndef GAME_OBJECT_HH
#define GAME_OBJECT_HH

#include "Asset.hh"
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject(const Asset & asset, sf::Vector2f &pos, float size);
	~GameObject(){}
	virtual void	setPos(const sf::Vector2f &pos);
	virtual void	incPos(const sf::Vector2f &pos);
	virtual void	setSpeed(const sf::Vector2f &speed);
	virtual void	incSpeed(const sf::Vector2f &speed);
	virtual void	update(float dt);
	void	draw();

private:
	sf::Vector2f	_speed;
	sf::Vector2f	_pos;
	float			_angle;
	float			_hitBoxSize;
	Asset			_asset;
};

#endif
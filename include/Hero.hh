#ifndef HERO_HH
#define HERO_HH

#include "GameObject.hh"

class Hero : public GameObject
{
public:
	Hero(const Asset & asset, sf::Vector2f &pos);
	virtual ~Hero(){}
};

#endif
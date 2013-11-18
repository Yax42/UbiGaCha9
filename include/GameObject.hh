#include "Asset.hh"

class AGameObject
{
public:
	AGameObject(const Asset & asset, sf::Vector2f &pos, float size);
	~AGameObject(){}
	virtual void	update(float dt);
	void	draw();
private:
	sf::Vector2f	_speed;
	sf::Vector2f	_pos;
	float			_angle;
	float			_hitBoxSize;
	Asset			_asset;
};
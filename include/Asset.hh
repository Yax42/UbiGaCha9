#ifndef ASSERT_HH
#define ASSERT_HH

#include "AssetDescriptor.hh"

class Asset
{
public:
	~Asset(){}
	Asset(const AssetDescriptor &assetDesc);
	void	setCurrentLine(int cur);
	void	resetSprite();
	void	update();
	void	draw(const sf::Vector2f &pos, float angle);

private:
	const AssetDescriptor	&_assetDesc;
	int						_curLine;
	int						_curFrame;
	sf::Sprite				_sprite;
};

#endif

#ifndef ASSERT_HH
#define ASSERT_HH

#include "AssetDescriptor.hh"

class Asset
{
public:
	Asset(const AssetDescriptor &assetDesc);
	~Asset() {}
	void	setCurrentLine(int cur);
	void	resetSprite();
	bool	update();
	void	draw(const sf::Vector2f &pos, float angle, sf::RenderTexture &window);
	int		getCount(int line);

private:
	const AssetDescriptor	&_assetDesc;
	int						_curLine;
	int						_curFrame;
	sf::Sprite				_sprite;
public:
	sf::Vector2f			_size;
};

#endif

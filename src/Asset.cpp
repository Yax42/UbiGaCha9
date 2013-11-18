#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Asset.hh"

Asset::Asset(const AssetDescriptor	&assetDesc) : _assetDesc(assetDesc), _curLine(0), _curFrame(0)
{
}


void	Asset::setCurrentLine(int cur)
{
	_curLine = _assetDesc.lines.size() % cur;
	_curFrame = -1;
	resetSprite();
}

void	Asset::resetSprite()
{
	if (_curFrame < 0)
		_curFrame = 0;
	_sprite.setTextureRect(sf::IntRect(
		_assetDesc.lines[_curLine].width * _curFrame,
		_assetDesc.lines[_curLine].totalHeight,
		_assetDesc.lines[_curLine].width,
		_assetDesc.lines[_curLine].height));
	_sprite.setOrigin(_assetDesc.lines[_curLine].width, _assetDesc.lines[_curLine].height);
}

void	Asset::update()
{
	_curFrame++;
	_curFrame %= _assetDesc.lines[_curLine].count;
	resetSprite();
}

void	Asset::draw(const sf::Vector2f &pos, float angle)
{
  _sprite.setRotation(angle);
  _sprite.setPosition(pos);
}

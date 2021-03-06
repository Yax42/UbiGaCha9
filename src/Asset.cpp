#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Asset.hh"

Asset::Asset(const AssetDescriptor &assetDesc)
  : _assetDesc(assetDesc), _curLine(0), _curFrame(0)
{
  _sprite.setTexture(_assetDesc.texture);
}


void        Asset::setCurrentLine(int cur)
{
  if (cur != _curLine)
    {
      _curLine = cur % _assetDesc.lines.size();
      _curFrame = -1;
    }
}

void        Asset::resetSprite()
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

bool        Asset::update()
{
  _curFrame++;
  bool        result = (_curFrame == _assetDesc.lines[_curLine].count);
  _curFrame %= _assetDesc.lines[_curLine].count;
  resetSprite();
  return (result);
}

void        Asset::draw(const sf::Vector2f &pos, float angle, sf::RenderTexture &window)
{
  _sprite.setPosition(pos + sf::Vector2f((_size.x + _assetDesc.lines[_curLine].width) / 2,  (_size.y + _assetDesc.lines[_curLine].height) /2));
  window.draw(_sprite);
}

int		Asset::getCount(int line)
{
	return (_assetDesc.lines[line %_assetDesc.lines.size()].count);
}

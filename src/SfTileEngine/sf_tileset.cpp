#include "SfTileEngine/sf_tileset.h"

#include "TinyXML/tinyxml2.h"
  using namespace tinyxml2;

#include "SfTileEngine/sf_tile.h"

/// Engine namespace
namespace sftile
{

/// Private engine namespace
namespace priv
{

////////////////////////////////////////////////////////////
SfTileset::SfTileset()
  : tile_dimensions(32, 32)
  , tiles()
  , tileset_images()
{}

////////////////////////////////////////////////////////////
SfTileset::SfTileset(const SfTileset& _copy)
  : tile_dimensions(_copy.tile_dimensions)
  , tiles(_copy.tiles)
  , tileset_images(_copy.tileset_images)
{}

////////////////////////////////////////////////////////////
SfTileset& SfTileset::operator=(const SfTileset& _copy)
{
  if (this != &_copy)
  {
    SfTileset temp(_copy);

    std::swap(tile_dimensions, temp.tile_dimensions);
    std::swap(tiles, temp.tiles);
    std::swap(tileset_images, temp.tileset_images);
  }

  return *this;
}


////////////////////////////////////////////////////////////
SfTileset::~SfTileset()
{}


////////////////////////////////////////////////////////////
SfTile SfTileset::GetTile(const unsigned int _id)
{
  return tiles.at(_id - 1);
}

////////////////////////////////////////////////////////////
const int SfTileset::GetNumTiles()
{
  return tiles.size();
}

////////////////////////////////////////////////////////////
void SfTileset::RenderTile(sf::RenderWindow& _window, const unsigned int _id, const float _x, const float _y)
{
  std::vector<std::pair<int, sf::Texture> >::iterator it = tileset_images.begin();
  SfTile tile = GetTile(_id);

  while (it != tileset_images.end())
    {
      std::vector<std::pair<int, sf::Texture> >::iterator back_it = it++;

      if (_id >= back_it->first && (_id < it->first || it == tileset_images.end()))
	{
	  sf::Sprite sprite(back_it->second, tile.GetRect());
	  sprite.setPosition(_x, _y);

	  _window.draw(sprite);
	  return ;
	}
    }
}

}

}

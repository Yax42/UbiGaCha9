#include "SfTileEngine/sf_tilemap.h"

#include "TinyXML/tinyxml2.h"
  using namespace tinyxml2;

#include "SfTileEngine/sf_camera.h"

namespace sftile
{

////////////////////////////////////////////////////////////
SfTilemap::SfTilemap()
  : camera(nullptr)
  , tileset()
  , tile_layers()
  , object_layers()
  , map_dimensions(-1, -1)
  , tile_dimensions(32, 32)
  , version(1.0)
{}


////////////////////////////////////////////////////////////
SfTilemap::SfTilemap(const SfTilemap& _copy)
  : camera(_copy.camera)
  , tileset(_copy.tileset)
  , tile_layers(_copy.tile_layers)
  , object_layers(_copy.object_layers)
  , map_dimensions(_copy.map_dimensions)
  , tile_dimensions(_copy.tile_dimensions)
  , version(_copy.version)
{}


////////////////////////////////////////////////////////////
SfTilemap& SfTilemap::operator=(const SfTilemap& _copy)
{
  if (this != &_copy)
  {
    SfTilemap temp(_copy);

    std::swap(camera, temp.camera);
    std::swap(tileset, temp.tileset);
    std::swap(tile_layers, temp.tile_layers);
    std::swap(object_layers, temp.object_layers);
    std::swap(map_dimensions, temp.map_dimensions);
    std::swap(tile_dimensions, temp.tile_dimensions);
  }

  return *this;
}


////////////////////////////////////////////////////////////
SfTilemap::~SfTilemap()
{
  camera = nullptr;
}


////////////////////////////////////////////////////////////
void SfTilemap::RegisterCamera(SfCamera* _camera)
{
  camera = _camera;
}


////////////////////////////////////////////////////////////
void SfTilemap::HandleEvents(sf::Event _evt)
{
  camera->HandleEvents(_evt);
}


////////////////////////////////////////////////////////////
void SfTilemap::Update()
{
  camera->Update();
}


////////////////////////////////////////////////////////////
void SfTilemap::Render(sf::RenderTexture& _window)
{
  sf::Vector2i offset = camera->GetTileOffset(tile_dimensions.x, tile_dimensions.y);
  sf::IntRect bounds = camera->GetBounds(tile_dimensions.x, tile_dimensions.y);

  for (int y = 0, tile_y = bounds.top; y < bounds.height; ++y, ++tile_y)
    for (int x = 0, tile_x = bounds.left; x < bounds.width; ++x, ++tile_x)
    {

      for (unsigned int l = 0; l < tile_layers.size(); ++l)
      {
        if (tile_x < 0 || tile_y < 0)
          continue;
        if (tile_x >= map_dimensions.x || tile_y >= map_dimensions.y)
          continue;

        int gid = tile_layers.at(l).GetTileGID(tile_x, tile_y);

        if (gid == 0)
          continue;

        const float pos_x = static_cast<float>(x * tile_dimensions.x - offset.x);
        const float pos_y = static_cast<float>(y * tile_dimensions.y - offset.y);
        tileset.RenderTile(_window, gid, pos_x, pos_y);
      }
    }
}

}

#include <algorithm>
#include "SfTileEngine/sf_tilemap_loader.h"

#include "TinyXML/tinyxml2.h"
using namespace tinyxml2;

#include "SfTileEngine/sf_tilemap.h"
#include "SfTileEngine/sf_tileset.h"
#include "SfTileEngine/sf_tile_layer.h"
#include "SfTileEngine/sf_tile.h"
#include "SfTileEngine/sf_object_layer.h"
#include "SfTileEngine/sf_object.h"

/// Engine namespace
namespace sftile
{

/// Private engine namespace
namespace priv
{


bool CheckPointer(const void* _ptr, string _error)
{
  if (!_ptr)
  {
    cout << _error << endl;
    return false;
  }
  return true;
}

bool pairTilesetImagesCompare(const std::pair<int, sf::Texture> &firstElem,
			      const std::pair<int, sf::Texture> &secondElem)
{
  return (firstElem.first < secondElem.first);
}

////////////////////////////////////////////////////////////
bool SfTilemapLoader::LoadTilemap(const string _path, SfTilemap& _tilemap)
{
  // Temporary map object
  SfTilemap temp_map;

  // Load TMX file in TinyXML
  XMLDocument doc;
  doc.LoadFile(_path.c_str());

  // Check for error in parsing
  if (doc.Error())
  {
    cout << "XML Parsing Error: " << doc.ErrorID() << endl;
    return false;
  }

  // Find the map element
  const XMLElement* map_element = doc.FirstChildElement("map");
  if (!CheckPointer(map_element, "Couldn't locate map element in map file"))
    return false;

  // Load all of the basic map data
  map_element->QueryFloatAttribute("version", &temp_map.version);
  map_element->QueryIntAttribute("width", &temp_map.map_dimensions.x);
  map_element->QueryIntAttribute("height", &temp_map.map_dimensions.y);
  map_element->QueryIntAttribute("tilewidth", &temp_map.tile_dimensions.x);
  map_element->QueryIntAttribute("tileheight", &temp_map.tile_dimensions.y);

  // Load the orientation of the tile map. Only orthogonal
  // is supported currently.
  string orient_str = map_element->Attribute("orientation");
  if (orient_str == "orthogonal")
    temp_map.orientation = SFTILE_ORIENT_ORTHOGONAL;
  else
  {
    cout << "SfTileEngine currently only supports orthogonal tile maps." << endl;
    temp_map.orientation = SFTILE_ORIENT_UNSUPPORTED;
    return false;
  }

  // Parse the tilesets in the tile map.
  const XMLElement* tileset_element = map_element->FirstChildElement("tileset");
  while (tileset_element)
  {
    if (!ParseTileset(tileset_element, temp_map.tileset))
    {
      cout << "Failed to parse tileset" << endl;
      return false;
    }
    tileset_element = tileset_element->NextSiblingElement("tileset");
  }
  // Don't let your pointer dangle... That's gross.
  tileset_element = nullptr;

  std::sort(temp_map.tileset.tileset_images.begin(), temp_map.tileset.tileset_images.end(),
	    pairTilesetImagesCompare);

  // Parse the tile layers
  const XMLElement* tile_layer_element = map_element->FirstChildElement("layer");
  while (tile_layer_element)
  {
    SfTileLayer temp_tile_layer;
    if (!ParseTileLayer(tile_layer_element, temp_tile_layer))
    {
      cout << "Failed to parse tile layer" << endl;
      return false;
    }
    else
    {
      temp_map.tile_layers.push_back(temp_tile_layer);
    }
    tile_layer_element = tile_layer_element->NextSiblingElement("layer");
  }
  tile_layer_element = nullptr;

  /// Parse the tile layers (object groups)
  const XMLElement* object_layer_element = map_element->FirstChildElement("objectgroup");
  while (object_layer_element)
  {
    SfObjectLayer temp_object_layer;
    if (!ParseObjectLayer(object_layer_element, temp_object_layer))
    {
      cout << "Failed to parse object layer" << endl;
      return false;
    }
    else
      temp_map.object_layers.push_back(temp_object_layer);
    object_layer_element = object_layer_element->NextSiblingElement("objectgroup");
  }
  object_layer_element = nullptr;

  _tilemap = temp_map;

  return true;
}

////////////////////////////////////////////////////////////
bool SfTilemapLoader::ParseTileset(const XMLElement* _element, SfTileset& _tileset)
{
  // First GID of the currently parsing tileset
  int first_gid = 0; _element->QueryIntAttribute("firstgid", &first_gid);
  _element->QueryIntAttribute("tilewidth", &_tileset.tile_dimensions.x);
  _element->QueryIntAttribute("tileheight", &_tileset.tile_dimensions.y);
  // Space around the tileset image
  int margin = 0; _element->QueryIntAttribute("margin", &margin);
  // Space in between each tile in the tileset
  int spacing = 0; _element->QueryIntAttribute("spacing", &spacing);

  // Load the image of the tileset and store
  // it in the SfTileset.
  const XMLElement* image_element = _element->FirstChildElement("image");
  if (!CheckPointer(image_element, "Couldn't locate image element in map file"))
    return false;

  // Load the tileset image
  string source("./ressource/maps/");
  source += image_element->Attribute("source");
  sf::Texture texture;
  if (!texture.loadFromFile(source))
  {
    cout << "Failed to load tileset image" << endl;
    return false;
  }
  _tileset.tileset_images.push_back(std::pair<int, sf::Texture>(first_gid, texture));
  int width = 0; image_element->QueryIntAttribute("width", &width);
  int height = 0; image_element->QueryIntAttribute("height", &height);
  image_element = nullptr;

  // Load all of the tiles into the tileset
  int gid = first_gid;
  for (int y = margin; y < height; y += spacing + _tileset.tile_dimensions.y)
    for (int x = margin; x < width; x += spacing + _tileset.tile_dimensions.x)
    {
      // We only save the rectangle around the tile
      // to help shorten loading times.
      // We can then load the texture every frame when we want
      // to display the tile.
      sf::IntRect rect(x, y, _tileset.tile_dimensions.x, _tileset.tile_dimensions.y);

      SfTile temp_tile(gid, rect);
      _tileset.tiles.push_back(temp_tile);
    }

  return true;
}

////////////////////////////////////////////////////////////
bool SfTilemapLoader::ParseTileLayer(const XMLElement* _element, SfTileLayer& _tile_layer)
{
  // Load the arbitrary name of the layer
  string name = _element->Attribute("name");
  _tile_layer.name = name;

  cout << "Loading layer: " << name << endl;

  // Load the dimensions of the layer
  sf::Vector2i layer_dimensions(0, 0);
  _element->QueryIntAttribute("width", &layer_dimensions.x);
  _element->QueryIntAttribute("height", &layer_dimensions.y);

  _tile_layer.layer_dimensions = layer_dimensions;

  float opacity = _element->FloatAttribute("opacity");
  _tile_layer.opacity = opacity;

  bool visible = _element->IntAttribute("visible");
  _tile_layer.visible = visible;

  // Load the data node
  const XMLElement* data = _element->FirstChildElement("data");

  // Find out the encoding of the data
  string encoding_attr = (data->Attribute("encoding") != NULL) ? data->Attribute("encoding") : "xml";

  // Go-go-gadget, Parsers!
  if (encoding_attr == "xml" && !ParseXmlTileLayer(data, _tile_layer))
    return false;
  else if (encoding_attr == "base64" && !ParseBase64TileLayer(data, _tile_layer))
    return false;
  else if (encoding_attr == "csv" && !ParseCsvTileLayer(data, _tile_layer))
    return false;
  else
    return true;
}


////////////////////////////////////////////////////////////
bool SfTilemapLoader::ParseXmlTileLayer(const XMLElement* _element, SfTileLayer& _tile_layer)
{
  const XMLElement* tile = _element->FirstChildElement("tile");

  for (int y = 0; y < _tile_layer.layer_dimensions.y; ++y)
  {
    vector<int> temp;
    for (int x = 0; x < _tile_layer.layer_dimensions.x; ++x)
    {
      int gid = tile->IntAttribute("gid");

      temp.push_back(gid);

      tile = tile->NextSiblingElement("tile");
    }
    _tile_layer.tile_gids.push_back(temp);
  }
  // Voila! It's a boy!
  return true;
}


////////////////////////////////////////////////////////////
bool SfTilemapLoader::ParseBase64TileLayer(const XMLElement* _element, SfTileLayer& _tile_layer)
{
  cout << "Cannot parse Base64 data" << endl;
  return false;
}


////////////////////////////////////////////////////////////
bool SfTilemapLoader::ParseCsvTileLayer(const XMLElement* _element, SfTileLayer& _tile_layer)
{
  cout << "Cannot parse CSV data" << endl;
  return false;
}


////////////////////////////////////////////////////////////
bool SfTilemapLoader::ParseObjectLayer(const tinyxml2::XMLElement* _element, SfObjectLayer& _object_layer)
{
  string name = _element->Attribute("name");
  _object_layer.name = name;

  cout << "Loading object layer: " << name << endl;

  int width = _element->IntAttribute("width");
  int height = _element->IntAttribute("height");
  _object_layer.layer_dimensions = sf::Vector2i(width, height);

  float opacity = _element->FloatAttribute("opacity");
  _object_layer.opacity = opacity;

  bool visible = _element->IntAttribute("visible");
  _object_layer.visible = visible;

  const XMLElement* object = _element->FirstChildElement("object");
  while (object)
  {
    SfObject temp_object;
    if (!ParseObject(object, temp_object))
    {
      cout << "Failed to parse object" << endl;
      return false;
    }
    else
      _object_layer.objects.push_back(temp_object);

    object = object->NextSiblingElement("object");
  }

  object = nullptr;

  return true;
}


////////////////////////////////////////////////////////////
bool SfTilemapLoader::ParseObject(const tinyxml2::XMLElement* _element, SfObject& _object)
{
  string name;
  if (_element->Attribute("name"))
    name = _element->Attribute("name");
  _object.name = name;

  string type;
  if (_element->Attribute("type"))
    type = _element->Attribute("type");
  _object.string_type = type;

  int x = _element->IntAttribute("x");
  int y = _element->IntAttribute("y");
  _object.position = sf::Vector2i(x, y);

  int width = _element->IntAttribute("width");
  int height = _element->IntAttribute("height");
  _object.dimensions = sf::Vector2i(width, height);

  float rotation = _element->FloatAttribute("rotation");
  _object.rotation = rotation;

  int gid = -1;
  _element->QueryIntAttribute("gid", &gid);
  _object.gid = gid;

  bool visible = _element->IntAttribute("visible");
  _object.visible = visible;

  ObjectType object_type;
  if (gid != -1)
    object_type = SF_OBJECT_TYPE_TILE;
  else
    object_type = SF_OBJECT_TYPE_UNKNOWN;
  const XMLElement *child_element = _element->FirstChildElement();
  if (child_element != nullptr)
    {
      std::string child_name = child_element->Name();

      if (child_name == "properties")
	{
	  const XMLElement *property_element = child_element->FirstChildElement("property");

	  while (property_element != nullptr)
	    {
	      std::string property_name = property_element->Attribute("name");

	      if (property_name == "id")
		{
		  int id = -1;
		  property_element->QueryIntAttribute("value", &id);
		  _object.id = id;
		}
	      property_element = property_element->NextSiblingElement("property");
	    }
	}
      child_element = child_element->NextSiblingElement();
    }
  return true;
}

}

}

#ifndef ASSET_DESCRIPTOR_HH
#define ASSET_DESCRIPTOR_HH

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

struct AssetLine
{
	int				height;
	int				width;
	int				count;
	int				totalHeight;
	~AssetLine(){ }
	AssetLine(int h, int w, int c) :
		height(h), width(w), count(c), totalHeight(0)
	{}
};
struct AssetDescriptor
{
public:
	AssetDescriptor() {}
	AssetDescriptor(const std::string &name);
	~AssetDescriptor(){}

	void   addLine(AssetLine &line);
	void   addLine(int h, int w, int c);
	std::vector<AssetLine>	lines;
	sf::Texture				texture;
};

#endif

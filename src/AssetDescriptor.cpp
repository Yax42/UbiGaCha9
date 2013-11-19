#include <iostream>

#include "AssetDescriptor.hh"

AssetDescriptor::AssetDescriptor(const std::string &name)
{
	if (texture.loadFromFile(name) == false)
	{
		std::cerr << "Error cannot load " << name << std::endl;
	}
}

void	AssetDescriptor::addLine(AssetLine &line)
{
	if (lines.size() > 1)
		line.totalHeight = lines[lines.size() - 1].totalHeight + lines[lines.size() - 1].height;
	lines.push_back(line);
}

void   AssetDescriptor::addLine(int h, int w, int c)
{
	addLine(AssetLine(h, w, c));
}
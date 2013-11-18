#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Asset
{
public:
	struct Line
	{
		int				height;
		int				width;
		int				count;
		int				totalHeight;
		~Line(){ }
		Line(int h, int w, int c) :
			height(h), width(w), count(c), totalHeight(0)
		{}
	};
public:
	~Asset(){}
	Asset(const std::string &name);
	void	setLine(Line &line);
	void	setCurrentLine(int cur);
	void	resetSprite();
	void	update();
	void	draw(const sf::Vector2f &pos, float angle);

private:
	int				_curLine;
	int				_curFrame;
	std::vector<Line>	_lines;
	sf::Texture		_texture;
	sf::Sprite		_sprite;
};

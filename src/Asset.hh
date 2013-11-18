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
	Asset(const &sf::string name);
	~Asset(){}
	void	setLine(Line &line);
	void	setCurrentLine(int cur);
	void	getFrame(&sf::Sprite sprite);
	void	update();
	void	draw(const sf::Vector2f &_pos, float _angle);

private:
	int				_curLine;
	int				_curFrame;
	vector<Line>	_lines;
	sf::Texture		_texture;
	sf::Sprite		_sprite;
};
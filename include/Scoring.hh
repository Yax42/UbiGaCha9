#ifndef		__SCORING_H__
#define		__SCORING_H__

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <iostream>
#include "ILayer.hh"

class Scoring : public ILayer
{
public:
	Scoring(sf::IpAddress &, unsigned short, sf::RenderWindow &);
	virtual ~Scoring();
	std::string getScore() const;
	std::list<std::string> getScoreList() const;
	void setScoreList();
  static void sendScore(const std::string &, int, int);
	virtual bool update(sf::Event &);
	virtual void draw();
	virtual void run();

public:
	float score;

private:
	sf::RenderWindow &_window;
	std::list<std::string> _scoreList;
	std::string _score;
	sf::TcpSocket _socket;
	sf::IpAddress _ip;
	unsigned short _port;
	sf::Font		_font;
	sf::Sprite	_sprite;
	sf::Text	_text;
	State _state;
	sf::Texture	_select;
	sf::Music _music;
};

#endif	//	__SCORING_H__

#ifndef		__SCORING_H__
#define		__SCORING_H__

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <list>
#include <iostream>

class Scoring
{
public:
	Scoring(sf::IpAddress &, unsigned short);
	virtual ~Scoring();
	std::string getScore() const;
	std::list<std::string> getScoreList() const;
	void setScoreList();
	void sendScore();

private:
	std::list<std::string> _scoreList;
	std::string _score;
	sf::TcpSocket _socket;
	sf::IpAddress _ip;
	unsigned short _port;
	sf::Packet _packet;
};


#endif	//	__SCORING_H__

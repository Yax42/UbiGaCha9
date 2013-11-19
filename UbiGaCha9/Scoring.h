#include <SFML/Network.hpp>
#include <SFML\System.hpp>
#include <list>
#include <iostream>

class Scoring
{
public:
	Scoring(sf::IpAddress &, unsigned short);
	virtual ~Scoring();
	std::string getScore() const;
	std::list<const std::string> getScoreList() const;
	void setScoreList();
	void sendScore();

private:
	std::list<const std::string> _scoreList;
	std::string _score;
	sf::TcpSocket _socket;
	sf::IpAddress _ip;
	unsigned short _port;
	sf::Packet _packet;
};

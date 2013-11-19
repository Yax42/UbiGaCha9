#include "Scoring.h"


Scoring::Scoring(sf::IpAddress &ip, unsigned short port)
	: _ip(ip), _port(port)
{
	_score = "";
}


Scoring::~Scoring()
{
}

std::string	Scoring::getScore() const
{
	return _score;
}

std::list<const std::string> Scoring::getScoreList() const
{
	return _scoreList;
}

void Scoring::sendScore()
{
	sf::Socket::Status status = _socket.connect(_ip, _port);
	if (status != sf::Socket::Done)
		std::cerr << "Error: Can't connect to " << _ip << ":" << _port << std::endl;

	_score = _score == "" ? "" : _score;
	_packet << "SendScore " << _score;
	_socket.send(_packet);
	_socket.disconnect();
}

void Scoring::setScoreList()
{
	std::string tmpScore;
	size_t pos = 0;
	std::string received = "SCORE ";
	std::string token;
	std::string delimiter = ";";
	
	_socket.connect(_ip, _port);
	_socket.receive(_packet);
	_socket.disconnect();

	_packet >> tmpScore;
	if (!_scoreList.empty())
		_scoreList.clear();

	// Rempli la liste des Hi-Scores
	if (!tmpScore.find(received))
		return;
	tmpScore.erase(0, received.length());
	while ((pos = tmpScore.find(delimiter)) != std::string::npos)
	{
		token = tmpScore.substr(0, pos);
		_scoreList.push_back(token);
		tmpScore.erase(0, pos + delimiter.length());
	}
}
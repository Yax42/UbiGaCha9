#include "Scoring.hh"
#include "UbiException.hh"

Scoring::Scoring(sf::IpAddress &ip, unsigned short port, sf::RenderWindow &window)
: _ip(ip), _port(port), _window(window), _state(LEADER)
{
	std::string	path = "./ressource/font/arial.ttf";
	if (!_font.loadFromFile(path))
		throw UbiException("Error load Font");

	_select.loadFromFile("./ressource/quit.png");
	_scoreList.push_back("1 Stanilas 1500");
	_scoreList.push_back("2 Bernard 1300");
	_scoreList.push_back("3 Aude 500");
	_scoreList.push_back("4 Claude 300");
	_scoreList.push_back("5 Barbara 15");
}


Scoring::~Scoring()
{
}

std::string	Scoring::getScore() const
{
	return _score;
}

std::list<std::string> Scoring::getScoreList() const
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
	sf::Packet packet;
	packet << "GetScore";
	_socket.send(packet);
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

bool Scoring::update(sf::Event & event)
{
	return (false);
}

void Scoring::draw()
{
	_text.setFont(_font);
	_text.setString("Hi-Scores");
	_text.setCharacterSize(16);
	_text.setColor(sf::Color::White);
	_text.setPosition(75, 0);
	_window.draw(_text);
	size_t i = 50;
	for (std::list<std::string>::iterator it = _scoreList.begin(); it != _scoreList.end(); ++it)
	{
		std::string t = *it;
		_text.setFont(_font);
		_text.setString(t);
		_text.setCharacterSize(12);
		_text.setColor(sf::Color::Green);
		_text.setPosition(75, i);
		_window.draw(_text);
		i += 25;
	}
	_sprite.setTexture(_select);
	_sprite.setColor(sf::Color::White);
	_sprite.setPosition(220, 200);
	_sprite.setScale(0.2, 0.2);
	_window.draw(_sprite);
}

void Scoring::run()
{
	while (_window.isOpen())
	{
		sf::Event event;
		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_window.close();
			if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::Return)
				_state = MENU;
		}
		if (_state == MENU)
			return;
		this->update(event);
		_window.clear();
		this->draw();
		_window.display();
	}
}
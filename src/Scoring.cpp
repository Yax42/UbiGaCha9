#include "Scoring.hh"
#include "UbiException.hh"

Scoring::Scoring(sf::IpAddress &ip, unsigned short port, sf::RenderWindow &window)
: _ip(ip), _port(port), _window(window), _state(LEADER)
{
	std::string	path = "./ressource/font/arial.ttf";
	if (!_font.loadFromFile(path))
		throw UbiException("Error load Font");

	_select.loadFromFile("./ressource/textures/quit.png");
	setScoreList();
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


	std::string s = "SendScore " + _score + "\n";
	_socket.send(s.c_str(), s.size() + 1);
	_socket.disconnect();
}

void Scoring::setScoreList()
{
	std::string tmpScore;
	size_t pos = 0;
	char buffer[1024];
	size_t dataReceived = 0;
	std::string received = "SCORE ";
	std::string token;
	std::string delimiter = ";";

	_socket.connect(_ip, _port);
	std::string s = "GetScore\n";
	_socket.send(s.c_str(), s.size() + 1);
	_socket.receive(buffer, sizeof(buffer), dataReceived);
	std::string data(buffer, dataReceived);
	_socket.disconnect();

	if (!_scoreList.empty())
		_scoreList.clear();

	// Rempli la liste des Hi-Scores
	data.erase(0, received.length());
	while ((pos = data.find(delimiter)) != std::string::npos)
	{
		token = data.substr(0, pos);
		_scoreList.push_back(token);
		data.erase(0, pos + delimiter.length());
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
	_sprite.setScale(1, 1);
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
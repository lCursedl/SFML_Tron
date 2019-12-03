#pragma once
#include "CPlayer.h"
#include <iostream>
#include "SFML/Network.hpp"

struct ClientStruct
{
	sf::TcpSocket cpSocket;
	CPlayer * cpPlayer;

	ClientStruct();
	~ClientStruct();
};

class CGame
{
public:
	CGame();
	~CGame();

	virtual void run() = 0;
	virtual void processEvents() = 0;
	virtual void update(Time dTime) = 0;
	virtual void render() = 0;

	
};

//Operators

//sf::Packet & operator >> (sf::Packet & packet, DIRECTION &data);
//sf::Packet & operator << (sf::Packet & packet, DIRECTION &data);
sf::Packet & operator >> (sf::Packet & packet, sf::Vector2i &data);
sf::Packet & operator << (sf::Packet & packet, const sf::Vector2i &data);
sf::Packet & operator >> (sf::Packet & packet, sf::Color &data);
sf::Packet & operator << (sf::Packet & packet, const sf::Color &data);

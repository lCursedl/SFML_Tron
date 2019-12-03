#include "CGame.h"

CGame::CGame(){}

CGame::~CGame(){}

//sf::Packet & operator>>(sf::Packet & packet, DIRECTION & data)
//{
//	return packet >> data;
//}
//
//sf::Packet & operator<<(sf::Packet & packet, DIRECTION & data)
//{
//	return packet << data;
//}

sf::Packet & operator>>(sf::Packet & packet, sf::Vector2i & data)
{
	return packet >> data.x >> data.y;
}

sf::Packet & operator<<(sf::Packet & packet, const sf::Vector2i & data)
{
	return packet << data.x << data.y;
}

sf::Packet & operator>>(sf::Packet & packet, sf::Color & data)
{
	return packet >> data.r >> data.g >> data.b;
}

sf::Packet & operator<<(sf::Packet & packet, const sf::Color & data)
{
	return packet << data.r << data.g << data.b;
}

ClientStruct::ClientStruct()
{
	cpPlayer = nullptr;
}

ClientStruct::~ClientStruct()
{
	if (cpPlayer != nullptr)
	{
		delete cpPlayer;
	}
}

#pragma once
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include <string>

using namespace sf;

class CPlayer
{
public:
	CPlayer();
	CPlayer(Vector2i position, Color color, std::string name, int Dir);
	~CPlayer();

	void update(Time dTime);
	void input(Keyboard::Key k);
	void renderToTexture();
	bool directionChange();

	int mDir;

	Vector2f mPos;
	std::string mName;
	Color mColor;
	CircleShape mCircle;
	int mSpeed;
	RenderTexture T;
	Sprite S;

	int actualDir;
	int newDir;
};
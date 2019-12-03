#include "CPlayer.h"

CPlayer::CPlayer(){}

CPlayer::CPlayer(Vector2i position, Color color, std::string name, int Dir)
{
	mPos = static_cast<Vector2f>(position);
	mColor = color;
	mName = name;
	mCircle.setRadius(1);
	mCircle.setPosition(mPos);
	mCircle.setFillColor(color);
	mDir = Dir;
	newDir = mDir;
	actualDir = mDir;
	mSpeed = 70;
	T.create(800, 600);
	T.setSmooth(true);
	S.setTexture(T.getTexture());
}

CPlayer::~CPlayer(){}

void CPlayer::update(Time dTime)
{
	Vector2f movement(0, 0);
	switch (actualDir)
	{
		//UP
	case 0:
		movement.y -= mSpeed;
		break;
		//DOWN
	case 1:
		movement.y += mSpeed;
		break;
		//LEFT
	case 2:
		movement.x -= mSpeed;
		break;
		//RIGHT
	case 3:
		movement.x += mSpeed;
		break;
	}
	renderToTexture();
	mCircle.move(movement * dTime.asSeconds());
}

void CPlayer::input(Keyboard::Key k)
{
	switch (k)
	{
	case sf::Keyboard::Left:
		if (actualDir != RIGHT)
		{
			newDir = LEFT;
		}
		break;
	case sf::Keyboard::Right:
		if (actualDir != LEFT)
		{
			newDir = RIGHT;
		}
		break;
	case sf::Keyboard::Up:
		if (actualDir != DOWN)
		{
			newDir = UP;
		}
		break;
	case sf::Keyboard::Down:
		if (actualDir != UP)
		{
			newDir = DOWN;
		}
		break;
	}
}

void CPlayer::renderToTexture()
{
	T.draw(mCircle);
	T.display();
}

bool CPlayer::directionChange()
{
	if (actualDir != newDir)
	{
		actualDir = newDir;
		return true;
	}
	return false;
}

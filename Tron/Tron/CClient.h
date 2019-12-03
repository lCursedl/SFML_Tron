#pragma once
#include "CGame.h"
class CClient : public CGame
{
public:
	CClient();
	~CClient();

	void run();
	void processEvents();
	void update(Time dTime);
	void render();
	void checkCollisions(CPlayer * Player);

	RenderWindow mWindow;
	Time TimePerFrame;

	// Player pointers
	CPlayer * mPlayer;
	CPlayer * mRemote1;
	CPlayer * mRemote2;

	// Host 
	ClientStruct * mHost;

	bool runGame;
};
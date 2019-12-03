#include "CHost.h"

CHost::CHost() : mWindow(VideoMode(800, 600), "SFML Tron_Host")
{
	//Inicializacion de variables locales y construccion de punteros
	TimePerFrame = seconds(1.0f / 60.0f);
	std::string tempName;
	std::cout << "Introduzca un nombre de usuario: ";
	std::cin >> tempName;
	mPlayer = new CPlayer(Vector2i(5, 10), Color::Red, tempName, RIGHT);
	runGame = true;
	Remote1 = new ClientStruct();
	Remote2 = nullptr;
	Remote3 = nullptr;
}

CHost::~CHost()
{
	//Liberar memoria utilizada
	delete mPlayer;
	if (Remote1 != nullptr)
	{
		delete Remote1;
	}
	if (Remote2 != nullptr)
	{
		delete Remote2;
	}
	if (Remote3 != nullptr)
	{
		delete Remote3;
	}
}

void CHost::run()
{
	//Declaracion de variables para manejo de tiempo y delta
	Clock GameClock;
	Time TimeSinceLastUpdate = Time::Zero;
	//Se comienza a escuchar en el puerto especificado
	HostListener.listen(4500);
	if (HostListener.accept(Remote1->cpSocket) == sf::Socket::Done)
	{
		std::cout << "Recibiendo jugador...\n";
		Packet p;
		if (Remote1->cpSocket.receive(p) == sf::Socket::Done)
		{
			std::string name;
			Vector2i pos = {5, 10};
			p >> name;
			std::cout << "Se conecto " << name << " a la partida.\n";
			p.clear();
			//Se envian los datos del host al cliente
			p << pos << mPlayer->mColor << mPlayer->mName << mPlayer->mDir;			
			if (Remote1->cpSocket.send(p) != Socket::Done)
			{
				std::cout << "Error al mandar datos de host a cliente.\n";
			}
			p.clear();

			//Se crea la instancia del cliente en el host
			Remote1->cpPlayer = new CPlayer(Vector2i(790, 590), sf::Color::Blue, name, LEFT);			
			pos = { 790, 590 };
			//Se empaquetan los datos de la instancia para indicarle al cliente como inicializarse
			p << pos << Remote1->cpPlayer->mColor << Remote1->cpPlayer->mDir;
			if (Remote1->cpSocket.send(p) == Socket::Done)
			{
				std::cout << name << " asignado en el espacio 2.\n";
				Remote1->cpSocket.setBlocking(false);
			}
			else
			{
				std::cout << "Error al asignar " << name << " a la partida.\n";
				delete Remote1->cpPlayer;
			}
			//Se entra al ciclo de juego
			while (runGame)
			{
				TimeSinceLastUpdate += GameClock.restart();
				while (TimeSinceLastUpdate > TimePerFrame)
				{
					TimeSinceLastUpdate -= TimePerFrame;
					processEvents();
					update(TimePerFrame);
				}
				render();
			}
		}
	}
	
	mWindow.close();
}

void CHost::processEvents()
{
	Event GameEvent;
	while (mWindow.pollEvent(GameEvent))
	{
		switch (GameEvent.type)
		{
		case Event::KeyPressed:
			mPlayer->input(GameEvent.key.code);
			break;
		case Event::Closed:
			runGame = false;
		}
	}
}

void CHost::update(Time dTime)
{
	Packet P;	
	//Recibir paquetes de clientes remotos	
	if (Remote1->cpSocket.receive(P) == Socket::Done)
	{
		std::cout << "Se recibio informacion de cliente.\n";
		P >> Remote1->cpPlayer->actualDir;
		P.clear();
	}
	//Si hubo un cambio en la direccion del jugador
	if (mPlayer->directionChange())
	{
		//Se empaqueta la direccion actual
		P << mPlayer->actualDir;
		//Enviar informacion de host actual
		if (Remote1->cpSocket.send(P) != Socket::Done)
		{
			std::cout << "Error al enviar informacion de host a cliente.\n";
		}
		P.clear();
	}
	//Actualizar host y clientes
	mPlayer->update(dTime);
	Remote1->cpPlayer->update(dTime);
	//Revisar colisiones de host y clientes
	checkCollisions(mPlayer);
	checkCollisions(Remote1->cpPlayer);
}

void CHost::render()
{
	mWindow.clear();
	mWindow.draw(mPlayer->S);
	mWindow.draw(Remote1->cpPlayer->S);
	mWindow.display();
}

void CHost::checkCollisions(CPlayer * Player)
{
	int posx = (int)Player->mCircle.getPosition().x;
	int posy = (int)Player->mCircle.getPosition().y;
	if (posx < 0)
	{
		Player->mCircle.setPosition(800.0, (float)posy);
	}
	if (posx > 800)
	{
		Player->mCircle.setPosition(0.0, (float)posy);
	}
	if (posy < 0)
	{
		Player->mCircle.setPosition((float)posx, 600.0);
	}
	if (posy > 600)
	{
		Player->mCircle.setPosition((float)posx, 0.0);
	}
	/*if (posx < 0 || posx > 800 || posy < 0 || posy > 600)
	{
		Player->mSpeed = 0;
	}
	else
	{
		if (field[posx][posy])
		{
			Player->mSpeed = 0;
		}
		field[posx][posy] = true;
	}*/
}
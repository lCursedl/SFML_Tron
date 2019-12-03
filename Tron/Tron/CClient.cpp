#include "CClient.h"

CClient::CClient() : mWindow(VideoMode(800, 600), "SFML Tron_Client")
{
	TimePerFrame = seconds(1.0f / 60.0f);
	mPlayer = nullptr;
	mHost = nullptr;
	mRemote1 = nullptr;
	mRemote2 = nullptr;
	runGame = true;
}

CClient::~CClient()
{
	//Liberar punteros utilizada
	delete mPlayer;	
	if (mHost != nullptr)
	{
		delete mHost;
		if (mRemote1 != nullptr)
		{
			delete mRemote1;
		}
		if (mRemote2 != nullptr)
		{
			delete mRemote2;
		}
	}
}

void CClient::run()
{
	Clock GameClock;
	std::string IP;
	Time TimeSinceLastUpdate = Time::Zero;
	//Se obtiene la direccion IP del host
	std::cout << "Introduzca una direccion IP: ";	
	std::cin >> IP;
	//Se inicializa la estructura con datos basicos del host
	mHost = new ClientStruct();
	std::cout << "Conectando a " << IP << "\n";
	if (mHost->cpSocket.connect(IP, 4500) == sf::Socket::Done)
	{
		std::string name;
		std::cout << "Introduzca un nombre de usuario: ";
		std::cin >> name;
		Packet p;
		p << name;
		if (mHost->cpSocket.send(p) != Socket::Done)
		{
			std::cout << "Error al mandar nombre de usuario al host.\n";
			return;
		}
		p.clear();
		if (mHost->cpSocket.receive(p) != Socket::Done)
		{
			std::cout << "Error al recibir datos del host para inicializar.\n";
			return;
		}
		Vector2i pos;
		Color tempColor;
		int tempDir;
		std::string hostName;
		//Se extraen los datos para inicializar la instancia del host en el cliente
		p >> pos >> tempColor >> hostName >> tempDir;
		mHost->cpPlayer = new CPlayer(pos, tempColor, hostName, tempDir);
		p.clear();
		//Se reciben los datos para inicializar la instancia del jugador
		if (mHost->cpSocket.receive(p) == Socket::Done)
		{
			p >> pos >> tempColor >> tempDir;
			mPlayer = new CPlayer(pos, tempColor, name, tempDir);
			mHost->cpSocket.setBlocking(false);
		}
		//Se entra en el ciclo de juego
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
		mWindow.close();
	}
	else
	{
		std::cout << "Sin respuesta del host.\n";
	}
}

void CClient::processEvents()
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

void CClient::update(Time dTime)
{
	Packet P;
	//Se detecta si hubo cambios de direccion
	if (mPlayer->directionChange())
	{
		//De haberlos, se empaqueta
		P << mPlayer->actualDir;
		if (mHost->cpSocket.send(P) != Socket::Done)
		{
			std::cout << "Error al mandar la informacion al host.\n";
		}
		P.clear();
	}
	//Se reciben cambios de direccion del servidor si es que hay
	if (mHost->cpSocket.receive(P) == Socket::Done)
	{
		std::cout << "Se recibio informacion del host.\n";
		P >> mHost->cpPlayer->actualDir;
		P.clear();
	}
		
	//Actualizar host y jugador
	mHost->cpPlayer->update(dTime);
	mPlayer->update(dTime);
	//Revisar colisiones con bordes de la ventana
	checkCollisions(mHost->cpPlayer);
	checkCollisions(mPlayer);
}

void CClient::render()
{
	mWindow.clear();
	mWindow.draw(mHost->cpPlayer->S);
	mWindow.draw(mPlayer->S);
	mWindow.display();
}

void CClient::checkCollisions(CPlayer * Player)
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
}
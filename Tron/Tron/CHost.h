#pragma once
#include "CGame.h"

class CHost : public CGame
{
public:
	CHost();
	~CHost();

	//Ejecutar juego
	void run();
	//Procesar teclas presionadas por el jugador
	void processEvents();
	//Actualizar logica del juego, posiciones y enviar paquetes
	void update(Time dTime);
	//Dibujar a la ventana
	void render();

	//Objeto tipo ventana
	RenderWindow mWindow;
	Time TimePerFrame;
	//Arreglo para almacenar colisiones
	bool field[800][600] = { 0 };

	//Estructuras para clientes remotos
	ClientStruct * Remote1;
	ClientStruct * Remote2;
	ClientStruct * Remote3;

	// Puntero a jugador host
	CPlayer * mPlayer;

	// Listener
	sf::TcpListener HostListener;

	//Revision de colisiones en arreglo y bordes de pantalla
	void checkCollisions(CPlayer * Player);

	bool runGame;
};
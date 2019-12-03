#include "CClient.h"
#include "CHost.h"

int main()
{
	short selection;
	std::cout << "Bienvenido al juego de Tron en SFML.\nPorfavor seleccione una opcion:\n\t1 - Host\n\t2 - Cliente\n";
	std::cin >> selection;
	std::cin.ignore();
	std::cin.clear();
	CGame * TronGame = nullptr;
	switch (selection)
	{
	case 1:		// Host
		TronGame = new CHost();
		TronGame->run();
		delete TronGame;
		break;
	case 2:		// Client
		TronGame = new CClient();
		TronGame->run();
		delete TronGame;
		break;
	default:	// Unknown input
		break;
	}
	return 0;
}
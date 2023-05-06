#include"SDL.h"
#include "SDL_ttf.h"
#include "src/utils/checkML.h"
#include <fstream>
#include "src/Game.h"
//#include <cstdint>
using namespace std;

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);// decetor de basura
	try
	{
		Game* game = new Game();
		game->run();
		SDL_Delay(1); // delay al acabar
		delete(game);
	}
	catch(string e)
	{
		cout << e << endl;
	}
	return 0;
}
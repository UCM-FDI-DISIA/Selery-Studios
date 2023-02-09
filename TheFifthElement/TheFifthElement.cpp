#include"SDL.h"
#include "tmxlite/detail/Android.hpp"
#include "SDL_ttf.h"
#include "utils/checkML.h"
#include <fstream>
#include "states/GameStateMachine.h"
#include "GameManager.h"
//#include <cstdint>
using namespace std;

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);// decetor de basura
	try
	{

		//COMO LO TENIA SOFI
		///GameManager* game=static_cast<GameManager*>(GameManeger::instance()) pero con esto no se
		//llama a la constructora de GameManager pero si al resto
		//game->run
		//GameStateMachine::init();
		GameManager* game = new GameManager();
		game->run();
		SDL_Delay(500); // delay al acabar
		delete(game);
		
	}
	catch(string e)
	{
		//cout << e << endl;
	}
	return 0;
}
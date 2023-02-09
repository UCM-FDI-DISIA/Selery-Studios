#include"SDL.h"
#include "tmxlite/detail/Android.hpp"
#include "SDL_ttf.h"
#include "utils/checkML.h"
#include <fstream>
#include "GameStateMachine.h"
#include "GameManager.h"
//#include <cstdint>
using namespace std;

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);// decetor de basura
	try
	{
		GameStateMachine::init();
		GameManager* game = static_cast<GameManager*>(GameManager::instance());
		game->run();
		SDL_Delay(500); // delay al acabar
		delete(game);// destruye game
	}
	catch(string e)
	{
		//cout << e << endl;
	}
	return 0;
}
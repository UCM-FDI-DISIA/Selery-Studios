#include "MainMenuState.h"
#include "../Game.h"
MainMenuState::MainMenuState()
{
	playButton = new Entity();
	playButtonWidth = 300;
	playButtonHeight = 100;
	
	/*void(*CallBack)(GameManager * gameManager)  = (*functionCallback)(GameManager* game)*/

	playButtonPos = Vector2D((WIN_WIDTH / 2) - playButtonWidth/2, (WIN_HEIGHT / 2));
	playButton->addComponent<Transform>(TRANSFORM_H,playButtonPos,playButtonWidth,playButtonHeight,1,0,1,false);
	playButton->addComponent<Button>(BUTTON_H,"PLAY");
    addEntity(playButton);
	SDLUtils::instance()->soundEffects().at("Menu").play();
}

void MainMenuState::update()
{
	Manager::update();
}
void MainMenuState::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		playButton->handleEvent(event);
	}

}
void MainMenuState::render(){
	Manager::render();
}

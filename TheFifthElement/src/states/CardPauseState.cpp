#include "CardPauseState.h"
#include "../Game.h"

void CardPauseState::createButtons()
{
	menuButton = new Entity();
	menuButton->addComponent<Transform>(TRANSFORM_H, Vector2D(WIN_WIDTH / 2, WIN_HEIGHT - 400), 289, 86);
	menuButton->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("MenuButton"));
	menuButton->addComponent<Button>(BUTTON_H, "MAINMENU");
	addEntity(menuButton);

	returnButton = new Entity();
	returnButton->addComponent<Transform>(TRANSFORM_H, Vector2D(WIN_WIDTH /2, WIN_HEIGHT-200), 289, 86);
	returnButton->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("ReturnButton"));
	returnButton->addComponent<Button>(BUTTON_H, "RETURN");
	addEntity(returnButton);
}

void CardPauseState::render()
{	
	controlsTex->render({ 0,0,WIN_WIDTH,WIN_HEIGHT });
	Manager::render();
}

void CardPauseState::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		menuButton->handleEvent(event);
		returnButton->handleEvent(event);
	}
}
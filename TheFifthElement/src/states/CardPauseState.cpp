#include "CardPauseState.h"
#include "../Game.h"

CardPauseState::CardPauseState(CardGameState* cardState_): cardState(cardState_)
{
	createButtons();
}

void CardPauseState::createButtons()
{
	menuButton = new Entity();
	menuButton->addComponent<Transform>(TRANSFORM_H, Vector2D(WIN_WIDTH / 2, WIN_HEIGHT - 380), 289, 86);
	menuButton->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("cardMenuButton"));
	menuButton->addComponent<Button>(BUTTON_H, "CARDMENU");
	addEntity(menuButton);

	returnButton = new Entity();
	returnButton->setContext(this);
	returnButton->addComponent<Transform>(TRANSFORM_H, Vector2D(WIN_WIDTH /2, WIN_HEIGHT-220), 289, 86);
	returnButton->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("cardReturnButton"));
	returnButton->addComponent<Button>(BUTTON_H, "CARDRETURN");
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
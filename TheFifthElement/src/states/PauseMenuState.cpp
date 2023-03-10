#include "PauseMenuState.h"

PauseMenuState::PauseMenuState()
{

	mainMenuButton_ = new Entity();
	mainMenuButtonWidth_ = 300;
	mainMenuButtonHeight_ = 100;

	mainMenuButtonPos_ = Vector2D(100, 200);
	mainMenuButton_->addComponent<Transform>(TRANSFORM_H, mainMenuButtonPos_, mainMenuButtonWidth_, mainMenuButtonHeight_, 1, 0, 1, false);
	mainMenuButton_->addComponent<Button>(BUTTON_H, "MAINMENU");

	addEntity(mainMenuButton_);

	resumeButton_ = new Entity();
	resumeButtonWidth_ = 300;
	resumeButtonHeight_ = 100;

	resumeButtonPos_ = Vector2D(Manager::camRect_.x + WIN_WIDTH/2, Manager::camRect_.y + WIN_HEIGHT/2);
	resumeButton_->addComponent<Transform>(TRANSFORM_H, resumeButtonPos_, resumeButtonWidth_, resumeButtonHeight_, 1, 0, 1, false);
	resumeButton_->addComponent<Button>(BUTTON_H, "RESUME");

	addEntity(resumeButton_);
}

void PauseMenuState::update()
{
	Manager::update();
}
void PauseMenuState::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		resumeButton_->handleEvent(event);
		mainMenuButton_->handleEvent(event);

	}

}
void PauseMenuState::render() {
	Manager::render();
}
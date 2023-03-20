#include "PauseMenuState.h"

PauseMenuState::PauseMenuState() {
	Background("fondoPausa");

	// Buttons
	//createButtons();

	resumeButton_ = new Entity();
	resumeButtonWidth_ = 300;
	resumeButtonHeight_ = 100;

	resumeButtonPos_ = Vector2D(Manager::camRect_.x + WIN_WIDTH/2 - buttonOffset_.getX(), Manager::camRect_.y + WIN_HEIGHT / 2 - buttonOffset_.getY());
	resumeButton_->addComponent<Transform>(TRANSFORM_H, resumeButtonPos_, resumeButtonWidth_, resumeButtonHeight_, 1, 0, 1, false);
	resumeButton->addComponent<Image>(int(IMAGE_H), &SDLUtils::instance()->images().at("ResumeButton"), 1, 1, 0, 289, 86);
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
		/*resumeButton->handleEvent(event);
		menuButton->handleEvent(event);
		optionsButton->handleEvent(event);*/
	}

}
void PauseMenuState::render() {
	Manager::render();
}

Entity* PauseMenuState::addNewEntity(string t, float w, float h, Vector2D pos, int nframes, bool flip, float size) {
	Entity* e = new Entity();

	e->addComponent<Transform>(TRANSFORM_H, pos, w / nframes, h, size);
	Texture* t_ = &SDLUtils::instance()->images().at(t);
	im_ = e->addComponent<Image>(IMAGE_H, t_, nframes, nframes, 0, w / nframes, h);
	if (flip) im_->setFlip(SDL_FLIP_HORIZONTAL);
	addEntity(e);
	return e;
}

void PauseMenuState::Background(string file) {
	Entity* e = new Entity();

	int f = 0;
	bool matrix = false;
	Vector2D v = { 0,0 };
	int r = 0;
	e->addComponent<Transform>(int(TRANSFORM_H), v, WIN_WIDTH, WIN_HEIGHT, r, 0, f, matrix);
	Texture* t = &SDLUtils::instance()->images().at(file);
	e->addComponent<Image>(int(IMAGE_H), t, f, f, f, BACKGROUNDAIR_WIDTH_FRAME, BACKGROUNDAIR_HEIGHT_FRAME);
	addEntity(e);
}

void PauseMenuState::createButtons() {
	resumeButton = addNewEntity("ResumeButton", 289, 86, Vector2D(5 * WIN_WIDTH / 90, 28 * WIN_HEIGHT / 60), 1, false);
	resumeButton->addComponent<Button>(BUTTON_H, "RESUME");

	menuButton = addNewEntity("MenuButton", 289, 86, Vector2D(5 * WIN_WIDTH / 90, 40 * WIN_HEIGHT / 60), 1, false);
	menuButton->addComponent<Button>(BUTTON_H, "MAINMENU");

	optionsButton = addNewEntity("OptionsButton", 95, 97, Vector2D(8 * WIN_WIDTH / 9, 2 * WIN_HEIGHT / 60), 1, false);
	optionsButton->addComponent<Button>(BUTTON_H, "OPTIONS");
}
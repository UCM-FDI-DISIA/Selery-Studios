#include "PauseState.h"
#include "../Game.h"

PauseState::PauseState()
{
	float scaleX = WIN_WIDTH / 900;
	float scaleY = WIN_HEIGHT / 600;
	Background("fondoPausa");

	addNewEntity("tree", 1024, 192, Vector2D(36.5 * WIN_WIDTH / 90, -200 * scaleY), 8, false, 1.8);
	addNewEntity("tree", 1024, 192, Vector2D(15 * WIN_WIDTH / 90, -175 * scaleY), 8, false, 1.8);
	addNewEntity("campfire2", 1024, 128, Vector2D(15 * WIN_WIDTH / 90, 17 * WIN_HEIGHT / 60), 8, false, 1.7);
	addNewEntity("treasure", 896, 64, Vector2D(11.3 * WIN_WIDTH / 90, 12 * WIN_HEIGHT / 60), 14, false, 1.7);
	addNewEntity("tree", 1024, 192, Vector2D(30 * WIN_WIDTH / 90, -72 * scaleY), 8, false, 1.8);
	addNewEntity("tree", 1024, 192, Vector2D(36.5 * WIN_WIDTH / 90, -2*scaleY), 8, false, 1.8);
	addNewEntity("treasureBlue", 704, 64, Vector2D(40.5 * WIN_WIDTH / 90, 23 * WIN_HEIGHT / 60), 11, false, 1.7);
	addNewEntity("tree", 1024, 192, Vector2D(-20 * scaleX, -96*scaleY), 8, false, 1.8);
	addNewEntity("tree", 1024, 192, Vector2D(550 * WIN_WIDTH / 900, -215 * scaleY), 8, false, 1.8);
	addNewEntity("tree", 1024, 192, Vector2D(650 * WIN_WIDTH / 900, -180 * scaleY), 8, false, 1.8);
	addNewEntity("shine", 896, 99, Vector2D(240 * WIN_WIDTH / 900, 450 * scaleY), 14, false, 1.8);

	addNewEntity("shine", 896, 99, Vector2D(660 * WIN_WIDTH / 900, 30 * scaleY), 14, false, 1.8);

	addNewEntity("NPC_2", NPC_WIDTH * 7, NPC_HEIGHT, Vector2D(60 * WIN_WIDTH / 90, 20 * WIN_HEIGHT / 600), 7, true);
	addNewEntity("NPC_1", NPC_WIDTH * 7, NPC_HEIGHT, Vector2D(75 * WIN_WIDTH / 90, 80 * WIN_HEIGHT / 600), 7, false);

	// Buttons
	createButtons();

}

void PauseState::update() {
	Manager::update();
}
void PauseState::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		resumeButton->handleEvent(event);
		menuButton->handleEvent(event);
		optionsButton->handleEvent(event);
	}

}
void PauseState::render() {
	Manager::render();
}

Entity* PauseState::addNewEntity(string t, float w, float h, Vector2D pos, int nframes, bool flip, float size) {
	Entity* e = new Entity();
	if (size != WIN_WIDTH / 900) size *= WIN_WIDTH / 900;
	e->addComponent<Transform>(TRANSFORM_H, pos, w / nframes, h, size);
	Texture* t_ = &SDLUtils::instance()->images().at(t);
	im_ = e->addComponent<Image>(IMAGE_H, t_, nframes, nframes, 0, w / nframes, h);
	if (flip) im_->setFlip(SDL_FLIP_HORIZONTAL);
	addEntity(e);
	return e;
}

void PauseState::Background(string file) {
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

void PauseState::createButtons() {
	resumeButton = addNewEntity("ResumeButton", 289, 86, Vector2D(WIN_WIDTH / 3, 16 * WIN_HEIGHT / 60), 1, false, 1.3);
	resumeButton->addComponent<Button>(BUTTON_H, "RESUME");

	menuButton = addNewEntity("MenuButton", 289, 86, Vector2D(WIN_WIDTH / 3, 33 * WIN_HEIGHT / 60), 1, false, 1.3);
	menuButton->addComponent<Button>(BUTTON_H, "MAINMENU");

	optionsButton = addNewEntity("OptionsButton", 95, 97, Vector2D(8 * WIN_WIDTH / 9, 2 * WIN_HEIGHT / 60), 1, false);
	optionsButton->addComponent<Button>(BUTTON_H, "OPTIONS");
}


#include "PauseState.h"
#include "../Game.h"

PauseState::PauseState()
{
	float scaleX = WIN_WIDTH / 900;
	float scaleY = WIN_HEIGHT / 600;
	float y;
	Background("fondoPausa");

	createCharacter("tree", 128, 192, Vector2D(36.5 * WIN_WIDTH / 90, 200*WIN_HEIGHT/600), 8, false, 1.8);
	createCharacter("tree", 128, 192, Vector2D(15 * WIN_WIDTH / 90, 175 * WIN_HEIGHT / 600), 8, false, 1.8);
	createCharacter("campfire2", 128, 128, Vector2D(15 * WIN_WIDTH / 90, 17 * WIN_HEIGHT / 60), 8, false, 1.7);
	createCharacter("treasure", 64, 64, Vector2D(11.3 * WIN_WIDTH / 90, 12 * WIN_HEIGHT / 60), 14, false,1.7);
	createCharacter("tree", 128, 192, Vector2D(26 * WIN_WIDTH / 90, 10 * WIN_HEIGHT / 600), 8, false, 1.8);
	createCharacter("tree", 128, 192, Vector2D(36.5 * WIN_WIDTH / 90, 12 * WIN_HEIGHT / 600), 8, false, 1.8);
	createCharacter("treasureBlue", 64, 64, Vector2D(40.5 * WIN_WIDTH / 90, 23 * WIN_HEIGHT / 60), 11, false, 1.7);
	createCharacter("tree", 128, 192, Vector2D(-20 * scaleX, 96* WIN_HEIGHT / 600), 8, false, 1.8);
	createCharacter("tree",128, 192, Vector2D(550 * WIN_WIDTH / 900, 215 * WIN_HEIGHT / 600), 8, false, 1.8);
	createCharacter("tree", 128, 192, Vector2D(650 * WIN_WIDTH / 900, 180 * WIN_HEIGHT / 600), 8, false, 1.8);
	createCharacter("shine", 64, 99, Vector2D(242 * WIN_WIDTH / 900, 450*WIN_HEIGHT/600), 14, false, 1.8);

	createCharacter("shine", 64, 99, Vector2D(660 * WIN_WIDTH / 900, 30 * WIN_HEIGHT / 600), 14, false, 1.8);

	createCharacter("NPC_2", PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME, Vector2D(WIN_WIDTH / 5, 350), 7, true, 1);
	createCharacter("NPC_1", PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME, Vector2D(WIN_WIDTH*4 /5, 100), 7, false, 1);

	// Buttons
	createButtons();

	camRect_.x = 0;
	camRect_.y = 0;

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

Entity* PauseState::addNewEntity(string t, float w, float h, Vector2D pos, int nframes, bool flip, float size, bool neg) {
	Entity* e = new Entity();

	if(!neg)e->addComponent<Transform>(TRANSFORM_H, pos, w / nframes, h, size);
	else e->addComponent<Transform>(TRANSFORM_H, Vector2D(pos.getX(), -pos.getY()), w / nframes, h, size);
	Texture* t_ = &SDLUtils::instance()->images().at(t);
	im_ = e->addComponent<Image>(IMAGE_H, t_);
	if (flip) im_->setFlip(SDL_FLIP_HORIZONTAL);
	addEntity(e);
	return e;
}

Entity* PauseState::createCharacter(string t, float w, float h, Vector2D pos, int nframes, bool flip, float size) {
	Entity* e = new Entity();
	float size_ = size * WIN_WIDTH / 900;
	e->addComponent<Transform>(TRANSFORM_H, pos, w, h, size_);
	e->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at(t), w, h, nframes);
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
	e->addComponent<Image>(IMAGE_H, t);
	addEntity(e);
}

void PauseState::createButtons() {
	resumeButton = addNewEntity("ResumeButton", 289, 86, Vector2D(290*WIN_WIDTH / 900, 16 * WIN_HEIGHT / 60), 1, false, 1.3);
	resumeButton->addComponent<Button>(BUTTON_H, "RESUME");

	menuButton = addNewEntity("MenuButton", 289, 86, Vector2D(290*WIN_WIDTH / 900, 33 * WIN_HEIGHT / 60), 1, false, 1.3);
	menuButton->addComponent<Button>(BUTTON_H, "MAINMENU");

	optionsButton = addNewEntity("OptionsButton", 95, 97, Vector2D(84 * WIN_WIDTH / 90, WIN_HEIGHT / 60), 1, false, 0.5);
	optionsButton->addComponent<Button>(BUTTON_H, "OPTIONS");
}


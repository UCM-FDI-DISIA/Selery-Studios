#include "MainMenuState.h"
#include "../Game.h"
MainMenuState::MainMenuState()
{

	Background("fondoMainMenu3");


	addNewEntity("campfire", 1024, 128, Vector2D(4 * WIN_WIDTH / 9, 3 * WIN_HEIGHT / 4), 8, false);

	addNewEntity("NPC_1", NPC_WIDTH * 7, NPC_HEIGHT, Vector2D(48 * WIN_WIDTH / 90, 3 * WIN_HEIGHT / 4), 7, false);

	addNewEntity("NPC_2", NPC_WIDTH * 7, NPC_HEIGHT, Vector2D(38 * WIN_WIDTH / 90, 2 * WIN_HEIGHT / 3), 7, true);

	addNewEntity("hole", 3840, 160, Vector2D(5 * WIN_WIDTH / 9, 11 * WIN_HEIGHT / 20), 30, false);

	addNewEntity("treasure", 896, 64, Vector2D(63 * WIN_WIDTH / 90, 30 * WIN_HEIGHT / 60), 14, false);

	addNewEntity("PTD_fire_idle", PLAYERTD_WIDTH_FRAME * 7, PLAYERTD_HEIGHT_FRAME, Vector2D(2 * WIN_WIDTH / 3, 17 * WIN_HEIGHT / 60), 7, false);
	addNewEntity("PTD_water_idle", PLAYERTD_WIDTH_FRAME * 7, PLAYERTD_HEIGHT_FRAME, Vector2D(55 * WIN_WIDTH / 60, WIN_HEIGHT / 3), 7, true);
	addNewEntity("PTD_earth_up", PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME, Vector2D(73 * WIN_WIDTH / 90, 25 * WIN_HEIGHT / 60), 1, false);
	addNewEntity("PTD_air_idle", PLAYERTD_WIDTH_FRAME * 7, PLAYERTD_HEIGHT_FRAME, Vector2D(65 * WIN_WIDTH / 90, 45 * WIN_HEIGHT / 60), 7, false);


	// Buttons
	createButtons();

	//SDLUtils::instance()->soundEffects().at("Menu").play();

}

void MainMenuState::update() {
	Manager::update();
	cout << slider->getComponent<sliderComponent>(SLIDERCOMPONENT_H)->getValue() << endl;
}
void MainMenuState::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		playButton->handleEvent(event);
		exitButton->handleEvent(event);
		optionsButton->handleEvent(event);
		slider->handleEvent(event);
	}

}
void MainMenuState::render() {
	Manager::render();
}

Entity* MainMenuState::addNewEntity(string t, float w, float h, Vector2D pos, int nframes, bool flip, float size) {
	Entity* e = new Entity();

	e->addComponent<Transform>(TRANSFORM_H, pos, w/nframes, h, size);
	Texture* t_ = &SDLUtils::instance()->images().at(t);
	im_ = e->addComponent<Image>(IMAGE_H, t_, nframes, nframes, 0, w/nframes, h);
	if (flip) im_->setFlip(SDL_FLIP_HORIZONTAL);
	addEntity(e);
	return e;
}

void MainMenuState::Background(string file) {
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

void MainMenuState::createButtons() {
	playButton = addNewEntity("PlayButton", 289, 86, Vector2D(5 * WIN_WIDTH / 90, 28 * WIN_HEIGHT / 60), 1, false);
	playButton->addComponent<Button>(BUTTON_H, "PLAY");

	exitButton = addNewEntity("ExitButton", 289, 86, Vector2D(5 * WIN_WIDTH / 90, 40 * WIN_HEIGHT / 60), 1, false);
	exitButton->addComponent<Button>(BUTTON_H, "EXIT");

	optionsButton = addNewEntity("OptionsButton", 95, 97, Vector2D(8 * WIN_WIDTH / 9, 2 * WIN_HEIGHT / 60), 1, false);
	optionsButton->addComponent<Button>(BUTTON_H, "OPTIONS");


	slider = addEntity(new Entity());
	slider->addComponent<Transform>(TRANSFORM_H, Vector2D(220,10), 20, 20, 1);
	slider->addComponent<brightSliderComponent>(BRIGHTSLIDER_H);
	slider->addComponent<sliderComponent>(SLIDERCOMPONENT_H);
}

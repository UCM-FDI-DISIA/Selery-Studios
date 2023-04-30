#include "MainMenuState.h"
#include "../Game.h"
MainMenuState::MainMenuState()
{
	

	Background("fondoMainMenu3");

	SDLUtils::instance()->soundEffects().at("Title").play(-1);
	addNewEntity("campfire", 128, 128, Vector2D(4 * WIN_WIDTH / 9, 3 * WIN_HEIGHT / 4), 8, 128, 128, false);

	addNewEntity("NPC_1", NPC_WIDTH, NPC_HEIGHT, Vector2D(48 * WIN_WIDTH / 90, 3 * WIN_HEIGHT / 4), 7, NPC_WIDTH, NPC_HEIGHT, false);

	addNewEntity("NPC_2", NPC_WIDTH, NPC_HEIGHT, Vector2D(38 * WIN_WIDTH / 90, 2 * WIN_HEIGHT / 3), 7, NPC_WIDTH, NPC_HEIGHT, true);

	addNewEntity("hole", 3840, 160, Vector2D(49 * WIN_WIDTH / 90, 10.5 * WIN_HEIGHT / 20), 30, 128, 160, false, 1.2);

	addNewEntity("treasure", 64, 64, Vector2D(63 * WIN_WIDTH / 90, 30 * WIN_HEIGHT / 60), 14, 64, 64, false);

	addNewEntity("PTD_fire_idle", PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME, Vector2D(2 * WIN_WIDTH / 3, 17 * WIN_HEIGHT / 60), 7, PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME, false);
	addNewEntity("PTD_water_idle", PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME, Vector2D(55 * WIN_WIDTH / 60, WIN_HEIGHT / 3), 7, PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME, true);
	addNewEntity("PTD_earth_up", PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME, Vector2D(73 * WIN_WIDTH / 90, 25 * WIN_HEIGHT / 60), 1, PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME, false);
	addNewEntity("PTD_air_idle", PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME, Vector2D(65 * WIN_WIDTH / 90, 45 * WIN_HEIGHT / 60), 7, PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME, false);


	// Buttons
	createButtons();

	

}

MainMenuState::~MainMenuState()
{
	Manager::~Manager();
}

void MainMenuState::update() {
	Manager::update();
}
void MainMenuState::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT )
		{
			GameManager::instance()->getGame()->setExit(true);
		}
		playButton->handleEvent(event);
		exitButton->handleEvent(event);
		optionsButton->handleEvent(event);
		
	}

}
void MainMenuState::render() {
	Manager::render();
}

Entity* MainMenuState::addNewEntity(string t, float w, float h, Vector2D pos, int nframes, int wFrame, int hFrame, bool flip, float size) {
	Entity* e = new Entity();

	e->addComponent<Transform>(TRANSFORM_H, pos, w, h, size);
	e->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at(t), wFrame, h, nframes);
	addEntity(e);
	return e;
}

void MainMenuState::Background(string file) {
	Entity* e = new Entity();
	//e->setContext(this);
	int f = 0;
	bool matrix = false;
	Vector2D v = { 0,0 };
	int r = 0;
	e->addComponent<Transform>(TRANSFORM_H, v, 900, 600, r, 0, f, matrix);
	Texture* t = &SDLUtils::instance()->images().at(file);
	e->addComponent<Image>(IMAGE_H, t);
	addEntity(e);
}

void MainMenuState::createButtons() {
	loadButton = new Entity();
	//playButton->setContext(this);
	loadButton->addComponent<Transform>(TRANSFORM_H, Vector2D(5 * WIN_WIDTH / 90, 28 * WIN_HEIGHT / 60-120), 289, 86);
	//playButton = addNewEntity("PlayButton", 289, 86, Vector2D(5 * WIN_WIDTH / 90, 28 * WIN_HEIGHT / 60), 1, false);
	loadButton->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("LoadButton"));
	loadButton->addComponent<Button>(BUTTON_H, "LOAD");
	//addEntity(playButton);
	addEntity(loadButton);

	playButton = new Entity();
	//playButton->setContext(this);
	playButton->addComponent<Transform>(TRANSFORM_H, Vector2D(5 * WIN_WIDTH / 90, 28 * WIN_HEIGHT / 60), 289, 86);
	//playButton = addNewEntity("PlayButton", 289, 86, Vector2D(5 * WIN_WIDTH / 90, 28 * WIN_HEIGHT / 60), 1, false);
	playButton->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("PlayButton"));
	playButton->addComponent<Button>(BUTTON_H, "PLAY");
	addEntity(playButton);

	exitButton = new Entity();
	//exitButton->setContext(this);
	exitButton->addComponent<Transform>(TRANSFORM_H, Vector2D(5 * WIN_WIDTH / 90, 40 * WIN_HEIGHT / 60), 289, 86);
	//exitButton = addNewEntity("ExitButton", 289, 86, Vector2D(5 * WIN_WIDTH / 90, 40 * WIN_HEIGHT / 60), 1, false);
	exitButton->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("ExitButton"));
	exitButton->addComponent<Button>(BUTTON_H, "EXIT");
	addEntity(exitButton);

	optionsButton = new Entity();
	//optionsButton->setContext(this);
	optionsButton->addComponent<Transform>(TRANSFORM_H, Vector2D(84 * WIN_WIDTH / 90, WIN_HEIGHT / 60), 95 / 2, 97 / 2);
	//optionsButton = addNewEntity("OptionsButton", 95, 97, Vector2D(84 * WIN_WIDTH / 90, WIN_HEIGHT / 60), 1, false, 0.5);
	optionsButton->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("OptionsButton"));
	optionsButton->addComponent<Button>(BUTTON_H, "OPTIONS");
	addEntity(optionsButton);

}

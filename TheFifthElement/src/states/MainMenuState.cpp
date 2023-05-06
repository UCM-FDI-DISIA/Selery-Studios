#include "MainMenuState.h"
#include "../Game.h"
MainMenuState::MainMenuState()
{
	
	if (SDL_NumJoysticks() < 1) {
		// No hay gamepads conectados
		controladorDetectado = false;
	}
	else {
		// Se detectA un gamepad
		controller = SDL_GameControllerOpen(0);
		controladorDetectado = true;
	}
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
		if (controladorDetectado) {
			if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)) {
				GameManager::instance()->leaveMainMenu();
			}
			else if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B)) {
				GameManager::instance()->getGame()->setExit(true);
			}
			else if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y)) {
				GameManager::instance()->goOptionsMenu();
			}
			else if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X)) {
				GameManager::instance()->LoadGame();
			}
		}
		playButton->handleEvent(event);
		exitButton->handleEvent(event);
		optionsButton->handleEvent(event);
		loadButton->handleEvent(event);
		
	}

}
void MainMenuState::render() {
	Manager::render();
	SDL_Rect dest1 = { 5 * WIN_WIDTH / 90, (25 * WIN_HEIGHT / 60) - 50 * WIN_HEIGHT / 600, 50 * WIN_WIDTH / 900, 50 * WIN_HEIGHT / 600 };
	SDLUtils::instance()->images().at("A").render(dest1);
	SDL_Rect dest2 = { 5 * WIN_WIDTH / 90, (45 * WIN_HEIGHT / 60) - 50 * WIN_HEIGHT / 600, 50 * WIN_WIDTH / 900, 50 * WIN_HEIGHT / 600 };
	SDLUtils::instance()->images().at("B").render(dest2);
	SDL_Rect dest3 = { 5 * WIN_WIDTH / 90, (45 * WIN_HEIGHT / 60) - 155 * WIN_HEIGHT / 600, 50 * WIN_WIDTH / 900, 50 * WIN_HEIGHT / 600 };
	SDLUtils::instance()->images().at("X").render(dest3);

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
	Vector2D pos = { 0,0 };
	e->addComponent<Transform>(TRANSFORM_H, pos, 900, 600, 1);
	Texture* t = &SDLUtils::instance()->images().at(file);
	e->addComponent<Image>(IMAGE_H, t);
	addEntity(e);
}

void MainMenuState::createButtons() {

	playButton = new Entity();
	playButton->addComponent<Transform>(TRANSFORM_H, Vector2D(5 * WIN_WIDTH / 90, 22 * WIN_HEIGHT / 60), 289, 86);
	playButton->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("PlayButton"));
	playButton->addComponent<Button>(BUTTON_H, "PLAY");
	addEntity(playButton);

	loadButton = new Entity();
	loadButton->addComponent<Transform>(TRANSFORM_H, Vector2D(5 * WIN_WIDTH / 90, 32 * WIN_HEIGHT / 60), 289, 86);
	loadButton->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("LoadButton"));
	loadButton->addComponent<Button>(BUTTON_H, "LOAD");
	addEntity(loadButton);

	exitButton = new Entity();
	exitButton->addComponent<Transform>(TRANSFORM_H, Vector2D(5 * WIN_WIDTH / 90, 42 * WIN_HEIGHT / 60), 289, 86);
	exitButton->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("ExitButton"));
	exitButton->addComponent<Button>(BUTTON_H, "EXIT");
	addEntity(exitButton);

	optionsButton = new Entity();
	optionsButton->addComponent<Transform>(TRANSFORM_H, Vector2D(84 * WIN_WIDTH / 90, WIN_HEIGHT / 60), 95 / 2, 97 / 2);
	optionsButton->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("OptionsButton"));
	optionsButton->addComponent<Button>(BUTTON_H, "OPTIONS");
	addEntity(optionsButton);

}

#include "MainMenuState.h"
#include "../Game.h"
MainMenuState::MainMenuState()
{
	
	addEntity(new Background("fondoMainMenu2"));
	
	addEntity(new NewEntity("campfire", 1024, 128, Vector2D(4*WIN_WIDTH/9, 3*WIN_HEIGHT/4), 8, false));

	addEntity(new NewEntity("NPC_1", NPC_WIDTH*7, NPC_HEIGHT, Vector2D(48*WIN_WIDTH / 90, 3 * WIN_HEIGHT / 4), 7, false));

	addEntity(new NewEntity("NPC_2", NPC_WIDTH*7, NPC_HEIGHT, Vector2D(38 * WIN_WIDTH / 90, 2 * WIN_HEIGHT / 3), 7, true));

	addEntity(new NewEntity("hole", 3840, 160, Vector2D(5 * WIN_WIDTH / 9, 11 * WIN_HEIGHT / 20), 30, false));

	addEntity(new NewEntity("treasure", 896, 64, Vector2D(63 * WIN_WIDTH / 90, 30 * WIN_HEIGHT / 60), 14, false));

	addEntity(new NewEntity("PTD_fire_idle", PLAYERTD_WIDTH_FRAME*7,PLAYERTD_HEIGHT_FRAME, Vector2D(2 * WIN_WIDTH / 3, 17*WIN_HEIGHT /60), 7, false));
	addEntity(new NewEntity("PTD_water_idle", PLAYERTD_WIDTH_FRAME * 7, PLAYERTD_HEIGHT_FRAME, Vector2D(55 * WIN_WIDTH / 60, WIN_HEIGHT / 3), 7, true));
	addEntity(new NewEntity("PTD_earth_up", PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME, Vector2D(73 * WIN_WIDTH / 90, 25*WIN_HEIGHT / 60), 1, false));
	addEntity(new NewEntity("PTD_air_idle", PLAYERTD_WIDTH_FRAME * 7, PLAYERTD_HEIGHT_FRAME, Vector2D(65 * WIN_WIDTH / 90, 45 * WIN_HEIGHT / 60), 7, false));


	// Buttons
	playButton = addEntity(new NewEntity("PlayButton", 288, 81, Vector2D(5 * WIN_WIDTH / 90, 28 * WIN_HEIGHT / 60), 1, false));
	playButton->addComponent<Button>(BUTTON_H,"PLAY");

	exitButton = addEntity(new NewEntity("ExitButton", 288, 81, Vector2D(5 * WIN_WIDTH / 90, 40 * WIN_HEIGHT / 60), 1, false));
	exitButton->addComponent<Button>(BUTTON_H, "EXIT");

	optionsButton = addEntity(new NewEntity("OptionsButton", 95, 97, Vector2D(8 * WIN_WIDTH / 9, 2 * WIN_HEIGHT / 60), 1, false));
	optionsButton->addComponent<Button>(BUTTON_H, "OPTIONS");


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
		exitButton->handleEvent(event);
		optionsButton->handleEvent(event);
	}

}
void MainMenuState::render(){
	Manager::render();
}

/*void MainMenuState::addNewEntity(string t, float w, float h, Vector2D pos, int nframes, bool flip, float size) {
	Entity* e = new Entity();

	e->addComponent<Transform>(TRANSFORM_H, pos, w/nframes, h, size);
	Texture* t_ = &SDLUtils::instance()->images().at(t);
	im_ = e->addComponent<Image>(IMAGE_H, t_, nframes, nframes, 0, w/nframes, h);
	if (flip) im_->setFlip(SDL_FLIP_HORIZONTAL);
}*/

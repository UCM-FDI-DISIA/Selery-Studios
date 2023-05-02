#include "OptionsState.h"
#include "../Game.h"
OptionsState::OptionsState() {
	if (SDL_NumJoysticks() < 1) {
		// No hay gamepads conectados
		controladorDetectado = false;
	}
	else {
		// Se detectA un gamepad
		controller = SDL_GameControllerOpen(0);
		controladorDetectado = true;
	}
	Background("fondoPausa");
	ControlsBackground("controlPanel");
	createCharacter("PTD_water_right", PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME, Vector2D(WIN_WIDTH / 5, 350), 7, false, 1);
	createButtons();
}

OptionsState::~OptionsState()
{
}

void OptionsState::Background(string file) {
	Entity* e = new Entity();
	Vector2D pos = { 0,0 };
	e->addComponent<Transform>(TRANSFORM_H, pos, 900, 600, 1);
	Texture* t = &SDLUtils::instance()->images().at(file);
	e->addComponent<Image>(IMAGE_H, t);
	addEntity(e);
}
void OptionsState::ControlsBackground(string file)
{
	Entity* e = new Entity();
	float w = 444;
	float h = 719;
	int f = 0;
	bool matrix = false;
	Vector2D pos = { (WIN_WIDTH / 2) - (w * 0.75f * WIN_WIDTH / 900) / 2, (WIN_HEIGHT / 2) - (h / 2.5f * WIN_HEIGHT / 600) };
	int r = 0;
	e->addComponent<Transform>(TRANSFORM_H, pos, w, h, 0.75);
	e->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at(file));
	addEntity(e);
}

void OptionsState::render() {
	Manager::render();
}
void OptionsState::update() {
	Manager::update();
}
void OptionsState::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT )
		{
			GameManager::instance()->getGame()->setExit(true);

		}
		if (controladorDetectado) {
			if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B)) {
				GameManager::instance()->backToMainMenu();
			}
			//else if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)) {
			//	GameManager::instance()->backToMainMenu();
			//}
		}
		backButton->handleEvent(event);
		TDcontrolsButton->handleEvent(event);
		BEUcontrolsButton->handleEvent(event);
		sliderBrillo->handleEvent(event);
		sliderSonido->handleEvent(event);
		muteButton->handleEvent(event);
		//resumeButton->handleEvent(event);
		if (exitActive)
		{
			exitControlsButton->handleEvent(event);
		}
	}

}

Entity* OptionsState::createCharacter(string t, float w, float h, Vector2D pos, int nframes, bool flip, float size) {
	Entity* e = new Entity();
	float size_ = size * WIN_WIDTH / 900;
	e->addComponent<Transform>(TRANSFORM_H, pos, w, h, size_);
	e->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at(t), w, h, nframes);
	addEntity(e);
	return e;
}

Entity* OptionsState::addNewEntity(string t, float w, float h, Vector2D pos, int nframes, bool flip, float size) {
	Entity* e = new Entity();
	float size_ = size;
	e->addComponent<Transform>(TRANSFORM_H, pos, w / nframes, h, size_);
	im_ = e->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at(t));
	if (flip) im_->setFlip(SDL_FLIP_HORIZONTAL);
	addEntity(e);
	return e;
}

void OptionsState::createButtons() {

	backButton = addNewEntity("ReturnButton", 194, 45, Vector2D(WIN_WIDTH - (200 * WIN_WIDTH / 900), WIN_HEIGHT - (50 * WIN_HEIGHT / 600)), 1, false, 1);
	backButton->addComponent<Button>(BUTTON_H, "RETURN");

	muteButton = addNewEntity("MuteButton", 20, 20, Vector2D(WIN_WIDTH / 2.5 - (10 * WIN_WIDTH / 900), WIN_HEIGHT / 3.1f - (40 * WIN_HEIGHT / 600)), 1, false, 1);
	muteButton->addComponent<Button>(BUTTON_H, "MUTE");

	TDcontrolsButton = addNewEntity("TDControlsButton", 194, 45, Vector2D(WIN_WIDTH / 2 - (194 * WIN_WIDTH / 900) / 2, WIN_HEIGHT / 1.75), 1, false, 1);
	TDcontrolsButton->addComponent<Button>(BUTTON_H, "TDCONTROLS");

	BEUcontrolsButton = addNewEntity("BEUControlsButton", 194, 45, Vector2D(WIN_WIDTH / 2 - (194 * WIN_WIDTH / 900) / 2, WIN_HEIGHT / 1.5), 1, false, 1);
	BEUcontrolsButton->addComponent<Button>(BUTTON_H, "BEUCONTROLS");

	sliderBrillo = addEntity(new Entity());
	sliderBrillo->addComponent<Transform>(TRANSFORM_H, Vector2D(WIN_WIDTH / 2-10, WIN_HEIGHT / 2-45 * WIN_HEIGHT / 600), 20, 20, 1);
	sliderBrillo->addComponent<brightSliderComponent>(BRIGHTSLIDER_H);
	sliderBrillo->addComponent<sliderComponent>(SLIDERCOMPONENT_H);

	sliderSonido = addEntity(new Entity());
	sliderSonido->addComponent<Transform>(TRANSFORM_H, Vector2D(WIN_WIDTH / 2-10, WIN_HEIGHT / 3.75f), 20, 20, 1);
	sliderSonido->addComponent<VolumeSlider>(VOLUMESLIDER_H); 
	sliderSonido->addComponent<sliderComponent>(SLIDERCOMPONENT_H);

}

void OptionsState::deleteButtonsTD()
{
	backButton->~Entity();
	muteButton->~Entity();
	BEUcontrolsButton->~Entity();
	sliderBrillo->~Entity();
	sliderSonido->~Entity();
}

void OptionsState::deleteButtonsBEU()
{
	backButton->~Entity();
	muteButton->~Entity();
	TDcontrolsButton->~Entity();
	sliderBrillo->~Entity();
	sliderSonido->~Entity();
}

void OptionsState::exitControls()
{
	exitActive = true;
	exitControlsButton = addNewEntity("ReturnButton", 194, 45, Vector2D(10, 10), 1, false, 0.75);
	exitControlsButton->addComponent<Button>(BUTTON_H, "EXITCONTROLS");
}
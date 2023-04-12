#include "OptionsState.h"

OptionsState::OptionsState() {
	Background("fondoPausa");
	ControlsBackground("controlPanel");
	createCharacter("PTD_water_right", PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME, Vector2D(WIN_WIDTH / 5, 350), 7, false, 1);
	createButtons();
}

void OptionsState::Background(string file) {
	Entity* e = new Entity();

	int f = 0;
	bool matrix = false;
	Vector2D v = { 0,0 };
	int r = 0;
	e->addComponent<Transform>(TRANSFORM_H, v, WIN_WIDTH, WIN_HEIGHT, r, 0, f, matrix);
	Texture* t = &SDLUtils::instance()->images().at(file);
	e->addComponent<Image>(IMAGE_H, t);
	addEntity(e);
}
void OptionsState::ControlsBackground(string file)
{
	Entity* e = new Entity();

	int f = 0;
	bool matrix = false;
	Vector2D v = { WIN_WIDTH / 2-135, WIN_HEIGHT / 2-250 };
	int r = 0;
	e->addComponent<Transform>(TRANSFORM_H, v, 270, 500, r, 0, f, matrix);
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
		backButton->handleEvent(event);
		TDcontrolsButton->handleEvent(event);
		BEUcontrolsButton->handleEvent(event);
		sliderBrillo->handleEvent(event);
		sliderSonido->handleEvent(event);
		muteButton->handleEvent(event);
		resumeButton->handleEvent(event);
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
	float size_ = size * WIN_WIDTH / 900;
	e->addComponent<Transform>(TRANSFORM_H, pos, w / nframes, h, size_);
	im_ = e->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at(t));
	if (flip) im_->setFlip(SDL_FLIP_HORIZONTAL);
	addEntity(e);
	return e;
}

void OptionsState::createButtons() {

	backButton = addNewEntity("BackButton", 289, 86, Vector2D(WIN_WIDTH-150, WIN_HEIGHT -50), 1, false, 0.5);
	backButton->addComponent<Button>(BUTTON_H, "BACK");

	resumeButton = addNewEntity("ResumeButton", 289, 86, Vector2D(5, WIN_HEIGHT - 50), 1, false, 0.5);
	resumeButton->addComponent<Button>(BUTTON_H, "RESUME");

	muteButton = addNewEntity("MuteButton", 20, 20, Vector2D(WIN_WIDTH / 2+42, WIN_HEIGHT / 5-40), 1, false, 1);
	muteButton->addComponent<Button>(BUTTON_H, "MUTE");

	TDcontrolsButton = addNewEntity("TDControlsButton", 289, 86, Vector2D(WIN_WIDTH/2-72, WIN_HEIGHT/2+90), 1, false, 0.5);
	TDcontrolsButton->addComponent<Button>(BUTTON_H, "TDCONTROLS");

	BEUcontrolsButton = addNewEntity("BEUControlsButton", 289, 86, Vector2D(WIN_WIDTH / 2-72, WIN_HEIGHT/1.5+60), 1, false, 0.5);
	BEUcontrolsButton->addComponent<Button>(BUTTON_H, "BEUCONTROLS");

	sliderBrillo = addEntity(new Entity());
	sliderBrillo->addComponent<Transform>(TRANSFORM_H, Vector2D(WIN_WIDTH / 2-10, WIN_HEIGHT / 2-45), 20, 20, 1);
	sliderBrillo->addComponent<brightSliderComponent>(BRIGHTSLIDER_H);
	sliderBrillo->addComponent<sliderComponent>(SLIDERCOMPONENT_H);

	sliderSonido = addEntity(new Entity());
	sliderSonido->addComponent<Transform>(TRANSFORM_H, Vector2D(WIN_WIDTH / 2-10, WIN_HEIGHT / 5), 20, 20, 1);
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
	exitControlsButton = addNewEntity("exitControlsButton", 50, 50, Vector2D(10, 10), 1, false, 0.5);
	exitControlsButton->addComponent<Button>(BUTTON_H, "EXITCONTROLS");
}
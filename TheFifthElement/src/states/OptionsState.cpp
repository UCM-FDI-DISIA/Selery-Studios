#include "OptionsState.h"

OptionsState::OptionsState() {
	Background("fondoPausa");
	addNewEntity("PTD_water_right", PLAYERTD_WIDTH_FRAME * 7, PLAYERTD_HEIGHT_FRAME, Vector2D(2 * WIN_WIDTH / 5, 450), 7, false, 1);

	createButtons();
}

void OptionsState::Background(string file) {
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
		//controlsButton->handleEvent(event);
		sliderBrillo->handleEvent(event);
		sliderSonido->handleEvent(event);
		muteButton->handleEvent(event);
	}

}

Entity* OptionsState::addNewEntity(string t, float w, float h, Vector2D pos, int nframes, bool flip, float size) {
	Entity* e = new Entity();

	float size_ = size * WIN_WIDTH / 900;
	e->addComponent<Transform>(TRANSFORM_H, pos, w / nframes, h, size_);
	Texture* t_ = &SDLUtils::instance()->images().at(t);
	im_ = e->addComponent<Image>(IMAGE_H, t_, nframes, nframes, 0, w / nframes, h);
	if (flip) im_->setFlip(SDL_FLIP_HORIZONTAL);
	addEntity(e);
	return e;
}

void OptionsState::createButtons() {

	backButton = addNewEntity("BackButton", 289, 86, Vector2D(WIN_WIDTH / 3, WIN_HEIGHT / 2), 1, false, 1);
	backButton->addComponent<Button>(BUTTON_H, "BACK");

	muteButton = addNewEntity("MuteButton", 289, 86, Vector2D(WIN_WIDTH / 6, WIN_HEIGHT / 5), 1, false, 0.5);
	muteButton->addComponent<Button>(BUTTON_H, "MUTE");

/*	backButton = addNewEntity("BackButton", 289, 86, Vector2D(5 * WIN_WIDTH / 90, 50 * WIN_HEIGHT / 60), 1, false, 0.5);
	backButton->addComponent<Button>(BUTTON_H, "BACK");*/ //Este sería el botón de controles.

	sliderBrillo = addEntity(new Entity());
	sliderBrillo->addComponent<Transform>(TRANSFORM_H, Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 5), 20, 20, 1);
	sliderBrillo->addComponent<brightSliderComponent>(BRIGHTSLIDER_H);
	sliderBrillo->addComponent<sliderComponent>(SLIDERCOMPONENT_H);

	sliderSonido = addEntity(new Entity());
	sliderSonido->addComponent<Transform>(TRANSFORM_H, Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 1.5), 20, 20, 1);
	sliderSonido->addComponent<VolumeSlider>(VOLUMESLIDER_H); 
	sliderSonido->addComponent<sliderComponent>(SLIDERCOMPONENT_H);

}
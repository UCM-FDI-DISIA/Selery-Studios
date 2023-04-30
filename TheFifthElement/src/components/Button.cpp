#include "Button.h"
#include "../states/TopDownState.h"

void Button::initComponent() {
	buttonTransform = ent_->getComponent<Transform>(TRANSFORM_H);
	im_ = ent_->getComponent<Image>(IMAGE_H);
	size_ = buttonTransform->getS();
}

void Button::update() {
	mouseRect = build_sdlrect(mousePos, mouseWidth, mouseHeight);
	if (Collision::collides(buttonTransform->getPos(), buttonTransform->getW()*size_, buttonTransform->getH()*size_, mousePos, mouseRect.w, mouseRect.h))
	{
		currentPositionState = MOUSE_OVER;
		if (identifier == "PLAY")im_->setTexture("PlayButtonPressed");
		else if (identifier == "EXIT")im_->setTexture("ExitButtonPressed");
		else if (identifier == "OPTIONS")im_->setTexture("OptionsButtonPressed");
		else if (identifier == "RESUME")im_->setTexture("ResumeButtonPressed");
		else if (identifier == "MAINMENU")im_->setTexture("MenuButtonPressed");
		else if (identifier == "BACK")im_->setTexture("MenuButtonPressed");
		else if (identifier == "TDCONTROLS")im_->setTexture("TDControlsButtonPressed");
		else if (identifier == "BEUCONTROLS")im_->setTexture("BEUControlsButtonPressed");
		else if (identifier == "MUTE")im_->setTexture("MuteButtonPressed");
		else if (identifier == "EXITCONTROLS")im_->setTexture("TDControlsButtonPressed");
		else if (identifier == "RETURN")im_->setTexture("ReturnButtonPressed");
		else if (identifier == "LOAD")im_->setTexture("LoadButtonPress");
	}
	else
	{
		if (identifier == "PLAY")im_->setTexture("PlayButton");
		else if (identifier == "EXIT")im_->setTexture("ExitButton");
		else if (identifier == "BACK")im_->setTexture("BackButton");
		else if (identifier == "OPTIONS")im_->setTexture("OptionsButton");
		else if (identifier == "RESUME")im_->setTexture("ResumeButton");
		else if (identifier == "MAINMENU")im_->setTexture("MenuButton");
		else if (identifier == "TDCONTROLS")im_->setTexture("TDControlsButton");
		else if (identifier == "BEUCONTROLS")im_->setTexture("BEUControlsButton");
		else if (identifier == "MUTE")im_->setTexture("MuteButton");
		else if (identifier == "EXITCONTROLS")im_->setTexture("TDControlsButton");
		else if (identifier == "RETURN")im_->setTexture("ReturnButton");
		else if (identifier == "LOAD")im_->setTexture("LoadButton");
		currentPositionState = MOUSE_OUT;
	}
	updateMousePosition();
}

void Button::updateMousePosition() {
	SDL_GetMouseState(&mousePosX, &mousePosY);
	mousePos = Vector2D(mousePosX + mngr_->camRect_.x, mousePosY + mngr_->camRect_.y);
}

void Button::handleEvent(SDL_Event event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			if (currentPositionState == 1)
			{
				if (identifier == "PLAY") {
					SDLUtils::instance()->soundEffects().at("Title").haltChannel();
					//SDLUtils::instance()->soundEffects().at("pruebaBoton").play();
					GameManager::instance()->leaveMainMenu();
				}
				else if (identifier == "LOAD"){
					SDLUtils::instance()->soundEffects().at("Title").haltChannel();
					//SDLUtils::instance()->soundEffects().at("pruebaBoton").play();
					GameManager::instance()->LoadGame();
				}
				else if (identifier == "RESUME") {
					SDLUtils::instance()->soundEffects().at("prueba").play();
					SDLUtils::instance()->soundEffects().at("Title").resumeChannel();
					GameManager::instance()->goTopDown();
					//GameManager::instance()->Pop();
				}
				else if (identifier == "OPTIONS") {
					SDLUtils::instance()->soundEffects().at("pruebaBoton").play();
					GameManager::instance()->goOptionsMenu();
				}
				else if (identifier == "MAINMENU") {
					SDLUtils::instance()->soundEffects().at("pruebaBoton").play();
					GameManager::instance()->backToMainMenu();
				}
				else if (identifier == "EXIT") {
					SDL_Quit();
				}
				else if (identifier == "UPTURN") {
					SDLUtils::instance()->soundEffects().at("pruebaBoton").play();
					isClicked_ = true;
					static_cast<TopDownState*>(mngr_)->getShopComp()->shopEconomy();
					isClicked_ = false;
				}
				else if (identifier == "EXITSHOP") {
					TopDownState* topdownstate = static_cast<TopDownState*>(mngr_);
					topdownstate->cleanShopButtons();
					topdownstate->getDialog()->setopenedShop();
					
				}
				else if (identifier == "RETURN") {
					GameManager::instance()->Pop();

				}
				else if (identifier == "BACK") {
					GameManager::instance()->backToMainMenu();
				}
				else if (identifier == "MUTE")
				{
					SDL_AudioQuit(); //Mutea el juego (TODO). //Lo podremos manejar a traves del sound manager
				}
				else if (identifier == "TDCONTROLS")
				{		
					tdcontrols = true;
					OptionsState* optionsstate = static_cast<OptionsState*>(mngr_);
					optionsstate->exitControls();					
					optionsstate->deleteButtonsTD();
				}
				else if (identifier == "BEUCONTROLS")
				{			
					beucontrols = true;
					OptionsState* optionsstate = static_cast<OptionsState*>(mngr_);
					optionsstate->exitControls();
					optionsstate->deleteButtonsBEU();
				}
				else if (identifier == "EXITCONTROLS")
				{
					tdcontrols = false;
					beucontrols = false;
					GameManager::instance()->goOptionsMenu();
				}
			}
		}
	}
}

void Button::render() {
	SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 250, 0, 0);
	SDL_RenderDrawRect(GameManager::instance()->getRenderer(), &mouseRect);
	SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 0, 0, 255);
	SDL_Rect dest = { 0,0,WIN_WIDTH,WIN_HEIGHT };
	if (tdcontrols)
	{
		SDLUtils::instance()->images().at("TopDownControls").render(dest);
	}
	if (beucontrols)
	{
		SDLUtils::instance()->images().at("BEUControls").render(dest);
	}
}

bool Button::getBool() {
	return isClicked_;
}
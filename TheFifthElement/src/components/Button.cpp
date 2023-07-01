#include "Button.h"
#include "../states/TopDownState.h"
#include "../GameManager.h"
#include "../Game.h"
#include "../states/CardGameState.h"
#include "../states/CardPauseState.h"

void Button::initComponent() {
	buttonTransform = ent_->getComponent<Transform>(TRANSFORM_H);
	im_ = ent_->getComponent<Image>(IMAGE_H);
}

void Button::update() {
	mouseRect = build_sdlrect(mousePos, mouseWidth, mouseHeight);
	if (Collision::collides(buttonTransform->getPos(), buttonTransform->getW(), buttonTransform->getH(), mousePos, mouseRect.w, mouseRect.h)) {
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
		else if (identifier == "EXITCONTROLS")im_->setTexture("ReturnButtonPressed");
		else if (identifier == "RETURN")im_->setTexture("ReturnButtonPressed");
		else if (identifier == "LOAD")im_->setTexture("LoadButtonPress");
		else if (identifier == "CARDS")im_->setTexture("cardPlayButtonPressed"); //hay que cambiar los botones
		else if (identifier == "CARDMENU")im_->setTexture("cardMenuButtonPressed");
		else if (identifier == "CARDRETURN")im_->setTexture("cardReturnButtonPressed");
	}
	else {
		if (identifier == "PLAY")im_->setTexture("PlayButton");
		else if (identifier == "EXIT")im_->setTexture("ExitButton");
		else if (identifier == "BACK")im_->setTexture("BackButton");
		else if (identifier == "OPTIONS")im_->setTexture("OptionsButton");
		else if (identifier == "RESUME")im_->setTexture("ResumeButton");
		else if (identifier == "MAINMENU")im_->setTexture("MenuButton");
		else if (identifier == "TDCONTROLS")im_->setTexture("TDControlsButton");
		else if (identifier == "BEUCONTROLS")im_->setTexture("BEUControlsButton");
		else if (identifier == "MUTE")im_->setTexture("MuteButton");
		else if (identifier == "EXITCONTROLS")im_->setTexture("ReturnButton");
		else if (identifier == "RETURN")im_->setTexture("ReturnButton");
		else if (identifier == "LOAD")im_->setTexture("LoadButton");
		else if (identifier == "CARDS")im_->setTexture("cardPlayButton"); //hay que cambiar el boton
		else if (identifier == "CARDMENU")im_->setTexture("cardMenuButton");
		else if (identifier == "CARDRETURN")im_->setTexture("cardReturnButton");
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
					SDLUtils::instance()->soundEffects().at("pruebaBoton").play();
					GameManager::instance()->leaveMainMenu();
				}
				else if (identifier == "CARDS")
				{
					SDLUtils::instance()->soundEffects().at("pruebaBoton").play();
					GameManager::instance()->goCardsGame();
				}
				else if (identifier == "CARDMENU")
				{
					SDLUtils::instance()->soundEffects().at("pruebaBoton").play();
					GameManager::instance()->backToMainMenu();
				}
				else if (identifier == "CARDRETURN")
				{
					SDLUtils::instance()->soundEffects().at("pruebaBoton").play();
					CardGameState* cardGameState = static_cast<CardPauseState*>(mngr_)->getCardState();
					cardGameState->pausedGame(false);
					GameManager::instance()->Pop();
				}
				else if (identifier == "LOAD") {
					SDLUtils::instance()->soundEffects().at("pruebaBoton").play();
					GameManager::instance()->LoadGame();
				}
				else if (identifier == "RESUME") {
					SDLUtils::instance()->soundEffects().at("pruebaBoton").play();
					GameManager::instance()->Pop();
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
					GameManager::instance()->getGame()->setExit(true);
				}
				else if (identifier == "UPTURN") {
					isClicked_ = true;
					TopDownState* topdownstate = static_cast<TopDownState*>(mngr_);
					topdownstate->getShopComp()->shopEconomy();
					if (topdownstate->getShopComp()->canPurchase()) {
						SDLUtils::instance()->soundEffects().at("pruebaBoton").play();
					}
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
					if (!muted) { //Mutea el juego (TODO).
					Mix_Volume(-1, 0);
					Mix_VolumeMusic(0);
					muted = true; 
					}

					else {
						Mix_VolumeMusic(64);
						Mix_Volume(-1, 64);
						muted = false;
					}
		
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
					OptionsState* optionsstate = static_cast<OptionsState*>(mngr_);
					optionsstate->Background("fondoPausa");
					optionsstate->ControlsBackground("controlPanel");
					optionsstate->createCharacter("PTD_water_right", PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME, Vector2D(WIN_WIDTH / 5, 350), 7, false, 1);
					optionsstate->createButtons();
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
	if (tdcontrols) {
		SDLUtils::instance()->images().at("TopDownControls").render(dest);
	}
	if (beucontrols) {
		SDLUtils::instance()->images().at("BEUControls").render(dest);
	}
}

bool Button::getBool() {
	return isClicked_;
}
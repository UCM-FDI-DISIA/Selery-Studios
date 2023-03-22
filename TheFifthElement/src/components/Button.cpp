#include "Button.h"

void Button::initComponent() {
	buttonTransform = ent_->getComponent<Transform>(TRANSFORM_H);
	im_ = ent_->getComponent<Image>(IMAGE_H);
	scale = buttonTransform->getS();
}

void Button::update() {
	mouseRect = build_sdlrect(mousePos, mouseWidth, mouseHeight);
	if (Collision::collides(buttonTransform->getPos(), buttonTransform->getW()*scale, buttonTransform->getH()*scale, mousePos, mouseRect.w, mouseRect.h))
	{
		currentPositionState = MOUSE_OVER;
		if (identifier == "PLAY")im_->setAnimTexture("PlayButtonPressed", 1, 289);
		else if (identifier == "EXIT")im_->setAnimTexture("ExitButtonPressed", 1, 289);
		else if (identifier == "OPTIONS")im_->setAnimTexture("OptionsButtonPressed", 1, 95);
		else if(identifier == "RESUME")im_->setAnimTexture("ResumeButtonPressed", 1, 289);
		else if (identifier == "MAINMENU")im_->setAnimTexture("MenuButtonPressed", 1, 289);
		else if (identifier == "BACK")im_->setAnimTexture("MenuButtonPressed", 1, 289);
	}
	else
	{
		if (identifier == "PLAY")im_->setAnimTexture("PlayButton", 1, 289);
		else if (identifier == "EXIT")im_->setAnimTexture("ExitButton", 1, 289);
		else if (identifier == "BACK")im_->setAnimTexture("BackButton", 1, 289);
		else if (identifier == "OPTIONS")im_->setAnimTexture("OptionsButton", 1, 95);
		else if (identifier == "RESUME")im_->setAnimTexture("ResumeButton", 1, 289);
		else if (identifier == "MAINMENU")im_->setAnimTexture("MenuButton", 1, 289);
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
					//SDLUtils::instance()->soundEffects().at("pruebaBoton").play();
					GameManager::instance()->leaveMainMenu();
				}
				else if (identifier == "RESUME") {
					SDLUtils::instance()->soundEffects().at("prueba").play();
					SDLUtils::instance()->soundEffects().at("Title").resumeChannel();
					//GameManager::instance()->goTopDown();
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
					SDL_Quit();
				}
				else if (identifier == "UPTURN") {
					SDLUtils::instance()->soundEffects().at("pruebaBoton").play();
					isClicked_ = true;
				}
				else if (identifier == "EXITSHOP") {
					cout << "salir tienda";
				}
				else if (identifier == "BACK") {
					GameManager::instance()->backToMainMenu();
				}
				//else if (identifier == "CONTROLS")
				//{
				//	//CARGA IMAGEN
				//}
			}
		}
	}
}

void Button::render() {
	SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 250, 0, 0);
	SDL_RenderDrawRect(GameManager::instance()->getRenderer(), &mouseRect);
	SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 0, 0, 255);
	isClicked_ = false;
}

bool Button::getBool() {
	return isClicked_;
}
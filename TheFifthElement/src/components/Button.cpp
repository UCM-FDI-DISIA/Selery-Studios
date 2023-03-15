#include "Button.h"

void Button::initComponent() {
	buttonTransform = ent_->getComponent<Transform>(TRANSFORM_H);
	im_ = ent_->getComponent<Image>(IMAGE_H);
}

void Button::update() {
	mouseRect = build_sdlrect(mousePos, mouseWidth, mouseHeight);
	if (Collision::collides(buttonTransform->getPos(), buttonTransform->getW(), buttonTransform->getH(), mousePos, mouseRect.w, mouseRect.h))
	{
		currentPositionState = MOUSE_OVER;
		if (identifier == "PLAY")im_->setAnimTexture("PlayButtonPressed", 1, 289);
		else if (identifier == "EXIT")im_->setAnimTexture("ExitButtonPressed", 1, 289);
		else if (identifier == "OPTIONS")im_->setAnimTexture("OptionsButtonPressed", 1, 95);
	}
	else
	{
		if (identifier == "PLAY")im_->setAnimTexture("PlayButton", 1, 289);
		else if (identifier == "EXIT")im_->setAnimTexture("ExitButton", 1, 289);
		else if (identifier == "OPTIONS")im_->setAnimTexture("OptionsButton", 1, 95);
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
				else if (identifier == "RESUME") {
					SDLUtils::instance()->soundEffects().at("prueba").play();
					SDLUtils::instance()->soundEffects().at("Title").resumeChannel();
					GameManager::instance()->goTopDown();
				}
				else if (identifier == "OPTIONS") {
					SDLUtils::instance()->soundEffects().at("pruebaBoton").play();
					// ir a menu de opciones
					cout << "opciones";
				}
				else if (identifier == "MAINMENU") {
					SDLUtils::instance()->soundEffects().at("pruebaBoton").play();
					GameManager::instance()->backToMainMenu();
				}
				else if (identifier == "EXIT") {
					//salir del juego
					cout << "salir";
				}

				else if (identifier == "UPTURN") {
					SDLUtils::instance()->soundEffects().at("pruebaBoton").play();
					cout << "1";
				}
			}
		}
	}
}

void Button::render() {
	SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 250, 0, 0);
	SDL_RenderDrawRect(GameManager::instance()->getRenderer(), &mouseRect);
	SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 0, 0, 255);
}

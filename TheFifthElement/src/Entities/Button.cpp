#include "Button.h"

void Button::initComponent(){
	buttonTransform = ent_->getComponent<Transform>(TRANSFORM_H);
}

void Button::update() {
	mouseRect = build_sdlrect(mousePos, mouseWidth, mouseHeight);
	if (Collision::collides(buttonTransform->getPos(),buttonTransform->getW(),buttonTransform->getH(), mousePos,mouseRect.w,mouseRect.h))
	{
		currentPositionState = MOUSE_OVER;
		cout << "a";
	}
	else 
	{
		currentPositionState = MOUSE_OUT;
	}
	updateMousePosition();
}

void Button::updateMousePosition() {
	SDL_GetMouseState(&mousePosX, &mousePosY);
	mousePos = Vector2D(mousePosX, mousePosY);
}

void Button::handleEvent(SDL_Event event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			if (currentPositionState == 1) 
			{
				if (identifier == "PLAY"){
					SDLUtils::instance()->soundEffects().at("pruebaBoton").play();
					GameManager::instance()->leaveMainMenu();
				}
				else if (identifier == "RESUME"){
					SDLUtils::instance()->soundEffects().at("pruebaBoton").play();
					SDLUtils::instance()->soundEffects().at("Title").resumeChannel();
					GameManager::instance()->goTopDown();					
				}
				else if (identifier == "OPTIONS") {
					SDLUtils::instance()->soundEffects().at("pruebaBoton").play(); 
					// ir a menu de opciones
				}
				else if (identifier == "MAINMENU") {
					SDLUtils::instance()->soundEffects().at("pruebaBoton").play(); 
					GameManager::instance()->backToMainMenu();
				}
			}
		}
	}
}

void Button::render(){
	SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 250, 0, 0);
	SDL_RenderDrawRect(GameManager::instance()->getRenderer(), &mouseRect);
	SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 0, 0, 255);
}

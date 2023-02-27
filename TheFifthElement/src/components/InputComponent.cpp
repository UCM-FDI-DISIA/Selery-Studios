#include "InputComponent.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Entity.h"
#include "../utils/ecs.h"
#include "../Entities/PlayerTD.h"
#include "../states/TopDownState.h"
InputComponent::InputComponent():Component() {
}
void InputComponent::initComponent() {
	mov_ = ent_->getComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	im_ = ent_->getComponent<Image>(IMAGE_H);
	skin_ = ent_->getComponent<SkinComponent>(SKINCOMPONENT_H);
}
void InputComponent::update() { //Actualizamos el contador que mide el tiempo
	unsigned timer = clock();
	actionDelay = (double(timer) / CLOCKS_PER_SEC);
}
void InputComponent::handleEvents(SDL_Event event)
{

	InputHandler::instance()->update(event);

	if (ih().keyDownEvent()){
		if (!npccol) {
			if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_A)) {
				mov_->setDir(Vector2D(-1, 0));
				im_->setAnimTexture("p_left", 7, 476);
			}
			else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_D)) {
				mov_->setDir(Vector2D(1, 0));
				im_->setAnimTexture("p_right", 7, 476);
			}
			else  if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_W)) {
				mov_->setDir(Vector2D(0, -1));
				im_->setAnimTexture("p_top", 9, 612);
			}
			else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_S)) {
				mov_->setDir(Vector2D(0, 1));
				im_->setAnimTexture("p_down", 9, 612);
			}
			else {
				mov_->setDir(Vector2D(0, 0));
				im_->setAnimTexture("p_idle", 7, 519);
			}

			if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_U)) {
				skin_->changeSkin("fire");
			}
			else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_I)) {
				skin_->changeSkin("air");
			}
			else  if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_O)) {
				skin_->changeSkin("water");
			}
			else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_P)) {
				skin_->changeSkin("earth");
			}
		}
		
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_E)) {
			
			if (actionDelay > 0) {
				int a = static_cast<PlayerTD*>(ent_)->getCol();
				cout << a;

				if (a != -1) {

					npccol = true;
					mov_->setDir(Vector2D(0, 0));
					static_cast<TopDownState*>(mngr_)->dialog(a);
				}

			}
			actionDelay = 0;
		}

	}
	
	
}
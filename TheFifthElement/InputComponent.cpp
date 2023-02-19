#include "InputComponent.h"
#include "sdlutils/InputHandler.h"
#include "utils/Entity.h"
#include "utils/ecs.h"
#include "PlayerTD.h"
#include "states/TopDownState.h"
InputComponent::InputComponent():Component() {
}
void InputComponent::initComponent() {
	mov_ = ent_->getComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	skin_ = ent_->getComponent<SkinComponent>(SKINCOMPONENT_H);
}
void InputComponent::update() {
	//mov_->setSpeed(Vector2D(-1, 0));
	
	/*if (InputHandler::instance()->isKeyDown(SDLK_LEFT)) {
		mov_->setSpeed(Vector2D(-1, 0));
	}
	else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_W)) {
		mov_->setSpeed(Vector2D(-1, 0));
	}
	else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_S)) {
		mov_->setSpeed(Vector2D(-1, 0));
	}
	else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_D)) {
		mov_->setSpeed(Vector2D(-1, 0));
	}
	else mov_->setSpeed(Vector2D(0, 0)); std::cout << "asf" << endl;*/
}


void InputComponent::handleEvents(SDL_Event event)
{

	InputHandler::instance()->update(event);

	if(InputHandler::instance()->keyDownEvent())
	{
		if (!npccol) {
			if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_A)) {
				mov_->setDir(Vector2D(-1, 0));
			}
			else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_D)) {
				mov_->setDir(Vector2D(1, 0));
			}
			else  if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_W)) {
				mov_->setDir(Vector2D(0, -1));
			}
			else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_S)) {
				mov_->setDir(Vector2D(0, 1));
			}
			else mov_->setDir(Vector2D(0, 0));

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
		
		
	}
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_E)) {
		cout << "f";
			int a = static_cast<PlayerTD*>(ent_)->getCol() != -1;
			if (a ) {
				npccol = true;
				mov_->setDir(Vector2D(0, 0));
				static_cast<TopDownState*>(mngr_)->dialog(a);
			}
		}

}
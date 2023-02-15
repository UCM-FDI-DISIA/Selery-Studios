#include "InputComponent.h"
#include "sdlutils/InputHandler.h"
#include "utils/Entity.h"
#include "utils/ecs.h"

InputComponent::InputComponent():Component() {
}
void InputComponent::initComponent() {
	mov_ = ent_->getComponent<MovementComponent>(MOVEMENTCOMPONENT_H);

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
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_A)) {
			mov_->setSpeed(Vector2D(-1, 0));
		}

		else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_D)) {
			mov_->setSpeed(Vector2D(1, 0));
		}
		
		else  if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_W)) {
			mov_->setSpeed(Vector2D(0, -1));
		}
	    else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_S)) {
			mov_->setSpeed(Vector2D(0, 1));
		}
		else mov_->setSpeed(Vector2D(0, 0)); 
	}
	

}
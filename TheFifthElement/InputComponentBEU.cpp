#include "InputComponentBEU.h"
#include "sdlutils/InputHandler.h"
#include "utils/Entity.h"
#include "utils/ecs.h"

InputComponentBEU::InputComponentBEU() :Component() {
}
void InputComponentBEU::initComponent() {
	mov_ = ent_->getComponent<MovementComponent>(MOVEMENTCOMPONENT_H);

}
void InputComponentBEU::initComponentBEU()
{
	mov_ = ent_->getComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
}
void InputComponentBEU::update() {

}


void InputComponentBEU::handleEvents(SDL_Event event)
{

	InputHandler::instance()->update(event);

	if (InputHandler::instance()->keyDownEvent())
	{
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
		else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_R)) {
			std::cout << "ATTACK" << endl;
		}
		else mov_->setDir(Vector2D(0, 0));
	}


}
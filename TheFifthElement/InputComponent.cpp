#include "InputComponent.h"
#include "sdlutils/InputHandler.h"
#include "utils/Entity.h"
#include "RenderComponent.h"
#include "utils/ecs.h"

InputComponent::InputComponent():Component() {
}
void InputComponent::initComponent() {
	mov_ = ent_->getComponent<MovementComponent>(MOVEMENTCOMPONENT_H);

}
void InputComponent::update() {
	//mov_->setSpeed(Vector2D(-1, 0));

	if (InputHandler::instance()->keyDownEvent()) {
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
	else mov_->setSpeed(Vector2D(0, 0)); std::cout << "asf" << endl;
}
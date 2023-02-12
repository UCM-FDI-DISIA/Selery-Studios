#include "InputComponent.h"
#include "sdlutils/InputHandler.h"
#include "utils/Entity.h"
#include "RenderComponent.h"
#include "utils/ecs.h"

InputComponent::InputComponent() {
	mov_ = ent_->getComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
}

void InputComponent::update() {
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_A)) {
		cout << "n" << endl;
	}
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_W)) {
		cout << "e" << endl;
	}
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_S)) {
		cout << "g" << endl;
	}
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_D)) {
		cout << "r" << endl;
	}
}
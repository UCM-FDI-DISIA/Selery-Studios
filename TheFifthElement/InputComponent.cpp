#include "InputComponent.h"
#include "sdlutils/InputHandler.h"
#include "utils/Entity.h"
#include "RenderComponent.h"

InputComponent::InputComponent() {
	mov = ent_->getComponent<MovementComponent>(_MOVEMENTCOMPONENT_);
}

void InputComponent::update() {
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_A)) {
		cout << "negro" << endl;
	}

	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_W)) {
		cout << "negro" << endl;
	}
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_S)) {
		cout << "negro" << endl;
	}
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_D)) {
		cout << "negro" << endl;
	}


}
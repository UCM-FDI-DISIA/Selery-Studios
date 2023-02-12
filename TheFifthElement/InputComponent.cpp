#include "InputComponent.h"
#include "sdlutils/InputHandler.h"
#include "utils/Entity.h"
#include "RenderComponent.h"
#include "utils/ecs.h"

InputComponent::InputComponent(MovementComponent * mov) {
	mov_ = mov;
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
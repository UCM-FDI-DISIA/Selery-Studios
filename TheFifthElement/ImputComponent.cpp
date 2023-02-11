#include "ImputComponent.h"
#include "sdlutils/InputHandler.h"
#include "utils/Entity.h"
#include "RenderComponent.h"

ImputComponent::ImputComponent() {
	mov = ent_->getComponent<MovementComponent>(_MOVEMENTCOMPONENT_);
	//RenderComponent* mov = ent_->getComponent<RenderComponent>(RENDERCOMPONENT_H_);
}

void ImputComponent::update() {
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
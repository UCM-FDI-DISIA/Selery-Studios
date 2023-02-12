#include "InputComponent.h"
#include "sdlutils/InputHandler.h"
#include "utils/Entity.h"
#include "RenderComponent.h"
#include "utils/ecs.h"

<<<<<<< Updated upstream
InputComponent::InputComponent(MovementComponent * mov) {
	mov_ = mov;
=======
InputComponent::InputComponent(MovementComponent* Mov_) {
	mov_ = Mov_;
	//mov_ = ent_->getComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
>>>>>>> Stashed changes
}

void InputComponent::update() {
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_A)) {
		cout << "negro" << endl;
	}
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_W)) {
		cout << "negro" << endl;
	}
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_S)) {
		cout << "negro" << endl;
	}
	if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_D)) {
		cout << "negro" << endl;
	}
<<<<<<< Updated upstream


=======
>>>>>>> Stashed changes
}
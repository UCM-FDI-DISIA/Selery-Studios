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
	skin_ = ent_->getComponent<SkinComponent>(SKINCOMPONENT_H);
}
void InputComponent::update() {
	if (InputHandler::instance()->keyDownEvent())
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
	else mov_->setDir(Vector2D(0, 0));
	if (ih().isKeyDown(SDL_SCANCODE_E)) {
		if (actionDelay > 0) { // The shorterpaddle and biggerpaddle rewards is activated REWARDS_TIME seconds
			int a = static_cast<PlayerTD*>(ent_)->getCol() != -1;

			if (a) {
				cout << "2";
				npccol = true;
				mov_->setDir(Vector2D(0, 0));
				GameState* g = GameStateMachine::instance()->currentState();
				static_cast<TopDownState*>(g)->dialog(a);
			}

		}
		actionDelay = 0;
	}
	//Actualizamos el contador que mide el tiempo
	unsigned timer = clock();
	actionDelay = (double(timer) / CLOCKS_PER_SEC);

}
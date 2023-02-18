#include "InputComponentBEU.h"
#include "sdlutils/InputHandler.h"
#include "utils/Entity.h"
#include "utils/ecs.h"
#include "PlayerBEU.h"

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
void InputComponentBEU::stop_attack() {
	attack = false;
}

void InputComponentBEU::handleEvents(SDL_Event event)
{

	InputHandler::instance()->update(event);

	if (InputHandler::instance()->keyDownEvent())
	{
		if (!(static_cast<PlayerBEU*>(ent_)->getAttack())) {
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
				SDLUtils::instance()->soundEffects().at("playerAttack").play();
			}
			else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_E)) {
			SDLUtils::instance()->soundEffects().at("playerSpecialAttack").play();

			}
			else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_Q)) {
				//attack = true;
				static_cast<PlayerBEU*>(ent_)->setAttack(true);

			}
			else mov_->setDir(Vector2D(0, 0));
		}
		else mov_->setDir(Vector2D(0, 0));

		
	}


}
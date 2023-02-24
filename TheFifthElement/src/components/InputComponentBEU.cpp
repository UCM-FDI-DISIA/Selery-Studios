#include "InputComponentBEU.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Entity.h"
#include "../utils/ecs.h"
#include "../Entities/PlayerBEU.h"
#include "Image.h"
#include "../states/BeatEmUpState.h"

InputComponentBEU::InputComponentBEU() :Component() {

}

void InputComponentBEU::initComponent() {
	mov_ = ent_->getComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	im_ = ent_->getComponent<Image>(IMAGE_H);
}

void InputComponentBEU::update() {

}
void InputComponentBEU::handleEvents(SDL_Event event){

	InputHandler::instance()->update(event);

	
		if (!(static_cast<PlayerBEU*>(ent_)->getAttack())) 
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
			else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_O)) {
			    SDLUtils::instance()->soundEffects().at("playerAttack").play();
				im_->setAnim(true, 7, 10, 0, 0);
				static_cast<PlayerBEU*>(ent_)->setAttack(true);
			}
			else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_P)) {
			    SDLUtils::instance()->soundEffects().at("playerSpecialAttack").play();
				im_->setAnim(true, 10, 17, 0, 0);
				static_cast<PlayerBEU*>(ent_)->setAttack(true);
			}
			else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_M)) {
				static_cast<BeatEmUpState*>(mngr_)->finishBEU();
			}
			else mov_->setDir(Vector2D(0, 0));
		}
		
		else mov_->setDir(Vector2D(0, 0));
	
}
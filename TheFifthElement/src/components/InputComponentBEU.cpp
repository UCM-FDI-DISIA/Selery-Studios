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
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	im_ = ent_->getComponent<Image>(IMAGE_H);
	t_ = new Texture(GameManager::instance()->getRenderer(), "./assets/PlayableCharacters/BeatEmUp/Fire/spritesheets/fireMatrix.png");
}

void InputComponentBEU::update() {

}

void InputComponentBEU::handleEvents(SDL_Event event){
	InputHandler::instance()->update(event);
		if (!im_->isAnimPlaying()) {
			if (ih().isKeyDown(SDL_SCANCODE_A)) { // Mover Izquierda
				tr_->setDir(Vector2D(-1, 0));
				im_->setAnim(false, 1, 8, 0, 0, t_);
				im_->setFlip(SDL_FLIP_HORIZONTAL);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_D)) { // Mover Derecha
				tr_->setDir(Vector2D(1, 0));
				im_->setAnim(false, 1, 8, 0, 0, t_);
				im_->setFlip(SDL_FLIP_NONE);
			}
			else  if (ih().isKeyDown(SDL_SCANCODE_W)) { // Mover Arriba
				tr_->setDir(Vector2D(0, -1));
				im_->setAnim(false, 1, 8, 0, 0, t_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_S)) { // Mover Abajo
				tr_->setDir(Vector2D(0, 1));
				im_->setAnim(false, 1, 8, 0, 0, t_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_SPACE) && canJump) { // Salto
				im_->setAnim(true, 4, 20, 0, 0);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_O)) { // Ataque
			    sdlutils().soundEffects().at("playerAttack").play();
				im_->setAnim(true, 7, 10, 0, 0, t_);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_P)) { // Ataque Especial
<<<<<<< Updated upstream
			    SDLUtils::instance()->soundEffects().at("playerSpecialAttack").play();
				im_->setAnim(true, 10, 18, 0, 0, t_);
=======
				sdlutils().soundEffects().at("playerSpecialAttack").play();
				im_->setAnim(true, 10, 18, 0, 0);
>>>>>>> Stashed changes
			}
			else if (ih().isKeyDown(SDL_SCANCODE_M)) {
				static_cast<BeatEmUpState*>(mngr_)->finishBEU();
			}
			else {
				tr_->setDir(Vector2D(0, 0));
				im_->setAnim(false, 0, 8, 0, 0, t_);
			}
		}
		else {
			tr_->setDir(Vector2D(0, 0));
			im_->setAnim(false, 0, 8, 0, 0, t_);
		}
}
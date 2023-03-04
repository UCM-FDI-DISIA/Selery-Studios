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
	jmp_ = ent_->getComponent<JumpComponent>(JUMP_H);
	t_ = new Texture(GameManager::instance()->getRenderer(), "./assets/Player/BeatEmUp/Fire/spritesheets/fireMatrix.png");
}

void InputComponentBEU::update() {

}

void InputComponentBEU::handleEvents(SDL_Event event) {
	ih().update(event);
	if (ih().keyDownEvent()) {
		if (!im_->isAnimPlaying()) {
			if (ih().isKeyDown(SDL_SCANCODE_SPACE) && jmp_->isJumpEnabled()) { // Salto
				im_->setAnim(true, 4, 14, 0);
				jmp_->jump();
			}
			if (ih().isKeyDown(SDL_SCANCODE_A)) { // Mover Izquierda
				tr_->setDir(Vector2D(-1, 0));
				im_->setAnim(false, 1, 8, 0);
				im_->setFlip(SDL_FLIP_HORIZONTAL);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_D)) { // Mover Derecha
				tr_->setDir(Vector2D(1, 0));
				im_->setAnim(false, 1, 8, 0);
				im_->setFlip(SDL_FLIP_NONE);
			}
			else  if (ih().isKeyDown(SDL_SCANCODE_W) && tr_->getPos().getY()) { // Mover Arriba
				tr_->setDir(Vector2D(0, -1));
				im_->setAnim(false, 1, 8, 0);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_S) && tr_->getPos().getY()) { // Mover Abajo
				tr_->setDir(Vector2D(0, 1));
				im_->setAnim(false, 1, 8, 0);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_O)) { // Ataque
				sdlutils().soundEffects().at("playerAttack").play();
				im_->setAnim(true, 9, 24, 0);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_P)) { // Ataque Especial
				sdlutils().soundEffects().at("playerSpecialAttack").play();
				im_->setAnim(true, 10, 18, 0);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_M)) {
				static_cast<BeatEmUpState*>(mngr_)->finishBEU();
			}
			else { // Idle
				tr_->setDir(Vector2D(0, 0));
				im_->setAnim(true, 0, 8, 0);
			}
		}
		else if (jmp_->isJumpEnabled()) {
			tr_->setDir(Vector2D(0, 0));
			im_->setAnim(false, 0, 8, 0);
		}
	}
}


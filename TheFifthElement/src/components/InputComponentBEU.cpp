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
	lifeC_ = ent_->getComponent<LifeComponent>(LIFECOMPONENT_H);
	shadow = ent_->getComponent<ShadowComponent>(SHADOWCOMPONENT_H);
	assert(shadow != nullptr);
	sk_ = ent_->getComponent<SkinBEUComponent>(SKINBEUCOMPONENT_H);
}

void InputComponentBEU::update() {
	if (!im_->isAnimPlaying()) { // Si no esta realizando ninguna acción no cancelable
		if (moveLeft) {
			tr_->setDir(Vector2D(-1, 0));
			sk_->changeState(SkinBEUComponent::Left);
		}
		else if (moveRight) {
			tr_->setDir(Vector2D(1, 0));
			sk_->changeState(SkinBEUComponent::Right);
		}
		else if (moveUp) {
			tr_->setDir(Vector2D(0, -1));
			sk_->changeState(SkinBEUComponent::Vertical);
		}
		else if (moveDown) {
			tr_->setDir(Vector2D(0, 1));
			sk_->changeState(SkinBEUComponent::Vertical);
		}
		else {
			tr_->setDir(Vector2D(0, 0));
			sk_->changeState(SkinBEUComponent::Idle);
		}
	}
	else if (jmp_->isJumpEnabled()) { // Esta realizando una acción no cancelable (distinta del salto)
		tr_->setDir(Vector2D(0, 0));
	}
	else { // Está saltando
		if (moveLeft) {
			tr_->setDir(Vector2D(-1, tr_->getDir().getY()));
			im_->setFlip(SDL_FLIP_HORIZONTAL);
		}
		else if (moveRight) {
			tr_->setDir(Vector2D(1, tr_->getDir().getY()));
			im_->setFlip(SDL_FLIP_NONE);
		}
	}
}

void InputComponentBEU::handleEvents(SDL_Event event) {
	ih().update(event);

	if (ih().isKeyDown(SDL_SCANCODE_SPACE) && !im_->isAnimPlaying() && jmp_->isJumpEnabled()) { // Salto
		jmp_->jump();
		sk_->changeState(SkinBEUComponent::Jump); // A lo mejor 15 cambia porque se le pueden dar o puede necesitar mas frames de salto

		shadow->Setpos_y(tr_->getPos().getY());
	}

	if (ih().isKeyDown(SDL_SCANCODE_A)) { // Mover Izquierda
		moveLeft = true;
	}
	else if (ih().isKeyUp(SDL_SCANCODE_A)) { moveLeft = false; }

	if (ih().isKeyDown(SDL_SCANCODE_D)) { // Mover Derecha
		moveRight = true;
	}
	else if (ih().isKeyUp(SDL_SCANCODE_D)) { moveRight = false; }

	if (ih().isKeyDown(SDL_SCANCODE_W)) { // Mover Arriba
		moveUp = true;
	}
	else if (ih().isKeyUp(SDL_SCANCODE_W)) { moveUp = false; }


	if (ih().isKeyDown(SDL_SCANCODE_S)) { // Mover Abajo
		moveDown = true;
	}
	else if (ih().isKeyUp(SDL_SCANCODE_S)) { moveDown = false; }


	if (ih().isKeyDown(SDL_SCANCODE_1) && !im_->isAnimPlaying()) {
		sk_->changeSkin("air");
		lifeC_->chageType("wind", 10);
	}

	if (ih().isKeyDown(SDL_SCANCODE_2) && !im_->isAnimPlaying()) {
		sk_->changeSkin("fire");
		lifeC_->chageType("fire", 10);
	}

	if (ih().isKeyDown(SDL_SCANCODE_3) && !im_->isAnimPlaying()) {
		sk_->changeSkin("water");
		lifeC_->chageType("water", 10);
	}

	if (ih().isKeyDown(SDL_SCANCODE_4) && !im_->isAnimPlaying()) {
		sk_->changeSkin("earth");
		lifeC_->chageType("earth", 10);
	}


	if (ih().isKeyJustDown(SDL_SCANCODE_O)) {
		if (!alreadyPressedBasic) {
			sdlutils().soundEffects().at("playerAttack").play();
			alreadyPressedBasic = true;
			if (im_->getRow() == 9) {
				if (im_->getTope() < 3 * 8) {
					im_->setTope(im_->getTope() + 8);
				}
			}
			else {
				im_->setAnim(true, 9, 24, 0, 8);
			}
		}
	}
	else if (ih().isKeyJustUp(SDL_SCANCODE_O)) alreadyPressedBasic = false;

	if (ih().isKeyDown(SDL_SCANCODE_P) && !alreadyPressedBasic) {
		// Ataque Especial
		if (!alreadyPressedSpecial) {
			alreadyPressedSpecial = true;
			sdlutils().soundEffects().at("playerSpecialAttack").play();
			im_->setAnim(true, 10, 18, 0, 100);
		}
	}
	else if (ih().isKeyJustUp(SDL_SCANCODE_P)) alreadyPressedSpecial = false;

	if (ih().isKeyJustDown(SDL_SCANCODE_M)) {
		if (!alreadyPressed2)
		{
			alreadyPressed2 = true;
			static_cast<BeatEmUpState*>(mngr_)->finishBEU();
		}
	}
	else if (ih().isKeyJustUp(SDL_SCANCODE_M)) {
		alreadyPressed2 = false;
	}

	if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
		GameManager::goPauseMenu();
	}
}

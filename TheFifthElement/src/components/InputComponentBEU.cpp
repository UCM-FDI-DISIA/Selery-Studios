#include "InputComponentBEU.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Entity.h"
#include "../utils/ecs.h"
#include "../Entities/PlayerBEU.h"
#include "Image.h"
#include "../states/BeatEmUpState.h"


InputComponentBEU::InputComponentBEU() :Component() {
	elements[0] = true;
	for (int i = 1; i < 4; i++) elements[i] = true;
	// por defecto solo está disponible aire
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
	if (!im_->isAnimPlaying() && jmp_->isJumpEnabled()) { // Si no esta realizando ninguna acci�n no cancelable
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
	else if (jmp_->isJumpEnabled()) { // Esta realizando una acci�n no cancelable (distinta del salto)
		tr_->setDir(Vector2D(0, 0));
	}
	else { // Est� saltando
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


	if (ih().isKeyDown(SDL_SCANCODE_1) && elements[0] && !im_->isAnimPlaying()) {
		sk_->changeSkin("air");
	}

	if (ih().isKeyDown(SDL_SCANCODE_2) && elements[1] && !im_->isAnimPlaying()) {
		sk_->changeSkin("fire");
	}

	if (ih().isKeyDown(SDL_SCANCODE_3) && elements[2] && !im_->isAnimPlaying()) {
		sk_->changeSkin("water");
	}

	if (ih().isKeyDown(SDL_SCANCODE_4) && elements[3] && !im_->isAnimPlaying()) {
		sk_->changeSkin("earth");
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

void InputComponentBEU::setAir(bool b) 
{ 
	elements[0] = b; 
	if (!b) {
		if (elements[1]) sk_->changeSkin("fire");
		else if (elements[2])sk_->changeSkin("water");
		else sk_->changeSkin("earth");
	}

}

void InputComponentBEU::setFire(bool b) 
{ 
	elements[1] = b;
	if (!b) {
		if (elements[2]) sk_->changeSkin("water");
		else if (elements[3])sk_->changeSkin("earth");
		else sk_->changeSkin("air");
	}
}

void InputComponentBEU::setWater(bool b) 
{ 
	elements[2] = b; 
	if (!b) {
		if (elements[3]) sk_->changeSkin("earth");
		else if (elements[0])sk_->changeSkin("air");
		else sk_->changeSkin("fire");
	}
}

void InputComponentBEU::setEarth(bool b) 
{ 
	elements[3] = b; 
	if (!b) {
		if (elements[0]) sk_->changeSkin("air");
		else if (elements[1])sk_->changeSkin("fire");
		else sk_->changeSkin("water");
	}
}

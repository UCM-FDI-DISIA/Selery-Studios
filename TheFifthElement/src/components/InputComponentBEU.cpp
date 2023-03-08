﻿#include "InputComponentBEU.h"
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

void InputComponentBEU::update()
{



	cout << jump << endl;
	//if (jump)
	//{
	//	im_->setAnim(true, 4, 14, 0, 100);
	//	jmp_->jump();

	//}
	if (moveLeft)
	{
		tr_->setDir(Vector2D(-1, 0));
		im_->setAnim(false, 1, 8, 0, 100);
		im_->setFlip(SDL_FLIP_HORIZONTAL);
	}
	else if (moveRight)
	{
		tr_->setDir(Vector2D(1, 0));
		im_->setAnim(false, 1, 8, 0, 100);
		im_->setFlip(SDL_FLIP_NONE);
	}
	else if (moveUp)
	{
		tr_->setDir(Vector2D(0, -1));
		im_->setAnim(false, 1, 8, 0, 100);
	}
	else if (moveDown)
	{
		tr_->setDir(Vector2D(0, 1));
		im_->setAnim(false, 1, 8, 0, 100);
	}
	else
	{
		tr_->setDir(Vector2D(0, 0));
	}
}

void InputComponentBEU::handleEvents(SDL_Event event) {


	ih().update(event);

	if (ih().isKeyDown(SDL_SCANCODE_SPACE) && jmp_->isJumpEnabled()) { // Salto
		im_->setAnim(true, 4, 14, 0, 100);
		jmp_->jump();
	}
	/*	else if (jmp_->isJumpEnabled()) {
			tr_->setDir(Vector2D(0, 0));
			im_->setAnim(false, 0, 8, 0, 100);
		}*/

	if (ih().isKeyDown(SDL_SCANCODE_A))
	{ // Mover Izquierda
		moveLeft = true;
	}
	else if (ih().isKeyUp(SDL_SCANCODE_A))	moveLeft = false;

	if (ih().isKeyDown(SDL_SCANCODE_D))
	{ // Mover Izquierda
		moveRight = true;
	}
	else if (ih().isKeyUp(SDL_SCANCODE_D))	moveRight = false;

	if (ih().isKeyDown(SDL_SCANCODE_W))
	{ // Mover Izquierda
		moveUp = true;
	}
	else if (ih().isKeyUp(SDL_SCANCODE_W))	moveUp = false;


	if (ih().isKeyDown(SDL_SCANCODE_S))
	{ // Mover Izquierda
		moveDown = true;
	}
	else if (ih().isKeyUp(SDL_SCANCODE_S))	moveDown = false;

	if (ih().isKeyJustDown(SDL_SCANCODE_O))
	{
		if (!alreadyPressedBasic)
		{
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

	if (ih().isKeyDown(SDL_SCANCODE_P) && !alreadyPressedBasic)
	{
		// Ataque Especial
		if (!alreadyPressedSpecial)
		{
			alreadyPressedSpecial = true;
			sdlutils().soundEffects().at("playerSpecialAttack").play();
			im_->setAnim(true, 10, 18, 0, 100);
		}
		
	}
	else if (ih().isKeyJustUp(SDL_SCANCODE_P)) alreadyPressedSpecial = false;

     if (ih().isKeyJustDown(SDL_SCANCODE_M))
	{
		if (!alreadyPressed2)
		{
			alreadyPressed2 = true;
			static_cast<BeatEmUpState*>(mngr_)->finishBEU();
		}
	}
	else if (ih().isKeyJustUp(SDL_SCANCODE_M))
	{
		alreadyPressed2 = false;
	}

	/*else if (jmp_->isJumpEnabled()) {
		tr_->setDir(Vector2D(0, 0));
		im_->setAnim(false, 0, 8, 0, 100);

	}*/
	if (ih().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		GameManager::goPauseMenu();
	}

}
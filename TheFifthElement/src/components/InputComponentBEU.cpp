#include "InputComponentBEU.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Entity.h"
#include "../utils/ecs.h"
#include "Image.h"
#include "../states/BeatEmUpState.h"


InputComponentBEU::InputComponentBEU(Roulette* r):Component() {
	elements[0] = Elements::instance()->getAir();
	elements[1] = Elements::instance()->getFire();
	elements[2] = Elements::instance()->getWater();
	elements[3] = Elements::instance()->getEarth();
	// por defecto solo está disponible aire
	roulette = r;

}

void InputComponentBEU::initComponent() {
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	im_ = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
	jmp_ = ent_->getComponent<JumpComponent>(JUMP_H);
	lifeC_ = ent_->getComponent<LifeComponent>(LIFECOMPONENT_H);
	shadow = ent_->getComponent<ShadowComponent>(SHADOWCOMPONENT_H);
	assert(shadow != nullptr);
	sk_ = ent_->getComponent<SkinBEUComponent>(SKINBEUCOMPONENT_H);
	if (SDL_NumJoysticks() < 1) {
		// No hay gamepads conectados
	}
	else {
		// Se detectA un gamepad
		controller = SDL_GameControllerOpen(0);
		if (controller == NULL) {


		}
	}
}

void InputComponentBEU::update() {	
	if (!im_->getIsAnimUnstoppable() && jmp_->isJumpEnabled()) { // Si no esta realizando ninguna accion no cancelable
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
	else if (jmp_->isJumpEnabled()) { // Esta realizando una accion no cancelable (distinta del salto)
		tr_->setDir(Vector2D(0, 0));
	}
	else { // Esta saltando
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

	if ((ih().isKeyDown(SDL_SCANCODE_SPACE) || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)) && !im_->getIsAnimUnstoppable() && jmp_->isJumpEnabled()) { // Salto
		jmp_->jump();
		sk_->changeState(SkinBEUComponent::Jump); // A lo mejor 15 cambia porque se le pueden dar o puede necesitar mas frames de salto
		shadow->Setpos_y(tr_->getPos().getY());
	}

	if (ih().isKeyDown(SDL_SCANCODE_A) || SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) < -8000) { // Mover Izquierda
		moveLeft = true;
	}
	else if (ih().isKeyUp(SDL_SCANCODE_A) || SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) >= -8000) { moveLeft = false; }

	if (ih().isKeyDown(SDL_SCANCODE_D) || SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) > 8000) { // Mover Derecha
		moveRight = true;
	}
	else if (ih().isKeyUp(SDL_SCANCODE_D) || SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) <= 8000) { moveRight = false; }

	if (ih().isKeyDown(SDL_SCANCODE_W) || SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) < -8000) { // Mover Arriba
		moveUp = true;
	}
	else if (ih().isKeyUp(SDL_SCANCODE_W) || SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) >= -8000) { moveUp = false; }


	if (ih().isKeyDown(SDL_SCANCODE_S) || SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) > 8000) { // Mover Abajo
		moveDown = true;
	}
	else if (ih().isKeyUp(SDL_SCANCODE_S) || SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) <= 8000) { moveDown = false; }


	if ((ih().isKeyDown(SDL_SCANCODE_1) || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) && elements[0] && !im_->getIsAnimUnstoppable()) {
		sk_->changeSkin("air");
		roulette->changeplayer(1);
	}

	if ((ih().isKeyDown(SDL_SCANCODE_2) || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP)) && elements[1] && !im_->getIsAnimUnstoppable() ) {
		sk_->changeSkin("fire");
		roulette->changeplayer(2);
	}

	if ((ih().isKeyDown(SDL_SCANCODE_3) || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) && elements[2] && !im_->getIsAnimUnstoppable()) {
		sk_->changeSkin("water");
		roulette->changeplayer(3);
	}

	if ((ih().isKeyDown(SDL_SCANCODE_4) || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) && elements[3] && !im_->getIsAnimUnstoppable()) {
		sk_->changeSkin("earth");
		roulette->changeplayer(4);
	}

	if ((ih().isKeyJustDown(SDL_SCANCODE_O) || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X)) && jmp_->isJumpEnabled()) {
		if (!alreadyPressedBasic) {
			sdlutils().soundEffects().at("playerAttack").play();
			alreadyPressedBasic = true;
			if(im_->getType()=="fire")
			{
				if (im_->getTexKey() == "Player_BEU_" + im_->getType() + "_attack3") {
					if (im_->getTope() <=  8) {
						im_->setTope(im_->getTope() + 8);
					}
					else
					{
						im_->setTope(im_->getTope() + 10);
					}
				}
				else {
					im_->setAnim("Player_BEU_" + im_->getType() + "_attack3",0, 26, true);
					im_->setTope(8);
				}
				
			}
			else if (im_->getType()=="water")
			{
				if (im_->getTexKey() == "Player_BEU_" + im_->getType() + "_attack3") {
					if (im_->getTope() <= 8) {
						im_->setTope(im_->getTope() + 7);
					}
					else
					{
						im_->setTope(im_->getTope() + 10);
					}
				}
				else {
					im_->setAnim("Player_BEU_" + im_->getType() + "_attack3", 0, 26, true);
					im_->setTope(8);
				}
			}
			else if(im_->getType()=="air")
			{
				if (im_->getTexKey() == "Player_BEU_" + im_->getType() + "_attack3") {
					if (im_->getTope() <= 8) {
						im_->setTope(im_->getTope() + 6);
					}
					else
					{
						im_->setTope(im_->getTope() + 14);
					}
				}
				else {
					im_->setAnim("Player_BEU_" + im_->getType() + "_attack3", 0, 26, true);
					im_->setTope(6);
				}
			}
			else
			{
				if (im_->getTexKey() == "Player_BEU_" + im_->getType() + "_attack3") {
					if (im_->getTope() <= 4) {
						im_->setTope(im_->getTope() + 5);
					}
					else
					{
						im_->setTope(im_->getTope() + 14);
					}
				}
				else {
					im_->setAnim("Player_BEU_" + im_->getType() + "_attack3", 0, 23, true);
					im_->setTope(4);
				}
			}
		}
	}
	else if (ih().isKeyJustUp(SDL_SCANCODE_O) || !ih().isGamePadButtonDown(SDL_CONTROLLER_BUTTON_X)) alreadyPressedBasic = false;

	if ((ih().isKeyDown(SDL_SCANCODE_P) || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y)) && !alreadyPressedBasic && jmp_->isJumpEnabled()) {
		// Ataque Especial
		if (im_->getType() == "fire" || im_->getType() == "water")
		{
			if (!alreadyPressedSpecial) {
				alreadyPressedSpecial = true;
				sdlutils().soundEffects().at("playerSpecialAttack").play();
				im_->setAnim("Player_BEU_" + im_->getType() + "_super", 18, true);
			}
		}
		else if(im_->getType()=="air")
		{
			if (!alreadyPressedSpecial) {
				alreadyPressedSpecial = true;
				sdlutils().soundEffects().at("playerSpecialAttack").play();
				im_->setAnim("Player_BEU_" + im_->getType() + "_super", 28, true);
			}
		}
		else
		{
			if (!alreadyPressedSpecial) {
				alreadyPressedSpecial = true;
				sdlutils().soundEffects().at("playerSpecialAttack").play();
				im_->setAnim("Player_BEU_" + im_->getType() + "_super", 25, true);
			}
		}
	
	}
	else if (ih().isKeyJustUp(SDL_SCANCODE_P) || !ih().isGamePadButtonDown(SDL_CONTROLLER_BUTTON_Y)) alreadyPressedSpecial = false;

	if (ih().isKeyJustDown(SDL_SCANCODE_E)) {
		if (!alreadyPressed2 && earthStage3) // Recogida de piedras en el stage 3 del boss de tierra
		{
			for (auto it : mngr_->getEntities()) {
				if (it->hasComponent(OBJECTSCOMPONENT_H) && it->getComponent<ObjectsComponent>(OBJECTSCOMPONENT_H)->getInRange()) {
					static_cast<StoneComponent*>(it->getComponent<StoneComponent>(STONECOMPONENT_H))->stonePicked();
					alreadyPressed2 = true;
				}
			}
			
		}
	}
	else if (ih().isKeyJustUp(SDL_SCANCODE_E)) {
		alreadyPressed2 = false;
	}

	if (ih().isKeyDown(SDL_SCANCODE_ESCAPE) || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START)) {
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

// Función para hacer que el mando de Xbox vibre
void InputComponentBEU::vibrate(SDL_GameController* controller, int duration_ms, float intensity) {
	// Comprobar si el mando está conectado
	if (!SDL_GameControllerGetAttached(controller)) {
		printf("El mando no está conectado\n");
		return;
	}

	// Comprobar si el mando tiene retroalimentación de fuerza
	if (!SDL_JoystickIsHaptic(SDL_GameControllerGetJoystick(controller))) {
		printf("El mando no tiene retroalimentación de fuerza\n");
		return;
	}

	// Abrir el dispositivo de retroalimentación de fuerza (haptic device)
	SDL_Haptic* haptic = SDL_HapticOpenFromJoystick(SDL_GameControllerGetJoystick(controller));
	if (haptic == NULL) {
		printf("No se pudo abrir el dispositivo haptic: %s\n", SDL_GetError());
		return;
	}

	// Configurar la intensidad y duración de la vibración
	if (SDL_HapticRumbleInit(haptic) != 0) {
		printf("No se pudo inicializar la retroalimentación de fuerza: %s\n", SDL_GetError());
		SDL_HapticClose(haptic);
		return;
	}
	if (SDL_HapticRumblePlay(haptic, intensity, duration_ms) != 0) {
		printf("No se pudo hacer que el mando vibre: %s\n", SDL_GetError());
		SDL_HapticClose(haptic);
		return;
	}

	// Esperar hasta que termine la vibración
	SDL_Delay(duration_ms);

	// Liberar los recursos usados por el dispositivo haptic
	SDL_HapticClose(haptic);
}
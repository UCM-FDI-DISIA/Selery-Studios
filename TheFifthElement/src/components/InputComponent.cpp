#include "InputComponent.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Entity.h"
#include "../utils/ecs.h"
#include "../states/TopDownState.h"
#include "DialogueComponent.h"
#include <string>
const int joystick_deadzone = 8000;


InputComponent::InputComponent(Roulette* r) :Component() {
	d = NONE;
	roulet = r;
	//s = td;
	// por defecto solo está disponible aire
}

void InputComponent::initComponent() {
	mov_ = ent_->getComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	skin_ = ent_->getComponent<SkinComponent>(SKINCOMPONENT_H);
	dialog = ent_->getComponent<DialogueComponent>(DIALOGCOMPONENT_H);
	//setContext();	

	 if (SDL_NumJoysticks() < 1) {
		 // No hay gamepads conectados
		 controladorDetectado = false;
	 }
	 else {
		 // Se detectA un gamepad
		 controller = SDL_GameControllerOpen(0);
	 }
}
void InputComponent::update() { //Actualizamos el contador que mide el tiempo
	unsigned timer = clock();
	actionDelay = (double(timer) / CLOCKS_PER_SEC);

	if (!dialog->gethasstarted()) {
		if (moveLeft) {
			mov_->setDir(Vector2D(-1, 0));
			skin_->changeState(SkinComponent::Left);
		}
		else if (moveRight) {
			mov_->setDir(Vector2D(1, 0));
			skin_->changeState(SkinComponent::Right);
		}
		else if (moveUp) {
			mov_->setDir(Vector2D(0, -1));
			skin_->changeState(SkinComponent::Up);
		}
		else if (moveDown) {
			mov_->setDir(Vector2D(0, 1));
			skin_->changeState(SkinComponent::Down);
		}
		else {
			mov_->setDir(Vector2D(0, 0));
			skin_->changeState(SkinComponent::Idle);
		}
	}
	else {
		mov_->setDir(Vector2D(0, 0));
		skin_->changeState(SkinComponent::Idle);
	}
}


void InputComponent::handleEvents(SDL_Event event)
{
	if(controladorDetectado)
	{
		if (SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) < -8000 && d != LEFT) {
			mov_->setDir(Vector2D(-1, 0));
			skin_->changeState(SkinComponent::Left);
		}
		
		else if (SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) > 8000 && d != RIGHT) {
			mov_->setDir(Vector2D(1, 0));
			skin_->changeState(SkinComponent::Right);
		}
		else  if (SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) < -8000 && d != UP) {
			mov_->setDir(Vector2D(0, -1));
			skin_->changeState(SkinComponent::Up);
		}
		else if (SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) > 8000 && d != DOWN) {
			mov_->setDir(Vector2D(0, 1));
			skin_->changeState(SkinComponent::Down);
		}
		else if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START)) {
			GameManager::goPauseMenu();
		}
		else if (abs(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX)) < joystick_deadzone && abs(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY)) < joystick_deadzone) {		// No ha habido movimiento en el eje horizontal izquierd
			mov_->setDir(Vector2D(0, 0));
			skin_->changeState(SkinComponent::Idle);
		}
		if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) && !dialog->getopenedShop()) {

			if (canTalk) {
				canTalk = false;
				mov_->setDir(Vector2D(0, 0));
				if (actionDelay > 0) {
					dialog->inicombe();
					sdlutils().soundEffects().at("NPC_Chat").play();
				}
				actionDelay = 0;
			}
		}
		if (SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_DPAD_DOWN) && Elements::instance()->getAir()) {
			skin_->changeSkin("air");
			roulet->changeplayer(1);
			//static_cast<HUD*>(ent_)->
		}
		else if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP) && Elements::instance()->getFire()) {
			roulet->changeplayer(2);

			skin_->changeSkin("fire");
		}
		else  if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT) && Elements::instance()->getWater()) {
			roulet->changeplayer(3);

			skin_->changeSkin("water");
		}
		else if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) && Elements::instance()->getEarth()) {
			roulet->changeplayer(4);

			skin_->changeSkin("earth");
		}
	}

	ih().update(event);
	if (ih().keyDownEvent()){
		if (!dialog->gethasstarted() && !dialog->getopenedShop()) {
			if ((ih().isKeyDown(SDL_SCANCODE_J))) {
				if(canSave)
				{
					static_cast<TopDownState*>(mngr_)->SaveGame();
					canSave = false;
					//s->SaveGame();
				}
			}
			else if (ih().isKeyUp(SDL_SCANCODE_J))
			{
				canSave = true;
			}
		
			if ((ih().isKeyDown(SDL_SCANCODE_T))) {
				if (canLoad)
				{
					canLoad = false;
					static_cast<TopDownState*>(mngr_)->LoadGame();
					//s->LoadGame();

				}
			}
			else if (ih().isKeyUp(SDL_SCANCODE_T))
			{
				canLoad = true;
			}



			if (ih().isKeyDown(SDL_SCANCODE_A) && d != LEFT) {
				moveLeft = true;
			}
			else if (ih().isKeyUp(SDL_SCANCODE_A) || d == LEFT) { moveLeft = false; }
			if (ih().isKeyDown(SDL_SCANCODE_D) && d != RIGHT) {
				moveRight = true;
			}
			else if (ih().isKeyUp(SDL_SCANCODE_D) || d == RIGHT) { moveRight = false; }
			
			if (ih().isKeyDown(SDL_SCANCODE_W) && d != UP ) {
				moveUp = true;
			}
			else if (ih().isKeyUp(SDL_SCANCODE_W) || d == UP) { moveUp = false; }

			if (ih().isKeyDown(SDL_SCANCODE_S)&&d!=DOWN ) {
				moveDown = true;
			}
			else if (ih().isKeyUp(SDL_SCANCODE_S) || d == DOWN) { moveDown = false; }
			

			if (ih().isKeyDown(SDL_SCANCODE_1) && Elements::instance()->getAir()) {
				skin_->changeSkin("air");
				roulet->changeplayer(1);
				skin_->changeAvatar(&SDLUtils::instance()->images().at("AirAvatar"));
			}
			else if (ih().isKeyDown(SDL_SCANCODE_2) && Elements::instance()->getFire()) {
				roulet->changeplayer(2);
				skin_->changeSkin("fire");
				skin_->changeAvatar(&SDLUtils::instance()->images().at("FireAvatar"));
			}
			else  if (ih().isKeyDown(SDL_SCANCODE_3) && Elements::instance()->getWater()) {
				roulet->changeplayer(3);
				skin_->changeSkin("water");
				skin_->changeAvatar(&SDLUtils::instance()->images().at("WaterAvatar"));
			}
			else if (ih().isKeyDown(SDL_SCANCODE_4) && Elements::instance()->getEarth()) {
				roulet->changeplayer(4);
				skin_->changeSkin("earth");
				skin_->changeAvatar(&SDLUtils::instance()->images().at("EarthAvatar"));
			}
		}

		if (ih().isKeyDown(SDL_SCANCODE_E) && !dialog->getopenedShop()){

			if (canTalk)
			{
				canTalk = false;
				mov_->setDir(Vector2D(0, 0));
				if (actionDelay > 0) {
					dialog->inicombe();
					sdlutils().soundEffects().at("NPC_Chat").play();
				}
				actionDelay = 0;
			}
			
		}
		else if(ih().isKeyUp(SDL_SCANCODE_E))
		{
			canTalk = true;
		}

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE) && !dialog->gethasstarted() && !dialog->getopenedShop() /* || SDL_GameControllerButton(SDL_CONTROLLER_BUTTON_A)*/) {
			GameManager::goPauseMenu();
		}

		//if (ih().isKeyDown(SDL_SCANCODE_Q)) static_cast<TopDownState*>(mngr_)->questsMenu = !static_cast<TopDownState*>(mngr_)->questsMenu;

		if (ih().isKeyDown(SDL_SCANCODE_X) && static_cast<TopDownState*>(mngr_)->getMenuQuest()) 
			static_cast<TopDownState*>(mngr_)->setMenuQuest(false);
		else if (ih().isKeyDown(SDL_SCANCODE_Q) && !static_cast<TopDownState*>(mngr_)->getMenuQuest()) 
			static_cast<TopDownState*>(mngr_)->setMenuQuest(true);

		if (ih().isKeyDown(SDL_SCANCODE_0)) //cambio a pantalla completa podria ser una opcion
		{
			SDL_SetWindowFullscreen(SDLUtils::instance()->window(), SDL_WINDOW_FULLSCREEN); //tambien se puede usar _DESKTOP
		}

	}
}
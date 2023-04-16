#include "InputComponent.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Entity.h"
#include "../utils/ecs.h"
#include "../states/TopDownState.h"
#include <string>
const int joystick_deadzone = 8000;


InputComponent::InputComponent(Roulette* r) :Component() {
	d = NONE;
	roulet = r;
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

			mov_->setDir(Vector2D(0, 0));
			if (actionDelay > 0) {
				dialog->inicombe();
				sdlutils().soundEffects().at("NPC_Chat").play();
			}
			actionDelay = 0;
		}
	}

	ih().update(event);
	if (ih().keyDownEvent()){
		if (!dialog->gethasstarted() && !dialog->getopenedShop()) {
			
			if (ih().isKeyDown(SDL_SCANCODE_A) && d != LEFT) {
				mov_->setDir(Vector2D(-1, 0));
				skin_->changeState(SkinComponent::Left);
			}
			
			else if (ih().isKeyDown(SDL_SCANCODE_D) && d != RIGHT) {
				mov_->setDir(Vector2D(1, 0));
				skin_->changeState(SkinComponent::Right);
			}
			
			else  if (ih().isKeyDown(SDL_SCANCODE_W) && d != UP ) {
				mov_->setDir(Vector2D(0, -1));
				skin_->changeState(SkinComponent::Up);
			}

			else if (ih().isKeyDown(SDL_SCANCODE_S)&&d!=DOWN ) {
				mov_->setDir(Vector2D(0, 1));
				skin_->changeState(SkinComponent::Down);
			}

			else {
				mov_->setDir(Vector2D(0, 0));
				skin_->changeState(SkinComponent::Idle);
			}

			if (ih().isKeyDown(SDL_SCANCODE_1) && Elements::instance()->getAir()) {
				skin_->changeSkin("air");
				roulet->changeplayer(1);
				//static_cast<HUD*>(ent_)->
			}
			else if (ih().isKeyDown(SDL_SCANCODE_2) && Elements::instance()->getFire()) {
				roulet->changeplayer(2);

				skin_->changeSkin("fire");
			}
			else  if (ih().isKeyDown(SDL_SCANCODE_3) && Elements::instance()->getWater()) {
				roulet->changeplayer(3);

				skin_->changeSkin("water");
			}
			else if (ih().isKeyDown(SDL_SCANCODE_4) && Elements::instance()->getEarth()) {
				roulet->changeplayer(4);

				skin_->changeSkin("earth");
			}
		}
		
		if (ih().isKeyDown(SDL_SCANCODE_E) && !dialog->getopenedShop()){

			mov_->setDir(Vector2D(0, 0));
			if (actionDelay > 0) {
				dialog->inicombe();
				sdlutils().soundEffects().at("NPC_Chat").play();
			}
			actionDelay = 0;
		}

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE) && !dialog->gethasstarted() && !dialog->getopenedShop() /* || SDL_GameControllerButton(SDL_CONTROLLER_BUTTON_A)*/) {
			GameManager::goPauseMenu();
		}

		if (ih().isKeyDown(SDL_SCANCODE_0)) //cambio a pantalla completa podria ser una opcion
		{
			SDL_SetWindowFullscreen(SDLUtils::instance()->window(), SDL_WINDOW_FULLSCREEN); //tambien se puede usar _DESKTOP
		}
	}
}
#include "InputComponent.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Entity.h"
#include "../utils/ecs.h"
#include "../Entities/PlayerTD.h"
#include "../states/TopDownState.h"
#include <string>

InputComponent::InputComponent(Roulette* r) :Component() {
	d = NONE;
	roulet = r;
	elements[0] = true;
	for (int i = 1; i < 4; i++) elements[i] = true;
	// por defecto solo está disponible aire
}

void InputComponent::initComponent() {
	mov_ = ent_->getComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	skin_ = ent_->getComponent<SkinComponent>(SKINCOMPONENT_H);
	 dialog = ent_->getComponent<DialogueComponent>(DIALOGCOMPONENT_H);
	//setContext();	
}
void InputComponent::update() { //Actualizamos el contador que mide el tiempo
	unsigned timer = clock();
	actionDelay = (double(timer) / CLOCKS_PER_SEC);
}


void InputComponent::handleEvents(SDL_Event event)
{
	ih().update(event);

	if (ih().keyDownEvent()){
		if (!dialog->gethasstarted() && !dialog->getopenedShop()) {
			if (ih().isKeyDown(SDL_SCANCODE_A)&& d!= LEFT) {
				mov_->setDir(Vector2D(-1, 0));
				skin_->changeState(SkinComponent::Left);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_D) && d!=RIGHT) {
				mov_->setDir(Vector2D(1, 0));
				skin_->changeState(SkinComponent::Right);
			}
			else  if (ih().isKeyDown(SDL_SCANCODE_W)&& d!=UP) {
				mov_->setDir(Vector2D(0, -1));
				skin_->changeState(SkinComponent::Up);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_S)&&d!=DOWN) {
				mov_->setDir(Vector2D(0, 1));
				skin_->changeState(SkinComponent::Down);
			}
			else {
				mov_->setDir(Vector2D(0, 0));
				skin_->changeState(SkinComponent::Idle);
			}

			if (ih().isKeyDown(SDL_SCANCODE_1) && elements[0]) {
				skin_->changeSkin("air");
				roulet->changeplayer(1);
				//static_cast<HUD*>(ent_)->
			}
			else if (ih().isKeyDown(SDL_SCANCODE_2) && elements[1]) {
				roulet->changeplayer(2);

				skin_->changeSkin("fire");
			}
			else  if (ih().isKeyDown(SDL_SCANCODE_3) && elements[2]) {
				roulet->changeplayer(3);

				skin_->changeSkin("water");
			}
			else if (ih().isKeyDown(SDL_SCANCODE_4) && elements[3]) {
				roulet->changeplayer(4);

				skin_->changeSkin("earth");
			}
		}
		
		if (ih().isKeyDown(SDL_SCANCODE_E)) {

			mov_->setDir(Vector2D(0, 0));
			if (actionDelay > 0) {
				dialog->inicombe();
			}
			actionDelay = 0;
		}

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
			GameManager::goPauseMenu();
		}
	}
}
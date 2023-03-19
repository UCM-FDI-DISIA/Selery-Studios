#include "InputComponent.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Entity.h"
#include "../utils/ecs.h"
#include "../Entities/PlayerTD.h"
#include "../states/TopDownState.h"
#include <string>

InputComponent::InputComponent() :Component() {
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
		if (!npccol) {
			if (ih().isKeyDown(SDL_SCANCODE_A)) {
				mov_->setDir(Vector2D(-1, 0));
				skin_->changeState(SkinComponent::Left);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_D)) {
				mov_->setDir(Vector2D(1, 0));
				skin_->changeState(SkinComponent::Right);
			}
			else  if (ih().isKeyDown(SDL_SCANCODE_W)) {
				mov_->setDir(Vector2D(0, -1));
				skin_->changeState(SkinComponent::Up);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_S)) {
				mov_->setDir(Vector2D(0, 1));
				skin_->changeState(SkinComponent::Down);
			}
			else {
				mov_->setDir(Vector2D(0, 0));
				skin_->changeState(SkinComponent::Idle);
			}

			if (ih().isKeyDown(SDL_SCANCODE_1)) {
				skin_->changeSkin("fire");
				//static_cast<HUD*>(ent_)->
			}
			else if (ih().isKeyDown(SDL_SCANCODE_2)) {
				skin_->changeSkin("air");
			}
			else  if (ih().isKeyDown(SDL_SCANCODE_3)) {
				skin_->changeSkin("water");
			}
			else if (ih().isKeyDown(SDL_SCANCODE_4)) {
				skin_->changeSkin("earth");
			}
		}
		
		if (ih().isKeyDown(SDL_SCANCODE_E)) {
			if (actionDelay > 0) {
				dialog->inicombe();
				/*int a = static_cast<PlayerTD*>(ent_)->getCol();
				cout << a;

				if (a != -1) {

					npccol = true;
					mov_->setDir(Vector2D(0, 0));
					static_cast<TopDownState*>(mngr_)->dialog(a);
					SDLUtils::instance()->soundEffects().at("NPC_Chat").play();
				}*/

			}
			actionDelay = 0;
		}

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
			GameManager::goPauseMenu();
		}
	}
}
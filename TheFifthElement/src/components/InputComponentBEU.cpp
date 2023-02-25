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
	tr_ = ent_->getComponent<Transform>(MOVEMENTCOMPONENT_H);
	im_ = ent_->getComponent<Image>(IMAGE_H);

}

void InputComponentBEU::update() {

    cout << tr_->getDir().getX() << " " <<tr_->getDir().getY() << endl;
    if (ih().keyDownEvent()) {
        if (!(im_->isAnimPlaying())) {
            if (ih().isKeyDown(SDL_SCANCODE_A)) { // Andar izquierda
                tr_->setDir(Vector2D(-1, 0));
                im_->setAnim(false, 1, 8, 0, 0);
                im_->setFlip(SDL_FLIP_HORIZONTAL);
            }
            else if (ih().isKeyDown(SDL_SCANCODE_D)) { // Andar derecha
                tr_->setDir(Vector2D(1, 0));
                im_->setAnim(false, 1, 8, 0, 0);
                im_->setFlip(SDL_FLIP_NONE);
            }
            else if (ih().isKeyDown(SDL_SCANCODE_W)) { // Andar arriba
                tr_->setDir(Vector2D(0, -1));
            }
            else if (ih().isKeyDown(SDL_SCANCODE_S)) { // Andar abajo
                tr_->setDir(Vector2D(0, 1));
            }
            else {  // Idle
                tr_->setDir(Vector2D(0, 0));
                im_->setAnim(false, 0, 8, 0, 0);
            }
            
            if (ih().isKeyDown(SDL_SCANCODE_SPACE)) { // Salto

            }
            else if (ih().isKeyDown(SDL_SCANCODE_O)) { // Ataque normal
                sdlutils().soundEffects().at("playerAttack").play();
               im_->setAnim(true, 7, 10, 0, 0);
            }
            else if (ih().isKeyDown(SDL_SCANCODE_P)) { // Ataque especial
                sdlutils().soundEffects().at("playerSpecialAttack").play();
                im_->setAnim(true, 10, 17, 0, 0);
            }
        }
    }
    else { // Idle
        tr_->setDir(Vector2D(0, 0));
        im_->setAnim(false, 0, 8, 0, 0);
    }
}
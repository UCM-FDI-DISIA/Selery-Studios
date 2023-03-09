#include "JumpComponent.h"

JumpComponent::JumpComponent() {}
JumpComponent::~JumpComponent() {}

void JumpComponent::initComponent() {
    tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
    im_ = ent_->getComponent<Image>(IMAGE_H);
    assert(tr_ != nullptr);
    assert(im_ != nullptr);
}

void JumpComponent::update() {
    if (!canJump) {
        // Si el jugador ha alcanzado el punto mas alto del salto, invertir la velocidad del salto
        if (im_->getCol() == 3) { ctr = true; }
        else if (im_->getCol() == 7 && ctr) {
            jumpSpeed = -jumpSpeed;
            ctr = false;
        }
        else if (im_->getCol() == 9) { ctr = true; }

        // Actualizar la posicion vertical del jugador en funci�n de la velocidad del salto
        tr_->setDir(Vector2D(tr_->getDir().getX(), -jumpSpeed));

        // Si el jugador ha alcanzado la altura m�xima del salto, establecer canJump en verdadero
        if (tr_->getPos().getY() >= jumpHeigth && ctr) {
            canJump = true;
            tr_->setDir(Vector2D(tr_->getDir().getX(), 0));
            jumpSpeed = -jumpSpeed;
            ctr = false;
        }
    }
}

void JumpComponent::jump() {
    if (canJump) {
        jumpHeigth = tr_->getPos().getY();
        canJump = false;
    }
}

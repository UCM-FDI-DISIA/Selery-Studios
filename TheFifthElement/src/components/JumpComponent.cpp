#include "JumpComponent.h"

JumpComponent::JumpComponent(){}
JumpComponent::~JumpComponent() {}

void JumpComponent::initComponent() {
    tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
    im_ = ent_->getComponent<Image>(IMAGE_H);
    assert(tr_ != nullptr);
    assert(im_ != nullptr);
}

void JumpComponent::update() {
    if (!canJump) {
        // Si el jugador ha alcanzado el punto más alto del salto, invertir la velocidad del salto
        if (im_->getCol() == 7) jumpSpeed = -jumpSpeed;

        // Actualizar la posición vertical del jugador en función de la velocidad del salto
        tr_->setDir(Vector2D(tr_->getDir().getX(), -jumpSpeed));

        // Si el jugador ha alcanzado la altura máxima del salto, establecer canJump en verdadero
        if (tr_->getPos().getY() >= jumpHeigth) {
            canJump = true;
            ctr = false;
            jumpSpeed = -jumpSpeed;
        }

        ctr = true;
    }
}

void JumpComponent::jump() {
    if (canJump) {
        jumpHeigth = tr_->getPos().getY();
        canJump = false;
    }
}
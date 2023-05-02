#include "JumpComponent.h"

JumpComponent::JumpComponent() {}
JumpComponent::~JumpComponent() {}

void JumpComponent::initComponent() {
    tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
    assert(tr_ != nullptr);
    jumpHeigth = tr_->getH()*3/4;
}

void JumpComponent::update() {
    if (!canJump) {
        // Si el jugador ha alcanzado el punto mas alto del salto, invertir la velocidad del salto
        if (groundHeigth - jumpHeigth >= tr_->getPos().getY()) {
            jumpSpeed = -jumpSpeed;
            ctr = true;
        }
       
        // Actualizar la posicion vertical del jugador en funci�n de la velocidad del salto
        tr_->setDir(Vector2D(tr_->getDir().getX(), -jumpSpeed));

        // Si el jugador ha alcanzado la altura maxima del salto, establecer canJump en verdadero
        if (ctr && tr_->getPos().getY() >= groundHeigth) {
            canJump = true;
            tr_->setDir(Vector2D(tr_->getDir().getX(), 0));
            jumpSpeed = -jumpSpeed;
            ctr = false;
        }
    }
}

void JumpComponent::jump() {
    if (canJump) {
        groundHeigth = tr_->getPos().getY();
        canJump = false;
        ctr = false;
    }
}

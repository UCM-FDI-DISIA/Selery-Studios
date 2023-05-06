﻿#include "EnemyBEUDirectionComponent.h"
#include "../utils/Entity.h"
#include "../utils/ecs.h"

const float UPPER_Y_LIMIT = WIN_WIDTH/4; // Define el límite superior en el eje Y
const float LOWER_Y_LIMIT = WIN_WIDTH / 3; // Define el límite inferior en el eje Y


EnemyBEUDirectionComponent::EnemyBEUDirectionComponent(Entity* p, string type) :Component() {
	dir_ = Vector2D(0.0f, 0.0f);
	player_ = p;
	type_ = type;
}

void EnemyBEUDirectionComponent::initComponent() {
	mov_ = ent_->getComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	playerTr_ = player_->getComponent<Transform>(TRANSFORM_H);
	playerCol_ = player_->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
}

void EnemyBEUDirectionComponent::update() {
	if (!set_) {
		col_ = ent_->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
		set_ = true;
	}
	if (!stop_ && player_ != nullptr) {

		Vector2D Poffset_ = playerCol_->getOffset();// player offset
		float w_ = playerTr_->getW();// player frame width
		float h_ = playerTr_->getH();// player frame height
		float pcw_ = playerCol_->getColWidth();// player collider width
		float pch_ = playerCol_->getColHeight();// player collider height

		float playerPosX = playerTr_->getPos().getX() + Poffset_.getX();;// player pos X

		Vector2D offset_ = col_->getOffset();// enemy offset
		w_ = tr_->getW();// enemy frame width
		h_ = tr_->getH();// enemy frame height
		float cw_ = col_->getColWidth();// enemy collider width
		float ch_ = col_->getColHeight();// enemy collider height

		float posX = tr_->getPos().getX() + offset_.getX();// enemy pos X

		float posY, targetY;

		if (type_ != "bat") {
			float playerFloor = playerTr_->getPos().getY() + Poffset_.getY() + pch_;// player pos Y (floor)

			posY = tr_->getPos().getY();// enemy pos Y
			targetY = playerFloor - offset_.getY() - ch_;// target point Y
		}
		else {

			posY = tr_->getPos().getY() + offset_.getY();// enemy pos Y
			targetY = playerTr_->getPos().getY() + Poffset_.getY();// target point Y
		}

		if (posX > playerPosX) playerPosX += pcw_ / 2;
		else playerPosX -= pcw_ / 2;

		Vector2D director_ = Vector2D(playerPosX - posX, targetY - posY);

		float dist_ = sqrt(pow(director_.getX(), 2) + pow(director_.getY(), 2));// distance
		if (dist_ <= distance_)
		{
			speed = 0.005f;
			changeDir(director_);
		}

		else //cuando el personaje no está dentro del rango de detección del enemigo
		{
			if (cont >= 100)
			{
				float rnd = rand() % 201;
				rnd -= 100;
				rnd = rnd / 100.00f;
				changeDir(Vector2D(dir_.getX(), rnd));
				cont = 0;
			}

			if (tr_->getPos().getX() >= WIN_WIDTH * 1.8/*esto debería ser el punto máximo de la pantalla al que se puede llegar*/)
				izq = true;// tiene que ir a la izquierda

			else if (tr_->getPos().getX() <= 0/*principio de pantalla*/)
				izq = false;// tiene que ir a la derecha


			if (izq) changeDir(Vector2D(-1.0f, dir_.getY()));
			else changeDir(Vector2D(1.0f, dir_.getY()));
			// Aplica límites en el eje Y
			if (tr_->getPos().getY() <= UPPER_Y_LIMIT) changeDir(Vector2D(dir_.getX(), 1.0f));
			else if (tr_->getPos().getY() >= LOWER_Y_LIMIT - (tr_->getH())/*final de pantalla*/)
				changeDir(Vector2D(dir_.getX(), -1.0f));

			speed = 0.5f;
			cont++;
		}

		direction = 1; // Por defecto, se mueve hacia la derecha
		if (playerTr_->getPos().getX() < tr_->getPos().getX()) {
			direction = -1; // Si el jugador está a la derecha, se mueve hacia la izquierda
		}

	}
	mov_->setDir(dir_ * speed);//move
}

void EnemyBEUDirectionComponent::changeDir(Vector2D d)
{
	dir_ = d;
}

void EnemyBEUDirectionComponent::moveBackX() {
	Vector2D currPos = tr_->getPos();
	currPos.set(currPos.getX() - 35.0 * direction, currPos.getY());
	tr_->setPos(currPos);
}

void EnemyBEUDirectionComponent::stop(bool s)
{
	if (s)changeDir(Vector2D(0, 0));
	stop_ = s;
}
#include "EnemyBEUDirectionComponent.h"
#include "../utils/Entity.h"
#include "../utils/ecs.h"

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
	if (!stop_) {

		Vector2D offset_ = playerCol_->getOffset();// player offset
		float w_ = playerTr_->getW();// player frame width
		float h_ = playerTr_->getH();// player frame height
		float pcw_ = playerCol_->getColWidth();// player collider width
		float pch_ = playerCol_->getColHeight();// player collider height

		float playerPosX = playerTr_->getPos().getX() + offset_.getX() /* + cw_ / 2*/;// player pos X
		float playerFloor = playerTr_->getPos().getY() + offset_.getY() + pch_;// player pos Y (floor)

		offset_ = col_->getOffset();// enemy offset
		w_ = tr_->getW();// enemy frame width
		h_ = tr_->getH();// enemy frame height
		float cw_ = col_->getColWidth();// enemy collider width
		float ch_ = col_->getColHeight();// enemy collider height

		float posX = tr_->getPos().getX() + offset_.getX();// enemy pos X
		float posY = tr_->getPos().getY();// enemy pos Y
		float targetY = playerFloor - offset_.getY() - ch_;// target point Y

		if (posX > playerPosX) playerPosX += pcw_;
		else playerPosX -= pcw_/2;

		Vector2D director_ = Vector2D(playerPosX - posX, targetY - posY);

		float dist_ = sqrt(pow(director_.getX(), 2) + (director_.getY(), 2));// distancia
		if (dist_ <= distance_)
		{
			speed = 0.005f;
			changeDir(director_);
		}

		else //cuando el personaje no est� dentro del rango de detecci�n del enemigo
		{
			if (cont >= 100)
			{
				float rnd = rand() % 201;
				rnd -= 100;
				rnd = rnd / 100.00f;
				changeDir(Vector2D(dir_.getX(), rnd));
				cont = 0;
				//if (!static_cast<EnemyBEU*>(ent_)->getSet())static_cast<EnemyBEU*>(ent_)->setSet(true);
			}

			if (tr_->getPos().getX() >= screenWidth_ /* - tr_->getW() / 4*//*final de pantalla*/)
				izq = true;// tiene que ir a la izquierda

			else if (tr_->getPos().getX() <= 0/*principio de pantalla*/)
				izq = false;// tinene que ir a la derecha


			if (izq) changeDir(Vector2D(-1.0f, dir_.getY()));
			else changeDir(Vector2D(1.0f, dir_.getY()));

			if (tr_->getPos().getY() <= screenHeight_/*mitad de pantalla*/) changeDir(Vector2D(dir_.getX(), 1.0f));
			else if (tr_->getPos().getY() >= 425 - tr_->getH()/*final de pantalla*/)changeDir(Vector2D(dir_.getX(), -1.0f));

			speed = 0.5f;
			cont++;
		}
	}
	mov_->setDir(dir_ * speed);//move
}

void EnemyBEUDirectionComponent::changeDir(Vector2D d)
{
	dir_ = d;
}

void EnemyBEUDirectionComponent::stop(bool s)
{
	if (s) {
		changeDir(Vector2D(0, 0));
	}
	stop_ = s;
}
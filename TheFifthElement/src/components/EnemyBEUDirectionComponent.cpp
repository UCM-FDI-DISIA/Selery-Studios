#include "EnemyBEUDirectionComponent.h"
#include "../utils/Entity.h"
#include "../utils/ecs.h"
#include "../Entities/EnemyBEU.h"

EnemyBEUDirectionComponent::EnemyBEUDirectionComponent(PlayerBEU* p, string type) :Component() {
	dir_ = Vector2D(0.0f, 0.0f);
	player_ = p;
	type_ = type;
}

void EnemyBEUDirectionComponent::initComponent() {
	mov_ = ent_->getComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	playerTr_ = player_->getComponent<Transform>(TRANSFORM_H);
	im_ = ent_->getComponent<Image>(IMAGE_H);
	//t_
}

void EnemyBEUDirectionComponent::update() {
	Vector2D director_ = Vector2D((playerTr_->getPos().getX()+50)-tr_->getPos().getX(),
		playerTr_->getPos().getY() - tr_->getPos().getY());
	float dist_ = sqrt(pow(director_.getX(), 2)+(director_.getY(), 2));
	if (dist_ <= distance_) {
		mov_->setDir(director_ * 0.01f);//move
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

		if (tr_->getPos().getX() >= 750 /* - tr_->getW() / 4*//*final de pantalla*/)
		{
			izq = true;// tiene que ir a la izquierda
			im_->setFlip(SDL_FLIP_HORIZONTAL);
			if(type_ != "skeleton" && type_ != "bat")static_cast<EnemyBEU*>(ent_)->setOffset(Vector2D(55, 55));
		}
		else if (tr_->getPos().getX() <= 0/*principio de pantalla*/)
		{
			izq = false;// tinene que ir a la derecha
			im_->setFlip(SDL_FLIP_NONE);
			if (type_ != "skeleton" && type_ != "bat")static_cast<EnemyBEU*>(ent_)->setOffset(Vector2D(50, 55));
		}

		if (izq) changeDir(Vector2D(-1.0f, dir_.getY()));
		else changeDir(Vector2D(1.0f, dir_.getY()));

		if (tr_->getPos().getY() <= 200/*mitad de pantalla*/) changeDir(Vector2D(dir_.getX(), 1.0f));
		else if (tr_->getPos().getY() >= 425 - tr_->getH()/*final de pantalla*/)changeDir(Vector2D(dir_.getX(), -1.0f));

		mov_->setDir(dir_ * 0.5);//move

		cont++;
	}
}

void EnemyBEUDirectionComponent::changeDir(Vector2D d) 
{
	dir_ = d;
}
#include "EnemyBEUDirectionComponent.h"
#include "utils/Entity.h"
#include "utils/ecs.h"

EnemyBEUDirectionComponent::EnemyBEUDirectionComponent() :Component() {
	dir_ = Vector2D(0.0f, 0.0f);
}
void EnemyBEUDirectionComponent::initComponent() {
	mov_ = ent_->getComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
}
void EnemyBEUDirectionComponent::update() {

	//cuando el personaje no está dentro del rango de detección del enemigo
	if (cont >= 100) 
	{
		float rnd = rand() % 201;
		rnd -= 100;
		rnd = rnd / 100.00f;
		changeDir(Vector2D(dir_.getX(), rnd));
		cont = 0;
	}

	if (tr_->getPos().getX() >= 600 - tr_->getW() / 4/*final de pantalla*/) izq = true;// tiene que ir a la izquierda
	else if (tr_->getPos().getX() <= 0/*principio de pantalla*/) izq = false;// tinene que ir a la derecha

	if (izq) changeDir(Vector2D(-1.0f, dir_.getY()));
	else changeDir(Vector2D(1.0f, dir_.getY()));

	if (tr_->getPos().getY() <= 200/*mitad de pantalla*/) changeDir(Vector2D(dir_.getX(), 1.0f));
	else if(tr_->getPos().getY() >= 425- tr_->getH()/*final de pantalla*/)changeDir(Vector2D(dir_.getX(), -1.0f));

	mov_->setDir(dir_*0.5);//move

	cont++;
}

void EnemyBEUDirectionComponent::changeDir(Vector2D d) 
{
	dir_ = d;
}
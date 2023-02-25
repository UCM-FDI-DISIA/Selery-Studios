#include "EnemyBEUDirectionComponent.h"
#include "utils/Entity.h"
#include "utils/ecs.h"

EnemyBEUDirectionComponent::EnemyBEUDirectionComponent(PlayerBEU* p) :Component() {
	dir_ = Vector2D(0.0f, 0.0f);
	player_ = p;
}

void EnemyBEUDirectionComponent::initComponent() {
	mov_ = ent_->getComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	playerTr_ = player_->getComponent<Transform>(TRANSFORM_H);
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

		if (tr_->getPos().getX() >= 600 - tr_->getW() / 4/*final de pantalla*/) izq = true;// tiene que ir a la izquierda
		else if (tr_->getPos().getX() <= 0/*principio de pantalla*/) izq = false;// tinene que ir a la derecha

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


/*void EnemyBEUDirectionComponent::handleEvents()
{

	InputHandler::instance()->update(event);

	if (InputHandler::instance()->keyDownEvent())
	{
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_A)) {
			mov_->setDir(Vector2D(-1, 0));
		}

		else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_D)) {
			mov_->setDir(Vector2D(1, 0));
		}

		else  if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_W)) {
			mov_->setDir(Vector2D(0, -1));
		}
		else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_S)) {
			mov_->setDir(Vector2D(0, 1));
		}
		else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_R)) {
			std::cout << "ATTACK" << endl;
		}
		else mov_->setDir(Vector2D(0, 0));
	}


}*/

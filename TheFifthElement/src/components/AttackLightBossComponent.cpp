#include "AttackLightBossComponent.h"

AttackLightBossComponent::AttackLightBossComponent(Entity* player)
{
	player_ = player;
	fightState = 1;
	contAtks = 0;
	dirMov = Vector2D(0, 0);
}

void AttackLightBossComponent::initComponent()
{
	movBoss_ = ent_->getComponent<MovementLightBossComponent>(MOVEMENTLIGHTBOSSCOMPONENT_H);
	playerTrans = player_->getComponent<Transform>(TRANSFORM_H);
	bossTrans = ent_->getComponent<Transform>(TRANSFORM_H);
	timer = sdlutils().currRealTime() + 3000;
}

void AttackLightBossComponent::setState(int state)
{
	fightState = state;
}

void AttackLightBossComponent::update()
{
	distX = playerTrans->getPos().getX() - bossTrans->getPos().getX();
	distY = playerTrans->getPos().getY() - bossTrans->getPos().getY();

	if (timer<=sdlutils().currRealTime())
	{
		if (fightState == 1)
		{
			contAtks++;
			if (contAtks == 3)
			{
				contAtks = 0;
				timer = sdlutils().currRealTime() + 3000;
				attack2();
			}
			else { timer = sdlutils().currRealTime() + 3000; attack1(); cout << playerTrans->getPos(); }
		}
		else if (fightState == 2)
		{

		}
		else if (fightState == 3)
		{

		}
		else if (fightState == 4)
		{

		}
	}
}

void AttackLightBossComponent::attack1()//esto debe ser para generar siempre bolas y no solo en fase1
{
	if (distX<closeX && distX>negCloseX && distY<closeY && distY>negCloseY)//si esta muy cerca se aleja para disparar
	{
		if (distX <= 0) { dirMov.setX(1); }
		else { dirMov.setX(-1); }
		movBoss_->move(dirMov);
	}
	//orden de ejecucion: move, set anim al atk2 y despues crear la flecha
	Entity* sphere= new Entity();
	arrowTrans_ = sphere->addComponent<Transform>(TRANSFORM_H, Vector2D(bossTrans->getPos().getX(), bossTrans->getPos().getY()+bossTrans->getH()/2), 256, 128);
	arrowIm_ = sphere->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at("SphereArrow"), 256, 128, 12);
	if (distX <= 0) { dirAtk = Vector2D(-1, 0); arrowIm_->setFlip(SDL_FLIP_HORIZONTAL); }
	else { dirAtk = Vector2D(1, 0); }
	arrowTrans_->setVel(5.0);
	arrowTrans_->setDir(dirAtk);
	sphere->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	sphere->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(96,48),32,64);//datos metidos a mano deberian ser mediante metodos
	sphere->addComponent<DisableOnExit>(DISABLEONEXIT_H);
	sphere->addComponent<ColDetectorComponent>(COLDETECTORCOMPONENT_H, sphere, player_);
	sphere->addComponent<LightBossElement>(LIGHTBOSSELEMENT_H);
	mngr_->addEntity(sphere);
}

void AttackLightBossComponent::attack2()
{
	Entity* ray = new Entity();
	rayTrans_ = ray->addComponent<Transform>(TRANSFORM_H, Vector2D(0, bossTrans->getPos().getY() + bossTrans->getH() / 2), bossTrans->getPos().getX()+96, 128);
	ray->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at("Ray"), 256, 128, 8);
	ray->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(0, bossTrans->getH() / 4), bossTrans->getH() / 2, rayTrans_->getW());
	ray->addComponent<ColDetectorComponent>(COLDETECTORCOMPONENT_H, ray, player_);
	ray->addComponent<LightBossElement>(LIGHTBOSSELEMENT_H);
	mngr_->addEntity(ray);
}
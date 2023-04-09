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
	//set animacion a 2atk
	Entity* sphere= new Entity();
	//sphere->addComponent<Transform>(TRANSFORM_H);
	//sphere->addComponent<FramedImage>(FRAMEDIMAGE_H);
	//collider
	//movement
	mngr_->addEntity(sphere);
}

void AttackLightBossComponent::attack2()
{

}
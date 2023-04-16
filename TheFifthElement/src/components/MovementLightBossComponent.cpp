#include "MovementLightBossComponent.h"

MovementLightBossComponent::MovementLightBossComponent(Entity* player)
{
	player_ = player;
}
void MovementLightBossComponent::initComponent()
{
	playerTrans = player_->getComponent<Transform>(TRANSFORM_H);

	bossTrans = ent_->getComponent<Transform>(TRANSFORM_H);
	bossTrans->setVel(5.0);
	bossTrans->setDir(Vector2D(0, 0));
	movDir = Vector2D(0, 0);
}
void MovementLightBossComponent::update()
{
	/*int difX = playerTrans->getPos().getX() - bossTrans->getPos().getX();
	int difY = playerTrans->getPos().getY() - bossTrans->getPos().getY();*/
	move(movDir);
	//checkeo de posiciones solo en caso de fase X ademas esto lo debe tratar el collision
	/*if (( difX< closeX && difX> negCloseX) && (difY< closeY && difY> negCloseY))
	{
		if (bossTrans->getPos().getX() > 400)
		{
			bossTrans->setPos(newPosLeft);
		}
		else { cout << playerTrans->getPos(); bossTrans->setPos(newPosRight); }
	}*/
	//tengo que hacer comprobaciones sobre donde y cuando hace tp el enemigo y ajustar el collider vendra con el colliderComponent
}
void MovementLightBossComponent::teleport(Vector2D newPos)
{
	bossTrans->setPos(newPos);
}

void MovementLightBossComponent::move(Vector2D dir)
{
	movDir = dir;

	if ((bossTrans->getPos().getX() >= (playerTrans->getPos().getX() + 300)) || (bossTrans->getPos().getX() <= (playerTrans->getPos().getX() - 300)))
	{
		movDir.setX(0);
	}
	bossTrans->setPos(bossTrans->getPos() + movDir * bossTrans->getVel());
}
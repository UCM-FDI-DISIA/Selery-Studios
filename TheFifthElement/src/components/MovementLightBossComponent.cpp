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
	move(movDir);
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
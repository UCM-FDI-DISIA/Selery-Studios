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
	//bossTrans->setPos(bossTrans->getPos() + bossTrans->getDir() * bossTrans->getVel());
	//quiza no necesito la linea de encima ya que los movimientos no son continuos si no en determinados momentos
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
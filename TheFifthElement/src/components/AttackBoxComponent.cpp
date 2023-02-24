#include "AttackBoxComponent.h"
#include "../utils/Entity.h"



AttackBoxComponent::AttackBoxComponent()
{
	
	
}
void AttackBoxComponent::initComponent()
{
	playerTr = ent_->getComponent<Transform>(TRANSFORM_H);
	box = build_sdlrect(playerTr->getPos().getX() + (playerTr->getW()/2)/28, playerTr->getPos().getY() + playerTr->getH(), 10, 10);
}
void AttackBoxComponent::render()
{
	SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 255, 0, 0);							//	Renderizamos el rect?gulo del player
	SDL_RenderDrawRect(GameManager::instance()->getRenderer(), &box);
}

void AttackBoxComponent::update()
{
	box = build_sdlrect(playerTr->getPos().getX() + (playerTr->getW() / 2) / 28, playerTr->getPos().getY() + playerTr->getH()/1.5f , 10, 10);
}
#include "ColManager.h"


void ColManager::checkCollisionP(SDL_Rect boxAttack)
{
	for(auto it: mngr_->getEntities())
	{
		if (it->hasComponent(ENEMYBEUDIRECTIONCOMPONENT_H))
		{
			col_= it->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
			if(Collision::collides(Vector2D(boxAttack.x,boxAttack.y), boxAttack.w,boxAttack.h,Vector2D(col_->getColRect().x, col_->getColRect().y), col_->getColRect().w, col_->getColRect().h))
			{
				it->getComponent<LifeComponent>(LIFECOMPONENT_H)->Hit(1);
			}
		}
	}
}

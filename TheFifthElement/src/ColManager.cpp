#include "ColManager.h"


void ColManager::checkCollisionP(SDL_Rect boxAttack)
{
	for(auto it: mngr_->getEntities())
	{
		if (it->hasComponent(ENEMYBEUDIRECTIONCOMPONENT_H))
		{
			Transform* t = it->getComponent<Transform>(TRANSFORM_H);
			if(Collision::collides(Vector2D(boxAttack.x,boxAttack.y), boxAttack.w,boxAttack.h,t->getPos(),t->getW(),t->getH()))
			{
				it->Hit(1);
			}
		}
	}
}

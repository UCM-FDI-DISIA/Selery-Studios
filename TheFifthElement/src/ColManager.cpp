#include "ColManager.h"
#include "states/BeatEmUpState.h"

void ColManager::checkCollisionP(SDL_Rect boxAttack,string type)
{
	for(auto it: mngr_->getEntities())
	{
			if (it->hasComponent(ENEMYBEUDIRECTIONCOMPONENT_H))
			{
				ColliderComponent* col = it->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
				{

					if(Collision::collides(Vector2D(boxAttack.x, boxAttack.y), boxAttack.w, boxAttack.h, Vector2D(col->getColRect().x, col->getColRect().y), col->getColRect().w, col->getColRect().h))
					{
						string typeHitted = it->getComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H)->getType();


						if (type == typeHitted || typeHitted == "fire" && type == "earth" || typeHitted == "water" && type == "fire" || typeHitted == "earth" && type == "water")
						{
							if (type == "air") {
								it->getComponent<LifeComponent>(LIFECOMPONENT_H)->Hit(0.5 * props_->instance()->getStrength(0)); // aqui multiplicamos el valor base por el obtenido en la tienda
							}
							else if (type == "fire") {
								it->getComponent<LifeComponent>(LIFECOMPONENT_H)->Hit(0.5 * props_->instance()->getStrength(0));
							}
							else if (type == "water") {
								it->getComponent<LifeComponent>(LIFECOMPONENT_H)->Hit(0.5 * props_->instance()->getStrength(0));
							}
							else if (type == "earth") {
								it->getComponent<LifeComponent>(LIFECOMPONENT_H)->Hit(0.5 * props_->instance()->getStrength(0));
							}
						}

						else if (typeHitted == "fire" && type == "water" || typeHitted == "water" && type == "earth" || typeHitted == "earth" && type == "fire")
						{
							if (type == "air") {
								it->getComponent<LifeComponent>(LIFECOMPONENT_H)->Hit(2 * props_->instance()->getStrength(0));
							}
							else if (type == "fire") {
								it->getComponent<LifeComponent>(LIFECOMPONENT_H)->Hit(2 * props_->instance()->getStrength(0));
							}
							else if (type == "water") {
								it->getComponent<LifeComponent>(LIFECOMPONENT_H)->Hit(2 * props_->instance()->getStrength(0));
							}
							else if (type == "earth") {
								it->getComponent<LifeComponent>(LIFECOMPONENT_H)->Hit(2 * props_->instance()->getStrength(0));
							}
						}

						else it->getComponent<LifeComponent>(LIFECOMPONENT_H)->Hit(1 * props_->instance()->getStrength(0));
					}
				}
			}
			else if (it->hasComponent(LIFEEARTHBOSSCOMPONENT_H)) {
				ColliderComponent* col = it->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
				if (Collision::collides(Vector2D(boxAttack.x, boxAttack.y), boxAttack.w, boxAttack.h, Vector2D(col->getColRect().x, col->getColRect().y), col->getColRect().w, col->getColRect().h))
				{
					/*string typeHitted = it->getComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H)->getType();

					if (type == typeHitted || typeHitted == "fire" && type == "earth" || typeHitted == "water" && type == "fire" || typeHitted == "earth" && type == "water")
					{
						it->getComponent<LifeEarthBossComponent>(LIFEEARTHBOSSCOMPONENT_H)->receiveDamage(10, 0.5);
					}

					else if (typeHitted == "fire" && type == "water" || typeHitted == "water" && type == "earth" || typeHitted == "earth" && type == "fire")
					{
						it->getComponent<LifeEarthBossComponent>(LIFEEARTHBOSSCOMPONENT_H)->receiveDamage(10, 1.5);
					}

					else it->getComponent<LifeEarthBossComponent>(LIFEEARTHBOSSCOMPONENT_H)->receiveDamage(10, 1);*/
					it->getComponent<LifeEarthBossComponent>(LIFEEARTHBOSSCOMPONENT_H)->receiveDamage(10, 1);

				}
			}
			else if (it->hasComponent(WATERBOSSIA_H)) {
				ColliderComponent* col = it->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
				if (Collision::collides(Vector2D(boxAttack.x, boxAttack.y), boxAttack.w, boxAttack.h, Vector2D(col->getColRect().x, col->getColRect().y), col->getColRect().w, col->getColRect().h))
				if (type == "earth") {
					it->getComponent<WaterBossLife>(WATERBOSSLIFE_H)->damage(props_->instance()->getStrength(0), 2);
				}
				else if (type == "fire") {
					it->getComponent<WaterBossLife>(WATERBOSSLIFE_H)->damage(props_->instance()->getStrength(0), 0.5);
				}
				else {
					it->getComponent<WaterBossLife>(WATERBOSSLIFE_H)->damage(props_->instance()->getStrength(0), 1);
				}
			}
	}
}

void ColManager::checkCollisionE(SDL_Rect boxAttack, string type)
{
	Entity* player = static_cast<BeatEmUpState*>(mngr_)->getPlayer();
	ColliderComponent* col = player->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
	if (Collision::collides(Vector2D(boxAttack.x, boxAttack.y), boxAttack.w, boxAttack.h, Vector2D(col->getColRect().x - mngr_->camRect_.x, col->getColRect().y), col->getColRect().w, col->getColRect().h))
	{
		string typeHitted = player->getComponent<Image>(IMAGE_H)->getType();

		if (type == typeHitted || typeHitted == "fire" && type == "earth" || typeHitted == "water" && type == "fire" || typeHitted == "earth" && type == "water")
		{		
			player->getComponent<LifeComponent>(LIFECOMPONENT_H)->Hit(0.5);		
		}

		else if (typeHitted == "fire" && type == "water" || typeHitted == "water" && type == "earth" || typeHitted == "earth" && type == "fire")
		{
			player->getComponent<LifeComponent>(LIFECOMPONENT_H)->Hit(2);
		}

		else player->getComponent<LifeComponent>(LIFECOMPONENT_H)->Hit(1);
	}
}

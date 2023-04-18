#include "ColManager.h"
#include "states/BeatEmUpState.h"

void ColManager::checkCollisionP(SDL_Rect boxAttack,string type)
{
	for (auto it: mngr_->getEntities())
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
				if (!it->getComponent<MovementEarthBossComponent>(MOVEMENTEARTHBOSSCOMPONENT_H)->getBossProtected()) {
					if (type == "fire") {
						it->getComponent<LifeEarthBossComponent>(LIFEEARTHBOSSCOMPONENT_H)->receiveDamage(props_->instance()->getStrength(0), 2);
					}
					else if (type == "water") {
						it->getComponent<LifeEarthBossComponent>(LIFEEARTHBOSSCOMPONENT_H)->receiveDamage(props_->instance()->getStrength(0), 0.5);
					}
					else {
						it->getComponent<LifeEarthBossComponent>(LIFEEARTHBOSSCOMPONENT_H)->receiveDamage(props_->instance()->getStrength(0), 1);
					}
				}
				else
				{
					it->getComponent<AttackEarthBossComponent>(ATTACKEARTHBOSSCOMPONENT_H)->addExtraDamage();
				}
			}
		}
		else if (it->hasComponent(WATERBOSSIA_H)) {
			ColliderComponent* col = it->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
			if (Collision::collides(Vector2D(boxAttack.x, boxAttack.y), boxAttack.w, boxAttack.h, Vector2D(col->getColRect().x, col->getColRect().y), col->getColRect().w, col->getColRect().h)) {
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
		else if (it->hasComponent(LIFELIGHTBOSSCOMPONENT_H))
		{
			ColliderComponent* col = it->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
			if (Collision::collides(Vector2D(boxAttack.x, boxAttack.y), boxAttack.w, boxAttack.h, Vector2D(col->getColRect().x, col->getColRect().y), col->getColRect().w, col->getColRect().h))
			{
				it->getComponent<LifeLightBossComponent>(LIFELIGHTBOSSCOMPONENT_H)->damage(10);
			}
		}
		else if (it->hasComponent(FIREBOSSCOMPONENT_H)) {
			ColliderComponent* col = it->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
			if (Collision::collides(Vector2D(boxAttack.x, boxAttack.y), boxAttack.w, boxAttack.h, Vector2D(col->getColRect().x, col->getColRect().y), col->getColRect().w, col->getColRect().h))
			{
				it->getComponent<FireBossComponent>(FIREBOSSCOMPONENT_H)->subLife(10);
			}
		}
		else if (it->hasComponent(LIFEBASICCOMPONENT_H)) {
			ColliderComponent* col = it->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
			if (Collision::collides(Vector2D(boxAttack.x, boxAttack.y), boxAttack.w, boxAttack.h, Vector2D(col->getColRect().x, col->getColRect().y), col->getColRect().w, col->getColRect().h))
			{
				it->getComponent<LifeBasicComponent>(LIFEBASICCOMPONENT_H)->lesslife(1);
			}
		}
	}
}

void ColManager::checkCollisionE(SDL_Rect boxAttack, string type, int extraDamage)
{
	Entity* player = static_cast<BeatEmUpState*>(mngr_)->getPlayer();
	ColliderComponent* col = player->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
	if (Collision::collides(Vector2D(boxAttack.x, boxAttack.y), boxAttack.w, boxAttack.h, Vector2D(col->getColRect().x - mngr_->camRect_.x, col->getColRect().y), col->getColRect().w, col->getColRect().h))
	{
		string typeHitted = player->getComponent<FramedImage>(FRAMEDIMAGE_H)->getType();

		if (type == typeHitted || typeHitted == "fire" && type == "earth" || typeHitted == "water" && type == "fire" || typeHitted == "earth" && type == "water")
		{		
			player->getComponent<LifeComponent>(LIFECOMPONENT_H)->Hit(0.5 + extraDamage);
		}

		else if (typeHitted == "fire" && type == "water" || typeHitted == "water" && type == "earth" || typeHitted == "earth" && type == "fire")
		{
			player->getComponent<LifeComponent>(LIFECOMPONENT_H)->Hit(2 + extraDamage);
		}

		else player->getComponent<LifeComponent>(LIFECOMPONENT_H)->Hit(1 + extraDamage);
	}
}

void ColManager::update()
{

	if (howManyNear() > 0)
	{
		for (auto it : mngr_->getEntities())
		{
			ColliderComponent* col = it->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
			if (it->hasComponent(ENEMYBEUDIRECTIONCOMPONENT_H) && !col->getCollisionWithPlayer())
			{
				Transform* tr = it->getComponent<Transform>(TRANSFORM_H);
				//poner idle
				tr->setVel(0);
			}
		}
	}
	else
	{
		for (auto it : mngr_->getEntities())
		{
			if (it->hasComponent(ENEMYBEUDIRECTIONCOMPONENT_H))
			{
				Transform* tr = it->getComponent<Transform>(TRANSFORM_H);
				if (tr->getVel() == 0)
				{
					//move
					tr->setVel(3);
				}

			}
		}
	}

}

int ColManager::howManyNear()
{
	enemiesNearPlayer = 0;
	int i = 0;
	for (auto it : mngr_->getEntities())
	{
		if (it->hasComponent(ENEMYBEUDIRECTIONCOMPONENT_H))
		{
			ColliderComponent* col = it->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
			Entity* player = static_cast<BeatEmUpState*>(mngr_)->getPlayer();
			Transform* tr = player->getComponent<Transform>(TRANSFORM_H);
			if (Collision::collides(Vector2D(tr->getPos().getX(), tr->getPos().getY()), tr->getW(), tr->getH(), Vector2D(col->getColRect().x, col->getColRect().y), col->getColRect().w, col->getColRect().h))
			{
				enemiesNearPlayer++;
				col->setCollisionWithPlayer(true);
			}
			else
			{
				col->setCollisionWithPlayer(false);
			}
		}
	}
	return enemiesNearPlayer;
}

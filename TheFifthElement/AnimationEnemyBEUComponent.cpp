#include "AnimationEnemyBEUComponent.h"
#include "src/Entities/EnemyBEU.h"

void AnimationEnemyBEUComponent::update() {

	if (currentState_ != nextState_) updateAnimation();
	else updateAn();
}

void AnimationEnemyBEUComponent::changeState(AnimationStates newState) 
{
	nextState_ = newState;// as� se evita que se a�ada el mismo estado m�s de una vez
}

void AnimationEnemyBEUComponent::updateAn() {
	//SUGERENCIA DEJAR AL ENEMIGO QUIETO MIENTRAS PEGA
}

void AnimationEnemyBEUComponent::updateAnimation() {

	currentState_ = nextState_;

	switch (currentState_)
	{
	case AnimationEnemyBEUComponent::Moving:
		setMovTexture();
		static_cast<EnemyBEU*>(ent_)->setColAnim(EnemyWidth_, EnemyHeight_, nframes_, offset_, ColWidth_, ColHeight_, t_, false);
		break;
	case AnimationEnemyBEUComponent::Attack:
		setAttackTexture();
		static_cast<EnemyBEU*>(ent_)->setColAnim(EnemyWidth_, EnemyHeight_, nframes_, offset_, ColWidth_, ColHeight_, t_, true);
		//SUGERENCIA DEJAR AL ENEMIGO QUIETO
		break;
	case AnimationEnemyBEUComponent::Hit:
		setHitTexture();
		static_cast<EnemyBEU*>(ent_)->setColAnim(EnemyWidth_, EnemyHeight_, nframes_, offset_, ColWidth_, ColHeight_, t_, true);
		break;
	case AnimationEnemyBEUComponent::Death:
		setDeathTexture();
		static_cast<EnemyBEU*>(ent_)->setColAnim(EnemyWidth_, EnemyHeight_, nframes_, offset_, ColWidth_, ColHeight_, t_, true);
		break;
	default:
		break;
	}
}

	void AnimationEnemyBEUComponent::setMovTexture() {
		if (enemy_ == "shroom") {

			nframes_ = 8;
			EnemyWidth_ = 1200;
			EnemyHeight_ = 150;

			offset_ = Vector2D(55, 55);
			ColHeight_ = EnemyHeight_ / 3;
			ColWidth_ = EnemyWidth_ / 25;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Mushroom_run");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Mushroom_run");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Mushroom_run");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Mushroom_run");
			}
		}

		else if (enemy_ == "skeleton") {

			nframes_ = 4;
			EnemyWidth_ = 600;
			EnemyHeight_ = 150;

			offset_ = Vector2D(55, 40);
			ColHeight_ = EnemyHeight_ / 2;
			ColWidth_ = EnemyWidth_ / 15;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Skeleton_run");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Skeleton_run");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Skeleton_run");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Skeleton_run");
			}
		}

		else if (enemy_ == "goblin") {

			nframes_ = 8;
			EnemyWidth_ = 1200;
			EnemyHeight_ = 150;

			offset_ = Vector2D(55, 55);
			ColHeight_ = EnemyHeight_ / 3;
			ColWidth_ = EnemyWidth_ / 25;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Goblin_run");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Goblin_run");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Goblin_run");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Goblin_run");
			}
		}

		else if (enemy_ == "bat") {

			nframes_ = 8;
			EnemyWidth_ = 1200;
			EnemyHeight_ = 150;

			offset_ = Vector2D(55, 50);
			ColHeight_ = EnemyHeight_ / 3;
			ColWidth_ = EnemyWidth_ / 25;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Bat_fly");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Bat_fly");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Bat_fly");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Bat_fly");
			}
		}
	}

	void AnimationEnemyBEUComponent::setAttackTexture() {
		if (enemy_ == "shroom") {

			nframes_ = 8;
			EnemyWidth_ = 1200;
			EnemyHeight_ = 150;

			offset_ = Vector2D(55, 55);
			ColHeight_ = EnemyHeight_ / 3;
			ColWidth_ = EnemyWidth_ / 25;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Mushroom_attack");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Mushroom_attack");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Mushroom_attack");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Mushroom_attack");
			}
		}

		else if (enemy_ == "skeleton") {

			nframes_ = 8;
			EnemyWidth_ = 1200;
			EnemyHeight_ = 150;

			offset_ = Vector2D(45, 42);
			ColHeight_ = 2.5 * EnemyHeight_ / 6;
			ColWidth_ = EnemyWidth_ / 25;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Skeleton_attack");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Skeleton_attack");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Skeleton_attack");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Skeleton_attack");
			}
		}

		else if (enemy_ == "goblin") {

			nframes_ = 8;
			EnemyWidth_ = 1200;
			EnemyHeight_ = 150;

			offset_ = Vector2D(55, 67);
			ColHeight_ = EnemyHeight_ / 4;
			ColWidth_ = EnemyWidth_ / 25;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Goblin_attack");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Goblin_attack");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Goblin_attack");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Goblin_attack");
			}
		}

		else if (enemy_ == "bat") {

			nframes_ = 8;
			EnemyWidth_ = 1200;
			EnemyHeight_ = 150;

			offset_ = Vector2D(55, 50);
			ColHeight_ = EnemyHeight_ / 5;
			ColWidth_ = EnemyWidth_ / 30;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Bat_attack");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Bat_attack");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Bat_attack");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Bat_attack");
			}
		}
	}

	void AnimationEnemyBEUComponent::setHitTexture()
	{
		if (enemy_ == "shroom") {

			nframes_ = 4;
			EnemyWidth_ = 600;
			EnemyHeight_ = 150;

			offset_ = Vector2D(60, 55);
			ColHeight_ = EnemyHeight_ / 3;
			ColWidth_ = EnemyWidth_ / 25;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Mushroom_hit");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Mushroom_hit");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Mushroom_hit");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Mushroom_hit");
			}
		}

		else if (enemy_ == "skeleton") {

			nframes_ = 4;
			EnemyWidth_ = 600;
			EnemyHeight_ = 150;

			offset_ = Vector2D(55, 45);
			ColHeight_ = 2 * EnemyHeight_ / 5;
			ColWidth_ = EnemyWidth_ / 15;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Skeleton_hit");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Skeleton_hit");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Skeleton_hit");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Skeleton_hit");
			}
		}

		else if (enemy_ == "goblin") {

			nframes_ = 4;
			EnemyWidth_ = 600;
			EnemyHeight_ = 150;

			offset_ = Vector2D(55, 55);
			ColHeight_ = EnemyHeight_ / 3;
			ColWidth_ = EnemyWidth_ / 15;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Goblin_hit");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Goblin_hit");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Goblin_hit");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Goblin_hit");
			}
		}

		else if (enemy_ == "bat") {

			nframes_ = 4;
			EnemyWidth_ = 545;
			EnemyHeight_ = 126;

			offset_ = Vector2D(45, 35);
			ColHeight_ = EnemyHeight_ / 4;
			ColWidth_ = EnemyWidth_ / 12;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Bat_hit");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Bat_hit");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Bat_hit");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Bat_hit");
			}
		}
	}

	void AnimationEnemyBEUComponent::setDeathTexture()
	{
		if (enemy_ == "shroom") {

			nframes_ = 4;
			EnemyWidth_ = 600;
			EnemyHeight_ = 150;

			offset_ = Vector2D(60, 55);
			ColHeight_ = EnemyHeight_ / 3;
			ColWidth_ = EnemyWidth_ / 25;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Mushroom_death");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Mushroom_death");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Mushroom_death");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Mushroom_death");
			}
		}

		else if (enemy_ == "skeleton") {

			nframes_ = 4;
			EnemyWidth_ = 600;
			EnemyHeight_ = 150;

			offset_ = Vector2D(55, 70);
			ColHeight_ = EnemyHeight_ / 4;
			ColWidth_ = EnemyWidth_ / 15;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Skeleton_death");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Skeleton_death");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Skeleton_death");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Skeleton_death");
			}
		}

		else if (enemy_ == "goblin") {

			nframes_ = 4;
			EnemyWidth_ = 600;
			EnemyHeight_ = 150;

			offset_ = Vector2D(40, 75);
			ColHeight_ = EnemyHeight_ / 5;
			ColWidth_ = EnemyWidth_ / 12;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Goblin_death");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Goblin_death");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Goblin_death");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Goblin_death");
			}
		}

		else if (enemy_ == "bat") {

			nframes_ = 4;
			EnemyWidth_ = 600;
			EnemyHeight_ = 150;

			offset_ = Vector2D(50, 75);
			ColHeight_ = EnemyHeight_ / 6;
			ColWidth_ = EnemyWidth_ / 12;

			if (type_ == "fire") {
				t_ = &SDLUtils::instance()->images().at("BEU_fire_Bat_death");
			}

			else if (type_ == "wind") {
				t_ = &SDLUtils::instance()->images().at("BEU_wind_Bat_death");
			}

			else if (type_ == "water") {
				t_ = &SDLUtils::instance()->images().at("BEU_water_Bat_death");
			}

			else if (type_ == "earth") {
				t_ = &SDLUtils::instance()->images().at("BEU_earth_Bat_death");
			}
		}
	}

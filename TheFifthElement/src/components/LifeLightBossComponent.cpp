#include "LifeLightBossComponent.h"

LifeLightBossComponent::LifeLightBossComponent()
{
	life = maxLife;
}

void LifeLightBossComponent::initComponent()
{
	scale = WIN_WIDTH / 900;
	im_ = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	backTexture_ = &SDLUtils::instance()->images().at("Light_LifeBarBack");
	barTexture_ = &SDLUtils::instance()->images().at("Light_LifeBar");
	borderTexture_ = &SDLUtils::instance()->images().at("Light_LifeBarBorder");
	barWidth_ = backWidth_ = borderWidth_ = 300*scale;
	barHeight_ = backHeight_ = borderHeight_ = 50*scale;
	atk_ = ent_->getComponent<AttackLightBossComponent>(ATTACKLIGHTBOSSCOMPONENT_H);
	animBoss_ = ent_->getComponent<AnimationLightBossComponent>(ANIMATIONLIGHTBOSSCOMPONENT_H);
}

void LifeLightBossComponent::damage(float dam)
{
	life -= dam;
	if (life <= 0)
	{
		animBoss_->setDeath();
		//animBoss_->newAnim(AnimationLightBossComponent::Die);
		//static_cast<BeatEmUpState*>(mngr_)->finishBEU();
		//ent_->~Entity(); //esto esta añadido ya que en 1 solo ataque se producen multiples daños y se llamaba a esta funcion demasiadas veces
	}
	else
	{
		if (!atk_->isAtkn())
		{
			checkState();
			animBoss_->newAnim(AnimationLightBossComponent::Hit);
		}
		
	}
}

void LifeLightBossComponent::checkState()
{
	//if (life > ((maxLife * 3) / 4))	{ cout << "fase1"; } la fase 1 no hace falta comprobarla ya que comienza siempre en esta fase

	if ((life <= ((maxLife * 3) / 4)) && (life > ((maxLife * 2) / 5)))
	{
		if (fightState != 2)
		{
			fightState = 2;
			atk_->setState(fightState);
		}
	}
	else if ((life <= ((maxLife * 2) / 5)) && (life > (maxLife / 5)))
	{
		if (fightState != 3)
		{
			fightState = 3;
			atk_->setState(fightState);
		}
	}
	else if ((life <= (maxLife / 5)) && (life > 0))
	{
		if (fightState != 4)
		{
			fightState = 4;
			atk_->setState(fightState);
		}
	}
}

void LifeLightBossComponent::render()
{
	barWidth_ = (life * backWidth_) / maxLife;

	SDL_Rect src = { 0, 0, 400, 50 };

	SDL_Rect dest;
	dest.x = 8 * (WIN_WIDTH / 13);
	dest.y = 35* (WIN_WIDTH/ 900);

	dest.h = backHeight_;
	dest.w = backWidth_;
	backTexture_->render(src, dest);

	dest.h = barHeight_;
	dest.w = barWidth_;
	barTexture_->render(src, dest);

	dest.h = borderHeight_;
	dest.w = borderWidth_;
	borderTexture_->render(src, dest);
}
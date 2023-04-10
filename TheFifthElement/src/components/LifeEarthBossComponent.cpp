#include "LifeEarthBossComponent.h"
LifeEarthBossComponent::LifeEarthBossComponent() {
	maxLife = 3000;
	life = maxLife;
}

void LifeEarthBossComponent::initComponent() {
	scale = WIN_WIDTH / 900;
	animEarthBoss = ent_->getComponent<AnimationEarthBossComponent>(ANIMATIONEARTHBOSSCOMPONENT_H);
	bossTransform = ent_->getComponent<Transform>(TRANSFORM_H);
	bossImage = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);

	backTexture_ = &SDLUtils::instance()->images().at("Earth_LifeBarBack");
	barTexture_ = &SDLUtils::instance()->images().at("Earth_LifeBar");
	borderTexture_ = &SDLUtils::instance()->images().at("Earth_LifeBarBorder");
	barWidth_ = backWidth_ = borderWidth_ = 300 * scale;
	barHeight_ = backHeight_ = borderHeight_ = 50 * scale;
}
void LifeEarthBossComponent::receiveDamage(float damage, float mul) {
	life -= damage * mul;
	barWidth_ = ((life * backWidth_) / maxLife);
	animEarthBoss->newAnimation(AnimationEarthBossComponent::Hit);
	if (life <= maxLife / 1.5 && stage == 1) {
		stageTwo();
		animEarthBoss->newAnimation(AnimationEarthBossComponent::Death);
	}
	else if (life <= 0) {
		ent_->setAlive(false);
	}
}

void LifeEarthBossComponent::stageTwo() {
	stage++;
	animEarthBoss->newStage();
	
	Entity* stone = new Entity();
	Vector2D pos = bossTransform->getPos();
	bossTransform->setPos(Vector2D(WIN_WIDTH, 200));
	stone->setContext(mngr_);
	stone->addComponent<Transform>(TRANSFORM_H, pos, EARTHBOSS_WIDTH * 2, EARTHBOSS_HEIGHT * 2);
	stone->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("stone6"));
	stone->addComponent<ObjectsComponent>(OBJECTSCOMPONENT_H);
	stone->addComponent<StoneComponent>(STONECOMPONENT_H);
	mngr_->addEntity(stone);
}

void LifeEarthBossComponent::render() {
	SDL_Rect src = { 0, 0, 400, 50 };

	SDL_Rect dest;
	dest.x = 8 * (WIN_WIDTH / 13);
	dest.y = 35 * scale;
	dest.h = backHeight_;
	dest.w = backWidth_;
	backTexture_->render(src, dest);

	dest.x = 8 * (WIN_WIDTH / 13);
	dest.h = barHeight_;
	dest.w = barWidth_;
	barTexture_->render(src, dest);

	dest.x = 8 * (WIN_WIDTH / 13);
	dest.h = borderHeight_;
	dest.w = borderWidth_;
	borderTexture_->render(src, dest);
}
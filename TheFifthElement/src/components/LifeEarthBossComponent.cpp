#include "LifeEarthBossComponent.h"
LifeEarthBossComponent::LifeEarthBossComponent() {
	maxLife = 3000;
	life = maxLife;
}

void LifeEarthBossComponent::initComponent() {
	animEarthBoss = ent_->getComponent<AnimationEarthBossComponent>(ANIMATIONEARTHBOSSCOMPONENT_H);
	bossTransform = ent_->getComponent<Transform>(TRANSFORM_H);
	bossImage = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
}
void LifeEarthBossComponent::receiveDamage(float damage, float mul) {
	life -= damage * mul;
	animEarthBoss->newAnimation(AnimationEarthBossComponent::Hit);
	if (life <= maxLife / 1.5 && stage == 1) {
		stageTwo();
		//animEarthBoss->newAnimation(AnimationEarthBossComponent::Death);
		cout << "Stage 2";
	}
	else if (life <= 0) {
		ent_->setAlive(false);
	}
}

void LifeEarthBossComponent::stageTwo() {
	stage++;
	bossTransform->setPos(Vector2D(-100, 200));
	bossImage->setAnim("GolemFase2", 58, false);
	////bossImage->setAnimTexture("GolemFase2", 58, EARTHBOSS_WIDTH * 2);
	Entity* stone = new Entity();
	//Vector2D pos = { SDLUtils::instance()->rand().nextInt(0, WIN_WIDTH) , WIN_HEIGHT - 100 };
	Vector2D pos = { 300 , WIN_HEIGHT - 400 };
	stone->setContext(mngr_);
	stone->addComponent<Transform>(TRANSFORM_H, pos, EARTHBOSS_WIDTH * 2, EARTHBOSS_HEIGHT * 2);
	stone->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("stone"));
	stone->addComponent<ObjectsComponent>(OBJECTSCOMPONENT_H);
	mngr_->addEntity(stone);
}
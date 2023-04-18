#include "LifeEarthBossComponent.h"
#include "../states/BeatEmUpState.h"
LifeEarthBossComponent::LifeEarthBossComponent() {
	maxLife = 50;
	life = maxLife;
}

void LifeEarthBossComponent::initComponent() {
	scale = WIN_WIDTH / 900;
	animEarthBoss = ent_->getComponent<AnimationEarthBossComponent>(ANIMATIONEARTHBOSSCOMPONENT_H);
	bossTransform = ent_->getComponent<Transform>(TRANSFORM_H);
	bossImage = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
	bossCol = ent_->getComponent<ColliderComponent>(COLLIDERCOMPONENT_H);
	bossMovement = ent_->getComponent<MovementEarthBossComponent>(MOVEMENTEARTHBOSSCOMPONENT_H);
	bossAttackComp = ent_->getComponent<AttackEarthBossComponent>(ATTACKEARTHBOSSCOMPONENT_H);

	backTexture_ = &SDLUtils::instance()->images().at("Earth_LifeBarBack");
	barTexture_ = &SDLUtils::instance()->images().at("Earth_LifeBar");
	borderTexture_ = &SDLUtils::instance()->images().at("Earth_LifeBarBorder");
	barWidth_ = backWidth_ = borderWidth_ = 300 * scale;
	barHeight_ = backHeight_ = borderHeight_ = 50 * scale;
}

void LifeEarthBossComponent::update() {
	unsigned timer = clock();
	timeExecution = (double(timer) / CLOCKS_PER_SEC);
	if (stage == 3) {
		if (!slow) {
			float vel = bossMovement->getVelocity();
			float increment = ((float)life / (float)maxLife) / 20.0f;
			if (vel + increment < 5) {
				bossMovement->setVelocity(vel + increment);
			}
			
		}
		else if (slowTime + 2 < timeExecution)
		{
			slow = false;
		}
	}
	if (die_ && !bossImage->isAnimPlaying()) {
		ent_->setAlive(false);
		static_cast<BeatEmUpState*>(mngr_)->finishBEU();
	}
	else if (hit_ && cont >= hitTime) hit_ = false;
	cont++;
}
void LifeEarthBossComponent::receiveDamage(float damage, float mul) {
	if (!die_ && !hit_) {
		life -= damage * mul;
		barWidth_ = ((life * backWidth_) / maxLife);

		if (stage == 3) {
			slow = true;
			bossMovement->setVelocity(1.75);
			unsigned timer = clock();
			slowTime = (double(timer) / CLOCKS_PER_SEC);
		}
		animEarthBoss->newAnimation(AnimationEarthBossComponent::Hit);
		if (life <= maxLife / 1.5 && stage == 1) {
			animEarthBoss->newAnimation(AnimationEarthBossComponent::Death);
			stageTwo();
		}
		else if (life <= maxLife / 3 && stage == 2) {
			animEarthBoss->newAnimation(AnimationEarthBossComponent::Death);
			stageThree();
		}
		else if (life <= 0) {
			animEarthBoss->newAnimation(AnimationEarthBossComponent::Death);
			die_ = true;
		}
		hit_ = true;
		cont = 0;
	}
}

void LifeEarthBossComponent::stageTwo() {
	stage++;
	animEarthBoss->newStage();
	ent_->addComponent<ProtectionEarthBossComponent>(PROTECTIONEARTHBOSSCOMPONENT_H);
	Entity* stone = new Entity();
	Vector2D pos = bossTransform->getPos();
	Vector2D posPlayer = static_cast<BeatEmUpState*>(mngr_)->getPlayer()->getComponent<Transform>(TRANSFORM_H)->getPos();
	bossTransform->setPos(posPlayer + Vector2D(WIN_WIDTH, 0));
	stone->setContext(mngr_);
	stone->addComponent<Transform>(TRANSFORM_H, pos, EARTHBOSS_WIDTH * 2, EARTHBOSS_HEIGHT * 2);
	stone->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("v1stone6"));
	stone->addComponent<ObjectsComponent>(OBJECTSCOMPONENT_H);
	stone->addComponent<StoneComponent>(STONECOMPONENT_H, 1);
	mngr_->addEntityAtI(stone, 2);
}

void LifeEarthBossComponent::stageThree() {
	stage++;
	static_cast<BeatEmUpState*>(mngr_)->getPlayer()->getComponent<InputComponentBEU>(INPUTCOMPONENTBEU_H)->setEarthStage3(true);
	animEarthBoss->newStage();
	Entity* stone = new Entity();
	Vector2D pos = bossTransform->getPos();
	Vector2D posPlayer = static_cast<BeatEmUpState*>(mngr_)->getPlayer()->getComponent<Transform>(TRANSFORM_H)->getPos();
	bossTransform->setPos(posPlayer + Vector2D(WIN_WIDTH, 0));
	stone->setContext(mngr_);
	stone->addComponent<Transform>(TRANSFORM_H, pos, EARTHBOSS_WIDTH * 2, EARTHBOSS_HEIGHT * 2);
	stone->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("v2stone6"));
	stone->addComponent<ObjectsComponent>(OBJECTSCOMPONENT_H);
	stone->addComponent<StoneComponent>(STONECOMPONENT_H, 2);
	mngr_->addEntityAtI(stone, 2);

	ent_->removeComponent(PROTECTIONEARTHBOSSCOMPONENT_H);
	bossImage->setAnim("Moose_idle", 8, false);
	bossImage->setWidthFrame(MOOSE_WIDTH);
	bossTransform->setW(MOOSE_WIDTH * 2);
	bossCol->setCollider(Vector2D(330, 120), (MOOSE_HEIGHT * 2) - 240, 100);
	bossMovement->setMarginToAttack(65);
	bossAttackComp->setExtraDamage(0);
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
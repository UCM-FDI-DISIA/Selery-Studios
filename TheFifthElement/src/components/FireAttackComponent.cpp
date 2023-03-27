#include "FireAttackComponent.h"
#include "../states/BeatEmUpState.h"

FireAttackComponent::FireAttackComponent(BeatEmUpState* STATE) { 
	timeToSpawn = sdlutils().currRealTime(); 
	state = STATE; 
}

FireAttackComponent::~FireAttackComponent() {
}

void FireAttackComponent::initComponent() {
}

void FireAttackComponent::update() {
	if (timeToSpawn <= sdlutils().currRealTime() && ih().isKeyDown(SDL_SCANCODE_K)) {
		timeToSpawn += sdlutils().currRealTime() + delay;
		spawnEnemies(3);
	}
}

void FireAttackComponent::spawnEnemies(int n) {
	for (int i = 0; i < n; i++) {
		int character = rand() % 4;
		Vector2D pos = { (float)sdlutils().rand().nextInt(50,WIN_WIDTH - 80), (float)sdlutils().rand().nextInt(50,WIN_HEIGHT - 50) };
		Entity* player_ = state->getPlayer();

		Entity* enemy = ent_->getContext()->addEntity();
		enemy->addComponent<Transform>(TRANSFORM_H, pos, ENEMYBEU_WIDTH, ENEMYBEU_HEIGHT, 1)->setDir(Vector2D(1, 0));
		AnimationEnemyBEUComponent* anim = enemy->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, "fire", enemyTypes[rand()%4], player_);
		anim->changeState(AnimationEnemyBEUComponent::Moving);
		anim->updateAnimation();
		enemy->addComponent<FramedImage>(FRAMEDIMAGE_H, anim->getTexture(), ENEMYBEU_WIDTH, ENEMYBEU_HEIGHT, anim->getNFrames(), "fire");
		enemy->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
		enemy->addComponent<EnemyBEUDirectionComponent>(ENEMYBEUDIRECTIONCOMPONENT_H, player_, anim->getEnemy());
		enemy->addComponent<LifeComponent>(LIFECOMPONENT_H, ENEMYBEU_MAXLIFE);
		enemy->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, anim->getOffset(), anim->getColHeight(), anim->getColWidth());
		enemy->addComponent<ColDetectorComponent>(COLDETECTORCOMPONENT_H, enemy, player_);
		enemy->addComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);
	}
}
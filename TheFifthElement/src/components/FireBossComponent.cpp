#include "FireBossComponent.h"
#include "../states/BeatEmUpState.h"
#include "../utils/Entity.h"
#include <cmath>
#include <math.h>

FireBossComponent::FireBossComponent(Entity* player) {
	this->player = player;
}

FireBossComponent::~FireBossComponent() {

}

void FireBossComponent::initComponent() {
	my_transform = ent_->getComponent<Transform>(TRANSFORM_H);
	assert(my_transform != nullptr);
	initial_posotion= ent_->getComponent<Transform>(TRANSFORM_H)->getPos();
	trans_player = player->getComponent<Transform>(TRANSFORM_H);
	assert(trans_player != nullptr);
	player_pos = trans_player->getPos();
	image = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
	assert(image != nullptr);
	image->setAnim("FireBoss", 12, false, 1);
	
	//diferencia de posicion entre player y BOSS
	velocity_x =(((player_pos.getX() * trans_player->getS() - initial_posotion.getX() * trans_player->getS())/WIN_WIDTH))*2;
	velocity_y = (((player_pos.getY() * trans_player->getS() -( initial_posotion.getY() * trans_player->getS() -PLAYERTD_HEIGHT_FRAME)) / WIN_HEIGHT))*2;

	barWidth_ = backWidth_ = borderWidth_ = 300 * scale;
	barHeight_ = backHeight_ = borderHeight_ = 50 * scale;
	death->play();
 }


void FireBossComponent::changeDir() {

	if (my_transform->getPos().getX() > trans_player->getPos().getX()) {
		velocity_x = trans_player->getPos().getX()*trans_player->getS() - my_transform->getPos().getX()*my_transform->getS();
		velocity_x = (velocity_x / WIN_WIDTH)*2;
		image->setFlip(SDL_FLIP_NONE);
		
	}
	else {
		velocity_x = my_transform->getPos().getX() * trans_player->getS() -trans_player->getPos().getX() * trans_player->getS();
		velocity_x = (velocity_x / WIN_WIDTH)*-2;
		image->setFlip(SDL_FLIP_HORIZONTAL);

	}
	if (my_transform->getPos().getY() < trans_player->getPos().getY()) {

		velocity_y = trans_player->getPos().getY() * my_transform->getS() - my_transform->getPos().getY()*trans_player->getS();
		velocity_y = velocity_y / WIN_HEIGHT;
	}
	else {
		
			velocity_y =  my_transform->getPos().getY()* my_transform->getS() -trans_player->getPos().getY() *trans_player->getS();
			velocity_y = velocity_y / WIN_HEIGHT;
		
	}

	if (velocity_x < -0.1)velocity_x = -0.95;
	if (velocity_x > 0.1)velocity_x = 0.95;

}
void FireBossComponent::update() {
	Vector2D new_pos = my_transform->getPos();
	


	int upper_limit = WIN_HEIGHT/4; // Nuevo límite superior
	int lower_limit = WIN_HEIGHT/2; // Nuevo límite inferior

	if (new_pos.getY() < upper_limit || new_pos.getY() > lower_limit) velocity_y = 0;
	
	//Así estaba antes:
	//if (new_pos.getY() < 330 || new_pos.getY() > WIN_HEIGHT - FIREBOSS_HEIGHT / 2) velocity_y = 0;

	Vector2D v{ velocity_x,velocity_y };
	my_transform->setPos(my_transform->getPos() + v);
	 cout << (abs(my_transform->getPos().getX() * my_transform->getS() - trans_player->getPos().getX() * trans_player->getS())) << endl;
	//my_transform->setPos(new_pos);
	switch (current) {
	case moving_towards_player:
			changeDir();
		image->setAnim("FireBoss", 12, false, 1);
		//Si has llegado a la posicion  cogida anteriormente por el player vuelve pa atras
		if (abs(my_transform->getPos().getX()*my_transform->getS() - trans_player->getPos().getX() *trans_player->getS())<50 ) {
			image->setAnim("FireBoss", 12, false, 1);
			image->setFlip(SDL_FLIP_HORIZONTAL);
			changeDir();
			//current = moving_towards_initialpoint;
		
			current = attack;//ATACAMOS
		}
		break;

	case moving_towards_initialpoint:
		////si has llegado a la posicion base vuelve pa el player
		//if (my_transform->getPos().getX()*my_transform->getS() >initial_posotion.getX()*my_transform->getS()) {
		//	image->setAnim("FireBoss", 12, false, 1);
		//	image->setFlip(SDL_FLIP_NONE);
		//	player_pos = trans_player->getPos();
		//	velocity_x = (((player_pos.getX() * my_transform->getS() - initial_posotion.getX() * trans_player->getS()) / WIN_WIDTH)) *2;
		//	velocity_y = (((player_pos.getY() * my_transform->getS() - initial_posotion.getY() * trans_player->getS()) / WIN_HEIGHT))*2 ;
		//	current = moving_towards_player;
		//}
		//break;

	case paused: 
		//Movimiento
		if (my_transform->getPos().getX() > sdlutils().width()) { 
			velocity_x = 0; 
		}
		else { 
			velocity_x = 4; 
			image->setAnim("FireBoss", 12, false, 1);
			image->setFlip(SDL_FLIP_HORIZONTAL);
		}

		//Vuelta del Boss a la batalla
		for (int i = 0; i < nEnemies; i++) {
			if (enemyRef[i] == nullptr || enemyRef[i]->getLife() > 0) {
				if (current_life < maxLife_) {
					current_life += 2;
					int save = barWidth_;
					barWidth_ = ((current_life * backWidth_) / maxLife_);
				}
				return;
			}
		}
		// Si hay algun enemigo vivo se acaba el update
		// Si no, se cambia de estado y vuelve a pelear
		velocity_x = -1;
		changeDir();
		current = moving_towards_player; 
		image->setFlip(SDL_FLIP_NONE);
		break;

	case recovery:
		for (int i = 0; i < fire_colums.size(); ++i) {
			
			LifeBasicComponent* life = fire_colums[i]->getComponent<LifeBasicComponent>(LIFEBASICCOMPONENT_H);
			if (life->getlife() > 0) {
				if (current_life < maxLife_) {
					current_life += 2;
					int save = barWidth_;
					barWidth_ = ((current_life * backWidth_) / maxLife_);
					
				}
				return;
				
			}

		}
		my_transform->setPos(initial_posotion);
		image->setAnim("FireBoss", 12, false, 1);
		image->setFlip(SDL_FLIP_NONE);
		player_pos = trans_player->getPos();
		changeDir();
		current = moving_towards_player;
		end = false;
		
		break;

	case attack: 
		
		cont++;
		if (cont > 20) {
			cont = 0;
		
				if (trans_player->getPos().getX() < my_transform->getPos().getX()) {
					image->setFlip(SDL_FLIP_NONE);
					image->setAnim("FireBoss", 15, false, 2);
				}
				else {
					image->setFlip(SDL_FLIP_HORIZONTAL);
					image->setAnim("FireBoss", 15, false, 2);
				}
				anim = image->isAnimPlaying();
				cout << anim;
		
			velocity_x = 0;
			velocity_y = 0;

			if (image->getCol()>12) {//acaba el ataque
				hit->play();
				image->setAnim("FireBoss", 12, false, 1);
				image->setFlip(SDL_FLIP_HORIZONTAL);
				player_pos = trans_player->getPos();
				changeDir();
				current = moving_towards_player;
			}
		}
		
		break;
	}

	//if (my_transform->getDir().getX() > 0) {
	//	image->setFlip(SDL_FLIP_NONE);
	//
	//}
	//else {
	//	image->setFlip(SDL_FLIP_HORIZONTAL);
	//}
 }

void FireBossComponent::summonEnemies(int n) { // Crea 4 enemigos de fuego aleatorios entre los 4 "tipos" posibles
	for (int i = 0; i < n; i++) {
		int character = rand() % 4;
		Vector2D pos = { (float)sdlutils().rand().nextInt(WIN_WIDTH * 0.75, WIN_WIDTH - 80), (float)sdlutils().rand().nextInt(150,WIN_HEIGHT * 0.75) };
		
		Entity* enemy = mngr_->addEntity();
		enemy->addComponent<Transform>(TRANSFORM_H, pos, ENEMYBEU_WIDTH, ENEMYBEU_HEIGHT, 1)->setDir(Vector2D(1, 0));
		AnimationEnemyBEUComponent* anim = enemy->addComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H, "fire", enemyTypes[rand() % 4], player);
		anim->changeState(AnimationEnemyBEUComponent::Moving);
		enemy->addComponent<Transform>(TRANSFORM_H, pos, ENEMYBEU_WIDTH, ENEMYBEU_HEIGHT, 2)->setDir(Vector2D(1, 0));
		enemy->addComponent<FramedImage>(FRAMEDIMAGE_H, anim->getTexture(), ENEMYBEU_WIDTH, ENEMYBEU_HEIGHT, anim->getNFrames(), anim->getType());
		enemy->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
		enemy->addComponent<EnemyBEUDirectionComponent>(ENEMYBEUDIRECTIONCOMPONENT_H, player, anim->getEnemy());
		enemy->addComponent<LifeComponent>(LIFECOMPONENT_H, ENEMYBEU_MAXLIFE);
		enemy->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, anim->getOffset(), anim->getColHeight(), anim->getColWidth());
		enemy->addComponent<ColDetectorComponent>(COLDETECTORCOMPONENT_H, enemy, player);
		anim->initComponent();
		enemy->addComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);
		enemyRef[i] = enemy->getComponent<LifeComponent>(LIFECOMPONENT_H);
	}
}

void FireBossComponent::createColumns(Vector2D pos) {
	Entity* c = mngr_->addEntity();
	trans_column = c->addComponent<Transform>(TRANSFORM_H,pos,45,90);
	column_image = c->addComponent<FramedImage>(IMAGE_H, &sdlutils().images().at("FireColumn"), 45, 90,15,0);
	c->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(0, 0), 90, 45);
	//c->addComponent<ColDetectorComponent>(COLDETECTORCOMPONENT_H, c, player);
	c->addComponent<LifeBasicComponent>(LIFEBASICCOMPONENT_H,1);
	fire_colums.push_back(c);
}

void FireBossComponent::subLife(float dmg) {
	current_life -= dmg;
	int save = barWidth_;
	barWidth_ = ((current_life * backWidth_) / maxLife_);
	diff = save - barWidth_;
	if (current != recovery && current != paused) {
		current = attack;
	}
	hit->play();
	//ESTO FUNCIONA
	if (current_life <= 0.25 * maxLife_ &&  current!=recovery && canfire2 ) {
		image->setAnim("FireBoss", 8, true, 4);
		my_transform->setPos({ 1000, -1000 });
		createColumns(column1);
		createColumns(column2);
		createColumns(column3);
		canfire2 = false;
		current = recovery;
		vanish->play();
	}
	else if(current_life <= 0.5 * maxLife_ && canSummonEnemies && current != recovery){
		summonEnemies(nEnemies);
		canSummonEnemies = false;
		current = paused;
	}
	else if (current_life <= 0.7 * maxLife_ && canfire &&current!=recovery) {
		image->setAnim("FireBoss", 10, true, 4);
		canfire = false;
		my_transform->setPos({ 1000, -1000 });
		createColumns(column1);
		createColumns(column2);
		current = recovery;
		vanish->play();
	}
	else if (current_life <= 0) {
		ent_->setAlive(false);
		static_cast<BeatEmUpState*>(mngr_)->finishBEU(); // Restar nEnemies para que acabe la batalla
	}
}

void FireBossComponent::moreLife() {
	current_life += 10;
	barWidth_ = ((current_life * backWidth_) / maxLife_);
}

void FireBossComponent::render() {
	SDL_Rect src = { 0, 0, 400, 50 };

	SDL_Rect dest;
	dest.x = 8 * (WIN_WIDTH / 13);
	dest.y =  35 * scale;
	dest.h = backHeight_;
	dest.w = backWidth_;
	backTexture->render(src, dest);

	dest.x = 8 * (WIN_WIDTH / 13);
	dest.h = barHeight_;
	dest.w = barWidth_;
	LifeBarTexture->render(src, dest);

	dest.x = 8 * (WIN_WIDTH / 13);
	dest.h = borderHeight_;
	dest.w = borderWidth_;
	borderTexture->render(src, dest);
 }
#include "PlayerBEU.h"
#include "../components/Image.h"

PlayerBEU::PlayerBEU() : Entity() {

	//int width = PlayerWidth_ / framesT_;
	tr = addComponent<Transform>(TRANSFORM_H, PlayerPosition_, PlayerWidth_, PlayerHeigth_, PlayerRotation_,speed_, framesT_, matrix_);
	t = new Texture(GameManager::instance()->getRenderer(), "./assets/Player/BeatEmUp/Fire/spritesheets/fireMatrix.png");
	//cmpId_type x = int(RENDERCOMPONENT_H);
	//referencia al texture y al transform
	fila_ = 0;	
	
	
	mov = addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	
	//igualamos el inputComponent a una variable ya que este necesita una referencia de image que aún no existe, por lo que esa referencia es NULL
	in_=addComponent<InputComponentBEU>(INPUTCOMPONENTBEU_H);

	addComponent<Image>(int(IMAGE_H), t, nframes, framesT_, fila_);
	//addComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H), Vector2D(100, 100), 20, 20);
	addComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);

	addComponent<LimitBEU>(LIMITBEU_H);
	
	//Al hacer aquí initComponent la referencia ya es correcta
	in_->initComponent();
	
	addComponent<ColliderComponent>(int(COLLIDERCOMPONENT_H), Vector2D(100, 70), PlayerHeigth_/2, PlayerWidth_/(framesT_*4));

}
PlayerBEU::~PlayerBEU() {

}
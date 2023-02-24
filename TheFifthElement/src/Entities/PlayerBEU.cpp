#include "PlayerBEU.h"
#include "../components/Image.h"
PlayerBEU::PlayerBEU() : Entity() {

	//int width = PlayerWidth_ / framesT_;
	tr = addComponent<Transform>(TRANSFORM_H, PlayerPosition_, PlayerWidth_, PlayerHeigth_, PlayerRotation_, framesT_, matrix_);
	t = new Texture(GameManager::instance()->getRenderer(), "./assets/PlayableCharacters/BeatEmUp/Fire/spritesheets/fireMatrix.png");
	//cmpId_type x = int(RENDERCOMPONENT_H);
	//referencia al texture y al transform
	fila_ = 0;	
	
	addComponent<AttackBoxComponent>(ATTACKBOXCOMPONENT_H);
	mov = addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	
	//igualamos el inputComponent a una variable ya que este necesita una referencia de image que aún no existe, por lo que esa referencia es NULL
	in_=addComponent<InputComponentBEU>(INPUTCOMPONENTBEU_H);

	addComponent<Image>(int(IMAGE_H), t, nframes, framesT_, fila_);
	
	//Al hacer aquí initComponent la referencia ya es correcta
	in_->initComponent();

}
PlayerBEU::~PlayerBEU() {

}
void PlayerBEU::setAttack(bool a) {
	is_attaking = a;
}
const bool PlayerBEU::getAttack() const {
	return is_attaking;
}
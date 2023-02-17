#include "PlayerBEU.h"
#include "Image.h"
PlayerBEU::PlayerBEU(GameManager* gm_) : Entity() {
	cmpId_type z = int(TRANSFORM_H);
	//int width = PlayerWidth_ / framesT_;
	tr = addComponent<Transform>(z, PlayerPosition_, PlayerWidth_, PlayerHeigth_, PlayerRotation_, framesT_, matrix_);
	t = new Texture(gm_->getRenderer(), "./assets/PlayableCharacters/BeatEmUp/Fire/spritesheets/fireMatrix.png");
	//cmpId_type x = int(RENDERCOMPONENT_H);
	//referencia al texture y al transform
	fila_ = 0;
	addComponent<Image>(int(IMAGE_H), t, nframes, framesT_, fila_);
	cmpId_type s = int(MOVEMENTCOMPONENT_H);
	mov = addComponent<MovementComponent>(s);
	cmpId_type w = int(INPUTCOMPONENTBEU_H);
	addComponent<InputComponentBEU>(w);

}
PlayerBEU::~PlayerBEU() {

}
void PlayerBEU::setAttack(bool a) {
	is_attaking = a;
}
const bool PlayerBEU::getAttack() const {
	return is_attaking;
}
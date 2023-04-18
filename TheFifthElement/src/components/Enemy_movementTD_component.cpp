#include "Enemy_movementTD_component.h"
#include "../utils/Entity.h"
Enemy_movementTD_component::Enemy_movementTD_component(string type) {
	type_ = type;
	if (type_ != "boss") state_ = "left";
	else state_ = "right";
}

void Enemy_movementTD_component::initComponent() {
	im_ = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
}

void Enemy_movementTD_component::changeState(Vector2D dir) {

	if (dir == Vector2D(1, 0)) {
		state_ = "right";
	}
	else if (dir == Vector2D(-1, 0)) {
		state_ = "left";
	}
	else {
		if (state_ == "left") state_ = "right";
		else state_ = "left";
	}

	if (type_ == "boss");
	else if (type_ == "mushroom") {
		im_->setAnim("TD_mushroom_" + state_, 7, false);
		//im_->setAnimTexture("TD_mushroom_" + state_, 7, 68);
	}
	else if (type_ == "goblin") {
		im_->setAnim("TD_goblin_" + state_, 7, false);
		//im_->setAnimTexture("TD_goblin_" + state_, 7, 68);
	}
	else if (type_ == "bat") {
		im_->setAnim("TD_bat_" + state_, 7, false);
		//im_->setAnimTexture("TD_bat_" + state_, 7, 68);
	}
	else if (type_ == "skeleton") {
		im_->setAnim("TD_skeleton_" + state_, 6, false);
		//im_->setAnimTexture("TD_skeleton_" + state_, 6, 86);
	}
}
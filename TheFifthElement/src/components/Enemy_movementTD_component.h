#pragma once
#include "../utils/Component.h"
#include "../utils/Vector2D.h"
#include "Image.h"
class Enemy_movementTD_component :public Component {
private:

	/*enum state {
		Idle, Left, Right
	};
	state st_;*/
	string type_;
	string state_;
	Image* im_;
public:
	Enemy_movementTD_component(string type) {
		//st_ = Idle;
		type_ = type;
		state_ = "left";
	}

	void initComponent() {
		im_ = ent_->getComponent<Image>(IMAGE_H);
	}

	void changeState(Vector2D dir) {
		
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


		if (type_ == "mushroom") {
			im_->setAnimTexture("TD_mushroom_" + state_, 7, 68);
		}
		else if (type_ == "goblin") {
			im_->setAnimTexture("TD_goblin_" + state_, 7, 68);
		}
		else if (type_ == "bat") {
			im_->setAnimTexture("TD_bat_" + state_, 7, 68);
		}
		else if (type_ == "skeleton") {
			im_->setAnimTexture("TD_skeleton_" + state_, 6, 86);
		}
	}
	string getState() { return state_; }
};
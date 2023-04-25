#pragma once

#include "Transform.h"
#include "../utils/Vector2D.h"

class MovementComponent : public Component {
public:
	MovementComponent() {
	
	}
	virtual ~MovementComponent() {}
	void initComponent();
	void update();
	void setDir(Vector2D direction) {
		tr_->setDir(direction);
	}
	void setNewPos(Vector2D position);
private:


	Transform* tr_ = nullptr;
};

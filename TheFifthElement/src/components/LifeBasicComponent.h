#pragma once
#include "../utils/Component.h"
#include "Transform.h"

class LifeBasicComponent :public Component {
private:
	int life;
public:
	LifeBasicComponent(int l) {
		life = l;
	}
	virtual ~LifeBasicComponent(){}
	inline void morelife(int more) {
		life += more;
	}
	inline void lesslife(int less) {
		life -= less;
	}
	inline int getlife() { return life; }
	inline void setlife(int l) { life = l;}
	void update() {
		if (life <= 0) {
			ent_->getComponent<Transform>(TRANSFORM_H)->setPos({ 10000,10000 });

		}
	}
	
};
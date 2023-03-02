#pragma once
#include "../utils/Component.h"
#include "../Entities/PlayerTD.h"
#include "../components/Transform.h"



class ColliderTileComponent :public Component {
private:
	PlayerTD* p;
	Transform* tr;
	bool isActive_ = true; 
	bool isColliding_ = false;
public:
	void initComponent();
	ColliderTileComponent(PlayerTD* p) {
		this->p = p;
	}
	virtual ~ColliderTileComponent(){}
	void update();
	inline bool isActive() { return isActive_; }
	inline void setColliding(bool p) { isColliding_ = p; }
};

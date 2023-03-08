//#pragma once
//#include "../utils/Entity.h"
//#include "../components/Transform.h"
//#include "../utils/ecs.h"
//#include "../sdlutils/Texture.h"
//#include "../GameManager.h"
//#include "../components/CheckCollision.h"
//#include "PlayerTD.h"
//#include "../components/ObjectsComponent.h"
//#include "Portal.h"
//
//
//class Element : public Entity
//{
//private:
//	Vector2D elementPosition_;
//	float elementWidth_ = ELEMENT_WIDTH, elementHeight_ = ELEMENT_HEIGHT, elementRotation_ = 1, elementSpeed = 0;
//	Texture* t;
//	Transform* tr;
//	Transform* trPlayer_;
//	Portal* portal_;
//	PlayerTD* player_;
//	CheckCollision* ch;
//	bool picked = false;
//	int nframes = 4;
//public:
//	~Element() {}
//
//	void update() {}
//	inline bool GetPicked() {
//		return picked;
//	}
//
//	inline void SetPicked(bool newValue) {
//		picked = newValue;
//		portal_->elementEarned();
//	}
//
//	Element(PlayerTD* player, Vector2D pos, Portal* portal);
//};

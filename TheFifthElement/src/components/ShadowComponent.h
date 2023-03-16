#pragma once
#include "../utils/Component.h"
#include"Transform.h"
#include "../utils/ecs.h"
#include "../sdlutils/SDLUtils.h"
#include "JumpComponent.h"

class ShadowComponent : public Component {
protected:
	Entity* p;
	Transform* trans_player;
	Texture* t=&SDLUtils::instance()->images().at("shadow");
	JumpComponent* Jump_player;
	int src_width = 62;
	int src_height = 40;
	int jump_poss_y;

public:
	ShadowComponent(Entity* player);
	virtual ~ShadowComponent();
	virtual void initComponent();
	virtual void update();
	virtual void render();
	virtual void handleEvent(SDL_Event event);

	inline void Setpos_y(int i) {
		jump_poss_y = i;
	}
};

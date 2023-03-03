#pragma once
#include "../utils/Entity.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../utils/ecs.h"
#include "../sdlutils/SDLUtils.h"
class Background :public Entity {
public:
	Background(string file) {
		int f = 0;
		bool matrix = false;
		Vector2D v = { 0,0 };
		int r = 0;
		addComponent<Transform>(int(TRANSFORM_H), v, WIN_WIDTH, WIN_HEIGHT,r,0, f, matrix);
		Texture* t = &SDLUtils::instance()->images().at(file);
		addComponent<Image>(int(IMAGE_H), t,f, f, f, BACKGROUNDAIR_WIDTH_FRAME, BACKGROUNDAIR_HEIGHT_FRAME);
	}
};
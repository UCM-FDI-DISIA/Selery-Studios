#pragma once
#include "../utils/Entity.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../utils/ecs.h"
#include "../sdlutils/SDLUtils.h"
class Background :public Entity {
public:
	Background() {
		int w = 900;
		int h = 600;
		int f = 0;
		bool matrix = false;
		Vector2D v = { 0,0 };
		int r = 0;
		addComponent<Transform>(int(TRANSFORM_H), v, w, h,r, f, matrix);
		Texture* t = &SDLUtils::instance()->images().at("fondo");
		addComponent<Image>(int(IMAGE_H), t,f, f, f);
		//Texture* tex, int nframes, int framesT, int fila
	//		Vector2D pos, float w, float h, float r, int frames, bool matrix
	}
};
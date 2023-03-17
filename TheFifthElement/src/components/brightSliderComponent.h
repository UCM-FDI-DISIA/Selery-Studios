#pragma once
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
class brightSliderComponent : public Component {
public:
	void channgeBrightness(float value) {
		value = value / 100.0f; // El slider que tenemos tiene un valor wntre 0 y 100 y necesitamos valores entre 0.0 y 1.0
		SDL_SetWindowBrightness(sdlutils().window(), value); 
	}
};
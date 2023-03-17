#pragma once
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"

class brightSliderComponent : public Component {
public:
	// El slider devuelve un valor entre 0 y 100 y necesitamos valores entre 0.0 y 1.0
	// Ademas si el valor de brillo es menor que 0.23 se aproxima a 0 y el brillo no cambia (cont)
	// Por eso hago la conversion 0,23 + value * 0,0077
	void channgeBrightness(float value) {
		value = 0.23f + value / 100.0f * 0.77f; 
		SDL_SetWindowBrightness(sdlutils().window(), value); 
	}
};
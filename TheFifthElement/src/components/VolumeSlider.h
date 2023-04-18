#pragma once
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/SoundManager.h"


class VolumeSlider : public Component {

public:

	void changeVolume(float value) {
	/*	value = (value * 0.01f)/10.0f;*/ //Debería ser así
		soundManager().setSFXVolume(value);
	}
};
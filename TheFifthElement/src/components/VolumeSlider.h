#pragma once
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/SoundManager.h"


class VolumeSlider : public Component {

public:

	void changeVolume(float value) {
		soundManager().setSFXVolume(value);
	}
};
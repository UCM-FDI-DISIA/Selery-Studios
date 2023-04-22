#pragma once
#include "../utils/Entity.h"
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"

class PropertiesManager;

class PowerUpControler : public Component {
private:
    const float POWERUP_DURATION = 5000; // En milisegundos
    const float DMG_MULT = 1.2F;

    int timeEndStrenght;

public:
    PowerUpControler(){}
    void initComponent(){}
    void update();
    void strenghtBonus();
};
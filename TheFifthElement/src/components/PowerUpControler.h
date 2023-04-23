#pragma once
#include "../utils/Entity.h"
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "MovementComponent.h"
#include "LifeComponent.h"

class PropertiesManager;

class PowerUpControler : public Component {
private:
    const float POWERUP_DURATION = 5000; // En milisegundos
    
    const float DMG_MULT = 1.2f;
    const float SPD_MULT = 2.0f;
    const float DMG_REDUCTION_MULT = 0.5f;
    const float INV_HITS = 2;

    int invulnerabilityHits = 0;
    int timeEndStrenght;
    int timeEndSpeed;
    int timeEndDamageReduction;

    Transform* _myTransform;

public:
    PowerUpControler(){}
    void initComponent();
    void update();

    void strenghtBonus();
    void speedBonus();
    void reductionBonus();
    void invulnerabilityBonus();
};
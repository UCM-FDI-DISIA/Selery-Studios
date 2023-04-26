#pragma once
#include "../utils/Entity.h"
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "LifeComponent.h"

class PropertiesManager;

class PowerUpControler : public Component {
private:
    const float POWERUP_DURATION = 10000; // En milisegundos
    
    const float DMG_MULT = 1.2f;
    const float SPD_MULT = 1.7f;
    const float DMG_REDUCTION_MULT = 0.5f;
    const float MAX_INV_HITS = 2;
    const float LF_HEAL = 2;

    int timeEndStrenght;
    int timeEndSpeed;
    int timeEndDamageReduction;
    int invulnerabilityHits = 0;
    float invLife;
    string previousFrameType; // Si el jugador cambia de skin no debe perder la invulnerabilidad

    Transform* _myTransform;
    LifeComponent* _myLifeComponent;

    Texture* dmgText;
    Texture* spdText;
    Texture* dmgRedText;
    Texture* shieldText;

public:
    PowerUpControler(){}
    void initComponent();
    void update();
    void render();

    void instancePowerUp();

    void strenghtBonus();
    void speedBonus();
    void reductionBonus();
    void invulnerabilityBonus();
    void healBonus();
};
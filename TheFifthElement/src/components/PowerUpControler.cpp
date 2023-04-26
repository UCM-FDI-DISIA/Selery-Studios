#include "PowerUpControler.h"
#include "../utils/PropertiesManager.h"

void PowerUpControler::initComponent() {
    _myTransform = ent_->getComponent<Transform>(TRANSFORM_H);
    _myLifeComponent = ent_->getComponent<LifeComponent>(LIFECOMPONENT_H);

    dmgText = &sdlutils().images().at("dmgIcon");
    spdText = &sdlutils().images().at("spdIcon");
    dmgRedText = &sdlutils().images().at("dmgRedIcon");
    shieldText = &sdlutils().images().at("shieldIcon");
}

void PowerUpControler::update() {
    if (properties().getMult() != 1 && timeEndStrenght <= sdlutils().currRealTime()) { // Fuerza
        properties().setMult();
        sdlutils().soundEffects().at("dmgEnd").play();
    }
    if (_myTransform->getVel() == PLAYERBEU_SPEED * SPD_MULT && timeEndSpeed <= sdlutils().currRealTime()) { // Velocidad
        _myTransform->setVel(_myTransform->getVel() / SPD_MULT);
        sdlutils().soundEffects().at("spdEnd").play();
    }
    if (_myLifeComponent->getDamageReduction() != 1 && timeEndDamageReduction <= sdlutils().currRealTime()) { // Reducción
        _myLifeComponent->setDamageReduction();
        sdlutils().soundEffects().at("dmgRedEnd").play();
    }
    if (invulnerabilityHits > 0 && _myLifeComponent->getLife() < invLife) { // Invulnerabilidad
        invulnerabilityHits--;
        _myLifeComponent->setLife(invLife);
        sdlutils().soundEffects().at("shieldEnd").play();
    }
}



void PowerUpControler::instancePowerUp() {
    int prct = 1 + (rand() % 100);
    if (prct <= 30) { // Fuerza
        strenghtBonus();
    }
    else if (prct <= 45) { // Velocidad
        speedBonus();
    }
    else if (prct <= 60) { // Reducción
        reductionBonus();
    }
    else if (prct <= 70) { // Invulnerabilidad
        invulnerabilityBonus();
    }
    else if (prct <= 80) { // Curación
        healBonus();
    }
    // 80 < prct <= 100 // No recibe powerUp
}



void PowerUpControler::strenghtBonus() {
    properties().setMult(DMG_MULT);
    timeEndStrenght = sdlutils().currRealTime() + POWERUP_DURATION;
    sdlutils().soundEffects().at("dmgStart").play();
}

void PowerUpControler::speedBonus() {
    if (_myTransform->getVel() == PLAYERBEU_SPEED) {
        _myTransform->setVel(_myTransform->getVel() * SPD_MULT);
        timeEndSpeed = sdlutils().currRealTime() + POWERUP_DURATION;
        sdlutils().soundEffects().at("spdStart").play();
    }
}

void PowerUpControler::reductionBonus() {
    _myLifeComponent->setDamageReduction(DMG_REDUCTION_MULT);
    timeEndDamageReduction = sdlutils().currRealTime() + POWERUP_DURATION;
    sdlutils().soundEffects().at("dmgRedStart").play();
}

void PowerUpControler::invulnerabilityBonus() {
    if (invulnerabilityHits < MAX_INV_HITS){
        ++invulnerabilityHits; 
        invLife = _myLifeComponent->getLife();
        sdlutils().soundEffects().at("shieldStart").play();
    }
}

void PowerUpControler::healBonus() {
    int currentLife = _myLifeComponent->getLife();
    int maxLife = _myLifeComponent->getMaxLife();

    if (currentLife + LF_HEAL > maxLife) { _myLifeComponent->setLife(maxLife); }
    else { _myLifeComponent->setLife(currentLife + LF_HEAL); }

    _myLifeComponent->updateLifeBar();
    sdlutils().soundEffects().at("heal").play();
}

void PowerUpControler::render() {
    int posx = 90; int posy = 55; // Posición de la barra de vida del playes deplazado hacia abajo

    if (properties().getMult() != 1) { // Fuerza
        dmgText->render({ posx, posy, ICON_SIZE, ICON_SIZE });
        posx += ICON_SIZE;
    }
    if (_myTransform->getVel() == PLAYERBEU_SPEED * SPD_MULT) { // Velocidad
        spdText->render({ posx, posy, ICON_SIZE, ICON_SIZE });
        posx += ICON_SIZE;
    }
    if (_myLifeComponent->getDamageReduction() != 1) { // Reducción
        dmgRedText->render({ posx, posy, ICON_SIZE, ICON_SIZE });
        posx += ICON_SIZE;
    }
    if (invulnerabilityHits > 0) { // Invulnerabilidad
        shieldText->render({ posx, posy, ICON_SIZE, ICON_SIZE });
        posx += ICON_SIZE;
    }
}
#include "PowerUpControler.h"
#include "../utils/PropertiesManager.h"

void PowerUpControler::initComponent() {
    _myTransform = ent_->getComponent<Transform>(TRANSFORM_H);
    _myLifeComponent = ent_->getComponent<LifeComponent>(LIFECOMPONENT_H);
}

void PowerUpControler::update() {
    if (properties().getMult() != 1 && timeEndStrenght <= sdlutils().currRealTime()) {
        properties().setMult();
        cout << "zoi devil" << endl;
    }
    if (_myTransform->getVel() == PLAYERBEU_SPEED * SPD_MULT && timeEndSpeed <= sdlutils().currRealTime()) {
        _myTransform->setVel(_myTransform->getVel() / SPD_MULT);
        cout << "l  e  n  t  o  o  o" << endl;
    }
    if (_myLifeComponent->getDamageReduction() != 1 && timeEndDamageReduction <= sdlutils().currRealTime()) {
        _myLifeComponent->setDamageReduction();
        cout << "TOMATE UNA SENZU" << endl;
    }
    if (invulnerabilityHits > 0 && _myLifeComponent->getLife() < invLife) {
        invulnerabilityHits--;
        _myLifeComponent->setLife(invLife);
        cout << "ESCUDO ROTO, ESTA A UNA BALA" << endl;
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
    cout << "FUERZAAA" << endl;
}

void PowerUpControler::speedBonus() {
    if (_myTransform->getVel() == PLAYERBEU_SPEED) {
        _myTransform->setVel(_myTransform->getVel() * SPD_MULT);
        timeEndSpeed = sdlutils().currRealTime() + POWERUP_DURATION;
        cout << "RAPIDOOOO" << endl;
    }
}

void PowerUpControler::reductionBonus() {
    _myLifeComponent->setDamageReduction(DMG_REDUCTION_MULT);
    timeEndDamageReduction = sdlutils().currRealTime() + POWERUP_DURATION;
    cout << "WISH" << endl;
}

void PowerUpControler::invulnerabilityBonus() {
    if (invulnerabilityHits < MAX_INV_HITS){
        ++invulnerabilityHits; 
        invLife = _myLifeComponent->getLife();
    }
    cout << "CAN'T TOUCH THIS" << endl;
}

void PowerUpControler::healBonus() {
    int currentLife = _myLifeComponent->getLife();
    int maxLife = _myLifeComponent->getMaxLife();

    if (currentLife + LF_HEAL > maxLife) 
        _myLifeComponent->setLife(maxLife);
    else
        _myLifeComponent->setLife(currentLife + LF_HEAL);

    _myLifeComponent->updateLifeBar();
    cout << "KAKAROTO VEN Y SANA MI DOLOOOOOOR" << endl;
}
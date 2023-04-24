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
    cout << "CAN'T TOUCH THIS" << endl;
}
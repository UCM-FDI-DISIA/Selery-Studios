#include "PowerUpControler.h"
#include "../utils/PropertiesManager.h"

void PowerUpControler::update() {
    if (properties().getMult() != 1 && timeEndStrenght <= sdlutils().currRealTime()) {
        properties().setMult();
        cout << "zoi devil" << endl;
    }
}

void PowerUpControler::strenghtBonus() {
    properties().setMult(DMG_MULT);
    timeEndStrenght = sdlutils().currRealTime() + POWERUP_DURATION;
    cout << "FUERZAAA" << endl;
}
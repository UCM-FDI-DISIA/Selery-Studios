#pragma once
#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H_
#include "../utils/Component.h"
#include "MovementComponent.h"
#include "SkinComponent.h"
#include "SDL_events.h"
#include <string>
#include "DialogueComponent.h"
#include <array>
#include "rouletteComponent.h"

enum Directions {
    NONE=-1,
    UP=0, DOWN=1, LEFT=2, RIGHT=3
};

class InputComponent : public Component {
private:
    Directions d;
    bool npccol = false;
    double actionDelay;
    MovementComponent* mov_ = nullptr;
    SkinComponent* skin_ = nullptr;
    DialogueComponent* dialog = nullptr;
    Roulette* roulet;
    bool elements[4];
    SoundManager* smg_=nullptr;
public:
    InputComponent(Roulette* r);
    void initComponent();
    void update();
    void handleEvents(SDL_Event event);
    void changebool(){ npccol = false; }
    inline void setDirection(int dd) {
        d = Directions(dd);
    }

    void setAir(bool b) { elements[0] = b; }
    void setFire(bool b) { elements[1] = b; }
    void setWater(bool b) { elements[2] = b; }
    void setEarth(bool b) { elements[3] = b; }
};
#endif
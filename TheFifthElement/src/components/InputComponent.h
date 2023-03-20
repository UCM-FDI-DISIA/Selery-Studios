#pragma once
#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H_
#include "../utils/Component.h"
#include "MovementComponent.h"
#include "SkinComponent.h"
#include "SDL_events.h"
#include <string>
#include "DialogueComponent.h"

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
public:
    InputComponent();
    void initComponent();
    void update();
    void handleEvents(SDL_Event event);
    void changebool(){ npccol = false; }
    inline void setDirection(int dd) {
        d = Directions(dd);
    }
};
#endif
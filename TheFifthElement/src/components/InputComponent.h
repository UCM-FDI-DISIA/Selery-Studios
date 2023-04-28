#pragma once
#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H_
#include "../utils/Component.h"
#include "MovementComponent.h"
#include "SkinComponent.h"
#include "SDL_events.h"
#include <string>
#include <array>
#include "rouletteComponent.h"
#include "../Elements.h"

enum Directions {
    NONE = -1,
    UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, UPLEFT = 4, UPRIGHT = 5, DOWNLEFT = 6, DOWNRIGHT = 7
};

class DialogueComponent;

class InputComponent : public Component {
private:
    Directions d;
    SDL_GameController* controller;
    bool npccol = false;
    double actionDelay;
    MovementComponent* mov_ = nullptr;
    SkinComponent* skin_ = nullptr;
    DialogueComponent* dialog = nullptr;
    Roulette* roulet;
    bool controladorDetectado;
    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;
    bool canTalk = false;
    bool canSave = false;
    bool canLoad = false;
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
};
#endif
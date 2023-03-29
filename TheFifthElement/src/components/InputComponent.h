#pragma once
#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H_
#include "../utils/Component.h"
#include "MovementComponent.h"
#include "SkinComponent.h"
#include "SDL_events.h"
#include <string>


class InputComponent : public Component {
private:
    bool npccol = false;
    double actionDelay;
    MovementComponent* mov_ = nullptr;
    SkinComponent* skin_ = nullptr;
<<<<<<< Updated upstream

=======
    DialogueComponent* dialog = nullptr;
    Roulette* roulet;
    bool elements[4];
    SoundManager* smg_=nullptr;
    bool moveLeft, moveRight, moveUp, moveDown;
>>>>>>> Stashed changes
public:
    InputComponent();
    void initComponent();
    void update();
    void handleEvents(SDL_Event event);
    void changebool(){ npccol = false; }
};
#endif
#pragma once
#include "../utils/Component.h"
#include "MovementComponent.h"
#include "SDL_events.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../components/JumpComponent.h"
#include "../components/LifeComponent.h"
#include "../components/ShadowComponent.h"
#include "SkinBEUComponent.h"
#include "rouletteComponent.h"
#include <array>
class Image;

class InputComponentBEU : public Component {
private:
    Transform* tr_ = nullptr;
    Image* im_ = nullptr;
    JumpComponent* jmp_ = nullptr;
    Texture* t_ = nullptr;
    LifeComponent* lifeC_ = nullptr;
    ShadowComponent* shadow = nullptr;
    SkinBEUComponent* sk_ = nullptr;
    Roulette* roulette;
    bool alreadyPressedBasic = false;
    bool alreadyPressedSpecial = false;
    bool alreadyPressed2 = false;
    bool moveLeft, moveRight, moveUp, moveDown, jump;


public:
    bool elements[4];

    InputComponentBEU(Roulette* r);
    void initComponent();
    void update();
    void handleEvents(SDL_Event event);

    void setAir(bool b);
    void setFire(bool b);
    void setWater(bool b);
    void setEarth(bool b);
};
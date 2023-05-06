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
#include "ObjectsComponent.h"
#include "StoneComponent.h"
#include <array>
#include "../Elements.h"
#include "ThrowableObject.h"
class Image;

class InputComponentBEU : public Component {
private:
    SDL_Color color = { 50, 50, 0 };
    Font* font_;
    Texture* p;
    Transform* tr_ = nullptr;
    FramedImage* im_ = nullptr;
    SDL_GameController* controller;
    JumpComponent* jmp_ = nullptr;
    LifeComponent* lifeC_ = nullptr;
    ShadowComponent* shadow = nullptr;
    SkinBEUComponent* sk_ = nullptr;
    Roulette* roulette;
    bool alreadyPressedBasic = false;
    bool alreadyPressedSpecial = false;
    bool alreadyPressed2 = false;
    bool moveLeft, moveRight, moveUp, moveDown, jump;
    bool earthStage3 = false;
    int direction;

    float timeExecution, ultiTime;

public:
    bool elements[4];

    InputComponentBEU(Roulette* r);
    void initComponent();
    void update();
    void render();
    void handleEvents(SDL_Event event);

    void setAir(bool b);
    void setFire(bool b);
    void setWater(bool b);
    void setEarth(bool b);

    void vibrate(SDL_GameController* controller, int duration_ms, float intensity);

    void MovePlayerBack();

    inline void setEarthStage3(bool newValue) { earthStage3 = newValue; }
    inline bool getEarthStage3() { return earthStage3; }
};
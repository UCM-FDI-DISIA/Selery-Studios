#pragma once
#include "../utils/Component.h"
#include "MovementComponent.h"
#include "SDL_events.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../components/JumpComponent.h"
#include "../components/LifeComponent.h"
class Image;

class InputComponentBEU : public Component {
private:
    Transform* tr_ = nullptr;
    Image* im_ = nullptr;
    JumpComponent* jmp_ = nullptr;
    Texture* t_ = nullptr;
    LifeComponent* lifeC_ = nullptr;

    bool alreadyPressedBasic = false;
    bool alreadyPressedSpecial = false;
    bool alreadyPressed2 = false;
    bool moveLeft, moveRight, moveUp, moveDown, jump;
public:
    InputComponentBEU();
    void initComponent();
    void update();
    void handleEvents(SDL_Event event);
};
#pragma once
#include "../utils/Component.h"
#include "MovementComponent.h"
#include "SDL_events.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

class Image;
class InputComponentBEU : public Component
{
private:
    Transform* tr_ = nullptr;
    Image* im_ = nullptr;
    bool canJump = true;
    Texture* t_ = nullptr;

public:
    InputComponentBEU();
    void initComponent();
    void update();
    void handleEvents(SDL_Event event);
};

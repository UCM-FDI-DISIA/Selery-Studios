#pragma once
#include "../utils/Component.h"
#include "MovementComponent.h"
#include "SDL_events.h"
#include "../sdlutils/SDLUtils.h"

class Image;
class InputComponentBEU : public Component
{
private:
    Transform* tr_ = nullptr;
    Image* im_ = nullptr;
    bool canJump = true;

public:
    InputComponentBEU();
    void initComponent();
    void update();
    void handleEvents(SDL_Event event);
<<<<<<< Updated upstream

private:
    Transform* tr_ = nullptr;
    Image* im_ = nullptr;
    Texture* t_ = nullptr;
    float downLimit, topLimit;
};

=======
};
>>>>>>> Stashed changes

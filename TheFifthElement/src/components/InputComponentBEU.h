#pragma once
#include "../utils/Component.h"
#include "MovementComponent.h"
#include "SDL_events.h"
<<<<<<< Updated upstream
#include "Transform.h"
=======
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "JumpComponent.h"
>>>>>>> Stashed changes

class Image;
class InputComponentBEU : public Component
{
<<<<<<< Updated upstream
=======
private:
    Transform* tr_ = nullptr;
    JumpComponent* jmp_ = nullptr;
    Image* im_ = nullptr;
    Texture* t_ = nullptr;

    float downLimit, topLimit;

>>>>>>> Stashed changes
public:
    InputComponentBEU();
    void initComponent();
    void update();
    
private:
    Transform* tr_ = nullptr;
    Image* im_ = nullptr;
};


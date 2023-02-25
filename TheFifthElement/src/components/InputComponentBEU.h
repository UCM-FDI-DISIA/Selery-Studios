#pragma once
#include "../utils/Component.h"
#include "MovementComponent.h"
#include "SDL_events.h"
#include "Transform.h"

class Image;
class InputComponentBEU : public Component
{
public:
    InputComponentBEU();
    void initComponent();
    void update();
    void handleEvents(SDL_Event event);
private:
 
    Transform* tr_ = nullptr;
    Image* im_ = nullptr;
  
};


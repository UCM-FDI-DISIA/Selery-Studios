#pragma once
#include "../utils/Component.h"
#include "MovementComponent.h"
#include "SDL_events.h"

class Image;
class InputComponentBEU : public Component
{
public:
    InputComponentBEU();
    void initComponent();
    void update();
    void handleEvents(SDL_Event event);
private:
 
    MovementComponent* mov_ = nullptr;
    Image* im_ = nullptr;
  
};


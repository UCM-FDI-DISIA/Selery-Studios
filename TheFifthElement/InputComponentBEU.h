#pragma once
#include "./utils/Component.h"
#include "MovementComponent.h"
#include "SDL_events.h"

class Image;
class InputComponentBEU : public Component
{
public:
    InputComponentBEU();
    void initComponent();
    void initComponentBEU();
    void update();
    void handleEvents(SDL_Event event);
    void stop_attack();
private:
    bool attack = false;
    MovementComponent* mov_ = nullptr;
    Image* img;
};


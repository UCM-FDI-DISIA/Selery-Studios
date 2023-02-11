#pragma once
#include "utils/Component.h"
#include "MovementComponent.h"

class ImputComponent : Component
{
public: 
    ImputComponent();
    void update(); 
private:
    MovementComponent* mov = nullptr;
};


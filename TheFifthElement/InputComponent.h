#pragma once
#include "utils/Component.h"
#include "MovementComponent.h"

class InputComponent : Component
{
public:
    InputComponent();
    void update();
private:
    MovementComponent* mov = nullptr;
};

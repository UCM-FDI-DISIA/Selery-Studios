#pragma once
#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H_
#include "utils/Component.h"
#include "MovementComponent.h"

class InputComponent : Component
{
public:
    InputComponent(MovementComponent* mov);
    void update();
private:
    
    MovementComponent* mov_ = nullptr;
};
#endif
#pragma once
#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H_
#include "utils/Component.h"
#include "MovementComponent.h"

class InputComponent : public Component
{
public:
    InputComponent();
    void initComponent();
    void update();
private:

    MovementComponent* mov_ = nullptr;
};
#endif
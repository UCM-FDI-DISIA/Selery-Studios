#pragma once
<<<<<<< Updated upstream
#ifndef INPUTCOMPONENT_H
=======
#ifndef INPUTCOMPONENT_H_
>>>>>>> Stashed changes
#define INPUTCOMPONENT_H_
#include "utils/Component.h"
#include "MovementComponent.h"

<<<<<<< Updated upstream
class InputComponent : Component
{
public:
    InputComponent(MovementComponent* mov);
    void update();
private:
    
=======
class InputComponent : public Component
{
public:
    InputComponent(MovementComponent* Mov_);
    InputComponent() {}
    void update();
private:

>>>>>>> Stashed changes
    MovementComponent* mov_ = nullptr;
};
#endif
#pragma once
#ifndef SKINCOMPONENT_H
#define SKINCOMPONENT_H_
#include "../utils/Component.h"
#include "../sdlutils/Texture.h"
#include "../GameManager.h"

class SkinComponent : public Component
{
public:
    enum AnimationStates
    {
        Idle, Left, Right, Up, Down, Null
    };
private:
    AnimationStates currentState_;
    AnimationStates nextState_;
    string t_;
    string skin_;
    int nframes_;
    int fila_;
    int w_, h_;
public:

    SkinComponent(string skin)
    {
        skin_ = skin;
    }
    void setIdle();
    void setLeft();
    void setRight();
    void setUp();
    void setDown();
    void initComponent();
    void update();
    void changeMov();
    void changeState(AnimationStates newState) { nextState_ = newState; };
    void changeSkin(string skin);

};
#endif
#pragma once
#include "../utils/Component.h"
#include "../sdlutils/Texture.h"
#include "../GameManager.h"
#include "Image.h"

class SkinBEUComponent : public Component
{
public:
    enum AnimationStates
    {
        Idle, Left, Right, Vertical, Jump, Hit, Death, Null
    };
private:
    AnimationStates currentState_;
    AnimationStates nextState_;
    string t_;
    string skin_;
    string prevSkin_;
    int nframes_;
    int fila_;
    int w_, h_;
    Image* im_;
    bool set_ = false;

public:

    SkinBEUComponent(string skin)
    {
        skin_ = skin;
        prevSkin_ = skin;
    }
    void setIdle();
    void setLeft();
    void setRight();
    void setVertical();
    void setJump();
    void setHit();
    void setDeath();
    void initComponent();
    void update();
    void changeMov();
    void changeState(AnimationStates newState) { nextState_ = newState; };
    void setTexture();
    void changeSkin(string skin) { skin_ = skin; }
    inline string getSkin() { return t_; }

};


#pragma once
#include "../utils/Component.h"
#include "../sdlutils/Texture.h"
#include "../utils/PropertiesManager.h"
#include "../GameManager.h"
#include "Image.h"

class LifeComponent;

class SkinBEUComponent : public Component
{
public:
    enum AnimationStates
    {
        Idle, Left, Right, Vertical, Jump, Hit, Death, Null
    };
    AnimationStates currentState_;
    AnimationStates nextState_;
private:
    string t_;
    string skin_;
    string prevSkin_;
    int nframes_;
    int fila_;
    int w_, h_;
    Image* im_;
    LifeComponent* lifeC_ = nullptr;
    bool set_ = false;
    PropertiesManager* props;

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
    void changeSkin(string skin);
    inline string getSkin() { return t_; }

};


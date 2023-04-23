#pragma once
#ifndef SKINCOMPONENT_H
#define SKINCOMPONENT_H_
#include "../utils/Component.h"
#include "../sdlutils/Texture.h"
#include "../GameManager.h"
#include "FramedImage.h"

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
    string prevSkin_;
    int nframes_;
    int fila_;
    FramedImage* im_;
    Texture* avatar_;

public:

    SkinComponent(string skin, Texture* avatar);
    void setIdle();
    void setLeft();
    void setRight();
    void setUp();
    void setDown();
    void initComponent();
    void update();
    void changeMov();
    void changeState(AnimationStates newState) { nextState_ = newState; };
    void changeSkin(string skin) {
        skin_ = skin;
    }
    void changeAvatar(Texture* avatar) { // cambia el icono en el minimapa
        avatar_ = avatar;
    }
    inline string getSkin() { return t_; }
    inline string getSkinPlayer() { return skin_; } // método para obtener el id "air", "fire",...
    inline Texture* getAvatar() { return avatar_; } // obtiene el icono para el minimapa

};
#endif
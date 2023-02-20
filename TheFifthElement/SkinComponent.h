#pragma once
#ifndef SKINCOMPONENT_H
#define SKINCOMPONENT_H_
#include "utils/Component.h"
#include "sdlutils/Texture.h"
#include "GameManager.h"
#include <string>


class SkinComponent : public Component
{
public:
    SkinComponent(GameManager* gm)
    {
        gm_ = gm;
        fire = new Texture(gm_->getRenderer(), "./assets/PlayableCharacters/Exploration/Fire/andar.png");
        air = new Texture(gm_->getRenderer(), "./assets/PlayableCharacters/Exploration/Fire/andararriba.png");
        water = new Texture(gm_->getRenderer(), "./assets/PlayableCharacters/Exploration/Fire/andar.png");
        earth = new Texture(gm_->getRenderer(), "./assets/PlayableCharacters/Exploration/Fire/andararriba.png");
        fila_ = 0;
    }
    void initComponent();
    void update();
    void changeSkin(string skin);
private:
    GameManager* gm_;
    Texture* fire;
    Texture* air;
    Texture* water;
    Texture* earth;
    int nframes = 7;
    int fila_;
};
#endif
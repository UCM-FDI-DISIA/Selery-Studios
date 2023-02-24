#pragma once
#ifndef SKINCOMPONENT_H
#define SKINCOMPONENT_H_
#include "../utils/Component.h"
#include "../sdlutils/Texture.h"
#include "../GameManager.h"
#include <string>


class SkinComponent : public Component
{
public:
    SkinComponent()
    {
        fire = new Texture(GameManager::instance()->getRenderer(), "./assets/PlayableCharacters/Exploration/Fire/andar.png");
        air = new Texture(GameManager::instance()->getRenderer(), "./assets/PlayableCharacters/Exploration/Fire/andararriba.png");
        water = new Texture(GameManager::instance()->getRenderer(), "./assets/PlayableCharacters/Exploration/Fire/andar.png");
        earth = new Texture(GameManager::instance()->getRenderer(), "./assets/PlayableCharacters/Exploration/Fire/andararriba.png");
        fila_ = 0;
    }
    void initComponent();
    void update();
    void changeSkin(string skin);
private:
    Texture* fire;
    Texture* air;
    Texture* water;
    Texture* earth;
    int nframes = 7;
    int fila_;
};
#endif
#pragma once
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../utils/Entity.h"
#include "Transform.h"
#include "FramedImage.h"

class WaterBossLife : public Component
{
private:

    float barWidth_, barHeight_;
    Texture* barTexture_;

    float backWidth_, backHeight_;
    Texture* backTexture_;

    float borderWidth_, borderHeight_;
    Texture* borderTexture_;

    FramedImage* im_;
    Transform* tr_;
    int life, maxLife;
    bool invulnerable;
    float scale;

public:
    WaterBossLife(int LIFE);
    virtual ~WaterBossLife() {}
    void damage(float damage, float mul);
    void initComponent();
    void render();
};


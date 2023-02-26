#pragma once
#include "../utils/Entity.h"
#include "../utils/Component.h"
#include "Transform.h"

class LimitBEU : public Component{
private:
    Transform* tr_ = nullptr;
    float downLimit, topLimit;
public:
    LimitBEU();
    void initComponent();
    void update();
};
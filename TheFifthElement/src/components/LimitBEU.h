#pragma once
#include "../utils/Entity.h"
#include "../utils/Component.h"
#include "Transform.h"
#include "JumpComponent.h"

class LimitBEU : public Component {
private:
    Transform* tr_ = nullptr;
    JumpComponent* jmp_ = nullptr;
    float downLimit, topLimit;
    bool stCam_;
public:
    LimitBEU(bool staticCamera = false);
    void initComponent();
    void update();
};
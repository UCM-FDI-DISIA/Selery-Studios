#pragma once
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"


class JumpComponent : public Component {
private:
    Transform* tr_ = nullptr;
    bool canJump = true;

public:
    JumpComponent();
    void initComponent();
    void update();

    void jump();
    bool isJumpEnable() { return canJump; }
};

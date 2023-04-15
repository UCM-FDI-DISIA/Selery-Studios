#pragma once
#include "../utils/Entity.h"
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"
#include "FramedImage.h"

class JumpComponent : public Component {
private:
    Transform* tr_ = nullptr;
    bool canJump = true;
    bool ctr = false;
    float groundHeigth, jumpHeigth;
    float jumpSpeed = 1;

public:
    JumpComponent();
    ~JumpComponent();
    void initComponent();
    void update();

    void jump();
    bool isJumpEnabled() { return canJump; }
};

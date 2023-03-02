#pragma once
#include "../utils/Entity.h"
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"
#include "Image.h"

class JumpComponent : public Component {
private:
    Transform* tr_ = nullptr;
    Image* im_ = nullptr;
    bool canJump = true;
    bool ctr = false;
    float jumpHeigth;
    float jumpSpeed = 1;

public:
    JumpComponent();
    ~JumpComponent();
    void initComponent();
    void update();

    void jump();
    bool isJumpEnable() { return canJump; }
};

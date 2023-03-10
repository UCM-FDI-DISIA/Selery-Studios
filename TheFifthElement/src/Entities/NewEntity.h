#pragma once
#include "../utils/Entity.h"
#include "../sdlutils/Texture.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../utils/Vector2D.h"
class NewEntity :
    public Entity
{
public:
    NewEntity(string t, float w, float h, Vector2D pos, int nframes, bool flip, float size = WIN_WIDTH / 900) {
        addComponent<Transform>(TRANSFORM_H, pos, w/nframes, h, size);
        Texture* t_ = &SDLUtils::instance()->images().at(t);
        Image* im_ = addComponent<Image>(IMAGE_H, t_, nframes, nframes, 0, w / nframes, h);
        if (flip) im_->setFlip(SDL_FLIP_HORIZONTAL);
    }
};


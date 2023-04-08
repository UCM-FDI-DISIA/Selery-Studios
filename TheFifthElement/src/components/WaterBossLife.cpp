#include "WaterBossLife.h"

WaterBossLife::WaterBossLife(int LIFE) {
    maxLife = LIFE;
    life = maxLife;
}

void WaterBossLife::initComponent() {
    scale = WIN_WIDTH / 900;
    tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
    im_ = ent_->getComponent<Image>(IMAGE_H);
    backTexture_ = &SDLUtils::instance()->images().at("Water_LifeBarBack");
    barTexture_ = &SDLUtils::instance()->images().at("Water_LifeBar");
    borderTexture_ = &SDLUtils::instance()->images().at("Water_LifeBarBorder");
    barWidth_ = backWidth_ = borderWidth_ = 300 * scale;
    barHeight_ = backHeight_ = borderHeight_ = 50 * scale;
}

void WaterBossLife::damage(float damage, float mul) {
    if (!invulnerable) {
        life -= damage * mul;
        if (life <= 0) {
            im_->setAnim(true, 4, 15, 0, 15, false);
            ent_->removeComponent(WATERBOSSIA_H);
        }
        else im_->setAnim(true, 3, 7, 0, 7);
    }
}

void WaterBossLife::render() {
    SDL_Rect src = { 0, 0, 400, 50 };

    SDL_Rect dest;
    dest.x = 8 * (WIN_WIDTH / 13);
    dest.y = 35 * scale;
    dest.h = backHeight_;
    dest.w = backWidth_;
    backTexture_->render(src, dest);

    dest.x = 8 * (WIN_WIDTH / 13);
    dest.h = barHeight_;
    dest.w = barWidth_;
    barTexture_->render(src, dest);

    dest.x = 8 * (WIN_WIDTH / 13);
    dest.h = borderHeight_;
    dest.w = borderWidth_;
    borderTexture_->render(src, dest);
}
#include "WaterBossLife.h"
#include "../states/BeatEmUpState.h"

WaterBossLife::WaterBossLife(int LIFE) {
    maxLife = LIFE;
    life = maxLife;
}

void WaterBossLife::initComponent() {
    scale = WIN_WIDTH / 900;
    tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
    im_ = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
    backTexture_ = &SDLUtils::instance()->images().at("Water_LifeBarBack");
    barTexture_ = &SDLUtils::instance()->images().at("Water_LifeBar");
    borderTexture_ = &SDLUtils::instance()->images().at("Water_LifeBarBorder");
    barWidth_ = backWidth_ = borderWidth_ = 300 * scale;
    barHeight_ = backHeight_ = borderHeight_ = 50 * scale;
    invulnerable = true;
}

void WaterBossLife::damage(float damage, float mul) {
    if (!invulnerable && !hit_) {
        life -= damage * mul;
        barWidth_ = ((life * backWidth_) / maxLife);
        if (life <= 0) {
            //im_->setAnim("waterBoss_death", 16, true);
            im_->setAnim("waterBoss", 16, true, 4);
            ////im_->setAnim(true, 4, 15, 0, 15, false);
            im_->setIsAnimUnstoppable(false);
            //im_->setAnimPlaying(false);
            //ent_->removeComponent(WATERBOSSIA_H);
            die_ = true;
        }
        else
        {
            //im_->setAnim("waterBoss", 16, true, 3);
            //im_->setAnim("waterBoss_hit", 7, true);
            ////im_->setAnim(true, 3, 7, 0, 7);
            //meter sonido de daño
            hit_ = true;
            cont_ = 0;
        }
    }
}

void WaterBossLife::update() {
    if (die_ && !im_->isAnimPlaying()) {
        ent_->setAlive(false);
        Quests::instance()->completedQuest("siblings");
        BeatEmUpState* beatemupstate = static_cast<BeatEmUpState*>(mngr_);
        beatemupstate->finishBEU();
    }
    else if (hit_ && cont_ >= 20) hit_ = false;
    cont_++;
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
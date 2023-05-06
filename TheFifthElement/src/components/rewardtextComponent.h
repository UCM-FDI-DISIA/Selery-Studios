#pragma once
#include "../utils/Component.h"
#include "../utils/PropertiesManager.h"
#include "../sdlutils/SDLUtils.h"
#include <string>


class rewardtextComponent :
    public Component
{
private:
    Texture* coinTexture_;
    PropertiesManager* props_;
    Font* f;
    int imgWidth_ = 224, imgHeight_ = 16, frames_ = 14;
    SDL_Color color_ = { 50,50,0 };
    int offsetX_ = 30 * WIN_WIDTH / 900;
    Vector2D pos_;
    std::string rew_;
    double cont_;
    int money_, prevMoney_;

    bool render_;
public:
    rewardtextComponent() {
        if (WIN_WIDTH == 1920)f = &SDLUtils::instance()->fonts().at("TCenturyScale");
        else f = &SDLUtils::instance()->fonts().at("TCentury");

        coinTexture_ = &SDLUtils::instance()->images().at("coin");

        rew_ = "";

        pos_ = Vector2D(WIN_WIDTH/2, WIN_HEIGHT/2 - (25*WIN_HEIGHT / 600));
        money_ = prevMoney_ =  cont_ = 0;
        render_ = false;
    }

    void render() {
        if (render_) {
            SDL_Rect dest = { pos_.getX() + offsetX_, pos_.getY(), (imgWidth_ / frames_) * 2, imgHeight_ * 2 };
            SDL_Rect src;
            src.x = 0;
            src.y = 0;
            src.h = imgHeight_;
            src.w = imgWidth_ / frames_;
            coinTexture_->render(src, dest);

            f->render(SDLUtils::instance()->renderer(), rew_, pos_.getX(), pos_.getY(), color_);
        }
    }

    void update() {
        money_ = props_->instance()->getMoney();
        if (prevMoney_ != money_) 
        { 
            if (money_ - prevMoney_ > 0) rew_ = "+ " + to_string(money_ - prevMoney_);
            else rew_ = to_string(money_ - prevMoney_);
            prevMoney_ = money_;
            cont_ = SDLUtils::instance()->currRealTime();
            render_ = true; 
        }
        else if (render_ && SDLUtils::instance()->currRealTime() - cont_ > 2000) render_ = false;

    }
};


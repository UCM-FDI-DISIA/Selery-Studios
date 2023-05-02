#pragma once
#ifndef TRANSFORM_H_
#define TRANSFORM_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Manager.h"

class Transform : public Component {
private:
    Vector2D position, direction;
    float width, height, rotation_, vel;
    SDL_Rect rect;
    int framesTotales_;
    bool matrix_, demo = false;
    float size_ = 1.0f;
    float scale_ = WIN_WIDTH / 900;
public:
    Transform(Vector2D pos, float w, float h, float size = 1.0f, float velocity = 3):Component() {
        position = pos;
        width = w * WIN_WIDTH / 900 * size;
        height = h * WIN_HEIGHT / 600 * size;
        rotation_ = 0;
        vel = velocity;
        framesTotales_ = 0;
        matrix_ = false;
        size_ = size;
    }
    Transform() {

    }
    // Constructora
    Transform(Vector2D pos, float w, float h, float r, float v, int frames, bool matrix, float size = 1.0f) : Component() {
        position = pos;
        width = w * (WIN_WIDTH / 900) * size;
        height = h * (WIN_HEIGHT / 600) * size;
        rotation_ = r;
        vel = v;
        framesTotales_ = frames;
        matrix_ = matrix;
        size_ = size;
    }

    // Destructora
    virtual ~Transform() { }
    // Devuelve su posicion
    inline Vector2D& getPos() { return position; }
    // Devuelve su velocidad
    inline Vector2D& getDir() { return direction; }
    // Devuelve su ancho
    inline float getW() { return width; }
    // Devuelve su altura
    inline float getH() { return height; }
    // Devuelve su rotacion
    inline float getR() { return rotation_; }

    inline float getVel() { return vel; }

    inline float getSW() { return size_ * WIN_WIDTH/900; }
    inline float getSH() { return size_ * WIN_HEIGHT/600; }

    inline float getSize() { return size_; }

    inline float getScaleW() { return scale_; }

    inline float getScaleH() { return WIN_HEIGHT/600; }

    inline void setR(float valRot) { rotation_ = valRot; }

    inline void setH(float valHei) { height = valHei; }

    inline void setW(float valWid) { width = valWid; }

    inline void setPos(Vector2D Position) { position = Position; }

    inline void setDir(Vector2D dir) { direction = dir; }

    inline void setVel(float veloc) { vel = veloc; }

    inline void setSize(float size) { size_ = size; }

    void render()
    {
        if (!demo) {
            /*if (matrix_)
                rect = build_sdlrect(getPos().getX() + 120, getPos().getY() + 70, (getW() * size_) / (5 * framesTotales_), (getH() * size_) / 2);
            else
            {
                if (framesTotales_ != 0) rect = build_sdlrect(getPos().getX(), getPos().getY(), (getW() * size_) / framesTotales_, (getH() * size_));
                else  rect = build_sdlrect(getPos().getX() + 50, getPos().getY() + 60, 3 * (getW() * size_) / 4, (getH() * size_) / 2);
            }*/
            rect = build_sdlrect(getPos().getX(), getPos().getY(), getW(), getH());
            rect.x -= mngr_->camRect_.x;
            rect.y -= mngr_->camRect_.y;
            SDL_SetRenderDrawColor(sdlutils().renderer(), 255, 0, 255, 0);
            SDL_RenderDrawRect(sdlutils().renderer(), &rect);
            SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 0);

        }
    }
};
#endif
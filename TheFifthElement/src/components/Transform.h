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
 
    bool matrix_, demo = false;
public:
    Transform(Vector2D pos, float w, float h) {
        position = pos;
        width = w;
        height = h;
        rotation_ = 0;
        vel = 0;
       
        matrix_ = false;
    }
    Transform() {

    }
    // Constructora
    Transform(Vector2D pos, float w, float h, float r, float v, int frames, bool matrix) : Component() {
        position = pos;
        width = w;
        height = h;
        rotation_ = r;
        vel = v;
       
        matrix_ = matrix;
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

    inline void setR(float valRot) { rotation_ = valRot; }

    inline void setH(float valHei) { height = valHei; }

    inline void setW(float valWid) { width = valWid; }

    inline void setPos(Vector2D Position) { position = Position; }

    inline void setDir(Vector2D dir) { direction = dir; }
    
    inline void setVel(float veloc) { vel = veloc; }

    void render()
    {
        if (!demo) {
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
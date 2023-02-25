#pragma once
#ifndef TRANSFORM_H_
#define TRANSFORM_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"

class Transform : public Component {
private:
    Vector2D position, direction;
    float width, height, rotation_, vel;
    SDL_Rect rect;
    int framesTotales_;
    bool matrix_, demo = false;
public:
    Transform() {
        //cout << "fdgbxc";
    }
    // Constructora
    Transform(Vector2D pos, float w, float h, float r, float v, int frames, bool matrix) : Component() {
        position = pos;
        width = w;
        height = h;
        rotation_ = r;
        vel = v;
        framesTotales_ = frames;
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
            if (matrix_)
                rect = build_sdlrect(getPos().getX() + 120, getPos().getY() + 70, getW() / (5 * framesTotales_), getH() / 2);
            else
            {
                if (framesTotales_ != 0) rect = build_sdlrect(getPos().getX(), getPos().getY(), getW() / framesTotales_, getH());
                else  rect = build_sdlrect(getPos().getX() + 50, getPos().getY() + 60, 3 * getW() / 4, getH() / 2);
            }
            SDL_SetRenderDrawColor(sdlutils().renderer(), 255, 0, 255, 0);
            SDL_RenderDrawRect(sdlutils().renderer(), &rect);
            SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 0);
        }
    }
};
#endif
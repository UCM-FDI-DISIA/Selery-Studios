#pragma once
#ifndef ATTACKBOXCOMPONENT_H_
#define ATTACKBOXCOMPONENT_H_
#include "../utils/Vector2D.h"
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "../GameManager.h"
#include "AnimationEnemyBEUComponent.h"
#include "SkinBEUComponent.h"



//Este método es el usado a la hora de crear rectángulos cuando golpeamos en el modo BeatEmUp y funciona de la siguiente manera:
//Este componente tiene una referencia al componente Image, el cual gestiona las animaciones.
//En el update de este componente se llama al metodo handleBoxes, el cual comprueba, dependiendo de nuestro personaje, si se está reproduciendo una animación de golpeo, crea una caja y la setea
// 
//Podemos mover la caja de dos manera, en linea recta o trazando una circunferencia:
// 
//Para moverla en linea recta necesitamos una direccion y una velocidad 
// 
//En circulos es un poco mas complejo:
//estos valores al crear la caja no son importantes (si usamos el movimiento circular), los únicos importantes son el ancho y el alto,
// y también le asigna el ángulo donde empezará su recorrido
//Tras crearse, esta se actualizará  a través del método moveBoxCurve, el cual recibe el arco de la circunferencia, el centro, la velocidad, el angulo anteriormente mencionado, el angulo limite y la dirección

class BeatEmUpState;
class Image;
class AttackBoxComponent : public Component {
private:
    Transform* entityTr = nullptr;
    vector<SDL_Rect> boxes;
    float angles[100];
    SDL_Rect box, box2;
    Image* im_;
    AnimationEnemyBEUComponent* anim_;
    SkinBEUComponent* sk_;
    float width, height, boxTime, timerExecution, angle, way, stoppingAngle;
    bool boxCreated = false;
    bool actualized = false;
    bool isPlayer;
    string type;
public:
    AttackBoxComponent();
    virtual ~AttackBoxComponent() {}
    void render();
    void update();
    void initComponent();
    void handleBoxes();
    void moveBox(SDL_Rect& box, Vector2D direction, float vel);
    void moveBoxCurve(SDL_Rect& box, float radio, Vector2D posCenter, float vel, float& angle, float stoppingAngle, int way);


};
#endif
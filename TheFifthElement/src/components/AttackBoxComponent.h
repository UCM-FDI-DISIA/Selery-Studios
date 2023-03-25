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



//Este m�todo es el usado a la hora de crear rect�ngulos cuando golpeamos en el modo BeatEmUp y funciona de la siguiente manera:
//Este componente tiene una referencia al componente Image, el cual gestiona las animaciones.
//En el update de este componente se llama al metodo handleBoxes, el cual comprueba, dependiendo de nuestro personaje, si se est� reproduciendo una animaci�n de golpeo, crea una caja y la setea
// 
//Podemos mover la caja de dos manera, en linea recta o trazando una circunferencia:
// 
//Para moverla en linea recta necesitamos una direccion y una velocidad 
// 
//En circulos es un poco mas complejo:
//estos valores al crear la caja no son importantes (si usamos el movimiento circular), los �nicos importantes son el ancho y el alto,
// y tambi�n le asigna el �ngulo donde empezar� su recorrido
//Tras crearse, esta se actualizar�  a trav�s del m�todo moveBoxCurve, el cual recibe el arco de la circunferencia, el centro, la velocidad, el angulo anteriormente mencionado, el angulo limite y la direcci�n

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
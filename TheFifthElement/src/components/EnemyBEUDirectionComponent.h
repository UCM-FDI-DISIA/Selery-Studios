#pragma once
#include "../utils/Component.h"
#include "MovementComponent.h"
#include "Transform.h"
#include "../utils/Vector2D.h"
#include "../Entities/PlayerBEU.h"
#include "Image.h"

class EnemyBEUDirectionComponent :
    public Component
{
public:
    EnemyBEUDirectionComponent(PlayerBEU* p, string type);
    void initComponent();
    void update();
    void changeDir(Vector2D d);
private:

    MovementComponent* mov_;
    Transform* tr_;
    Vector2D dir_;
   
    PlayerBEU* player_;
    Transform* playerTr_;

    Image* im_;
    Texture* t_;
    string enemy_;


    int cont = 1000;
    bool izq = true;
    float distance_ = 0.0f;

    string type_;
};


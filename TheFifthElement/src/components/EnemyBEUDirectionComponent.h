#pragma once
#include "../utils/Component.h"
#include "MovementComponent.h"
#include "Transform.h"
#include "../utils/Vector2D.h"
#include "../Entities/PlayerBEU.h"

class EnemyBEUDirectionComponent :
    public Component
{
public:
    EnemyBEUDirectionComponent(PlayerBEU* p, string type);
    void initComponent();
    void update();
    void changeDir(Vector2D d);
    void stop(bool s);
private:

    float screenWidth_ = 750, screenHeight_ = 200;

    MovementComponent* mov_;
    Transform* tr_;
    Vector2D dir_;
   
    PlayerBEU* player_;
    Transform* playerTr_;

    Texture* t_;
    string enemy_;


    int cont = 1000;
    bool izq = true;
    float distance_ = 100.0f;
    float speed = 0.0f;

    string type_;

    bool stop_ = false;
};


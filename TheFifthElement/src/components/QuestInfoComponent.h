#pragma once
#include <string>
#include "../utils/Component.h"
#include <vector>
#include "../sdlutils/Font.h"
#include "../utils/ecs.h"
#include "../sdlutils/SDLUtils.h"
#include <sstream>
#include "../utils/PropertiesManager.h"

class QuestInfoComponent :  public Component
{
private:
    string name_;// nombre de la quest
    string text_;// descripcion de la quest
    string reward_;// tipo de recompesa (hermano, monedas...)

    int coins_;// numero de monedas de recompensa

    bool alive_;
    bool end;

    bool init_;
    int cont_, fin, linea_, currFase, maxFase;

    vector<string> conespacios;
    string out;

    Font* font_;
    Texture* t_;
public:
    QuestInfoComponent(string Name, string text, string reward, int coin, int fases);

    void update();

    void render();
    void setDialogue(string i);

    string getName() { return name_; }
    string getText() { return text_; }
    string getReward() { return reward_; }
    int getCoins() { return coins_; }
    bool getAlive() { return alive_; }
    int getCurrFase() { return currFase; }
    int getMaxFase() { return maxFase; }

  
    void setAlive(bool b)
    {
        if (!b) setDialogue("end");
        alive_ = b;
    }
};

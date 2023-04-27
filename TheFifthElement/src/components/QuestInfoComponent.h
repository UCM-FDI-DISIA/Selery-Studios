#pragma once
#include <string>
#include "../utils/Component.h"
#include <vector>
#include "../sdlutils/Font.h"
#include "../utils/ecs.h"
#include "../sdlutils/SDLUtils.h"
#include <sstream>
#include "../GameManager.h"
#include "../utils/PropertiesManager.h"

class QuestInfoComponent :
    public Component
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
    QuestInfoComponent(string Name, string text, string reward, int coins = 0, int fases = 0) {
        name_ = Name;
        text_ = text;
        reward_ = reward;
        maxFase = fases;
        currFase = 0;

        if (reward == "monedas")coins_ = coins;

        init_ = true;
        alive_ = true;
        end = false;
        cont_ = 0;
        linea_ = 0;

        font_ = &SDLUtils::instance()->fonts().at("TCentury");
        t_ = &SDLUtils::instance()->images().at("papiro");

        setDialogue("init");
    }

    void update() {
        if (init_ || !alive_) {
            cont_++;
            if (cont_ < fin)
            {
                out += conespacios[linea_][cont_];
            }
            else if (cont_ >= fin + 100) {
                if (init_) { init_ = false;}
                else
                {
                    if (end) ent_->setAlive(false);
                    else 
                    { 
                        if (currFase == maxFase)setDialogue("reward");
                        else alive_ = true;
                    }
                }
            }
        }
    }

    void render() {
        if (init_ || !alive_) {
            Vector2D a;
            if (WIN_WIDTH == 1920) a = Vector2D(600, 0);
            else  a = Vector2D(100, 0);
            SDL_Rect dest = build_sdlrect(a, DIALOGUE_WIDTH, DIALOGUE_HEIGHT);
            t_->render(dest, 0);

            if (WIN_WIDTH == 1920) a = Vector2D(750, 150);
            else a = Vector2D(250, 150);
            font_->render(GameManager::instance()->getRenderer(), out, a.getX(), a.getY(), { 50,50,0 });
        }
    }

    void setDialogue(string i) {
        string s;
        if (i == "init") 
        { 
            if(maxFase > 0) s = "NUEVA QUEST: " + text_ + " " + to_string(currFase) + "/" + to_string(maxFase);
            else s = "NUEVA QUEST: " + text_;
        }
        else if (i == "end") 
        { 
            currFase++;
            if (maxFase > 0)s = "COMPLETADA: " + text_ + " " + to_string(currFase) + "/" + to_string(maxFase);
            else s = "COMPLETADA: " + text_;
        }
        else {
            if (reward_ == "monedas") 
            { 
                s = "RECOMPENSA: " + to_string(coins_) + " monedas"; 
                PropertiesManager::instance()->addMoney(coins_);// añade las monedas
            }
            else 
            { 
                if (reward_ == "Desbloqueo de zona");// desbloquear zona
                s = "RECOMPENSA: " + reward_; 
            }
            end = true;
        }

        stringstream aux(s);
        string segment;
        while (conespacios.size() != 0)conespacios.pop_back();
        while (std::getline(aux, segment, '$')) conespacios.push_back(segment);

        cont_ = 0;
        linea_ = 0;
        out = conespacios[0][0];
        fin = conespacios[0].size();
    }

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

#include "QuestInfoComponent.h"
#include "../states/TopDownState.h"
#include "../utils/Manager.h"
#include "../states/GameStateMachine.h"

QuestInfoComponent::QuestInfoComponent(string Name, string text, string reward, TopDownState* tp, int coins=0 , int fases=0 ) {
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

    topDown_ = tp;

    isThisQuest = !topDown_->activeQuest;// si no hay quest activa se ejecuta esta
    topDown_->activeQuest = true;// si esta va a ser la quest activa avisa de que está activa

   // if(isThisQuest)setDialogue("init");
}

void  QuestInfoComponent::update() {
   // if (!topDown_->activeQuest) isThisQuest = true;
    if ((!topDown_->activeQuest || isThisQuest) && (init_ || !alive_)) {
        if (init_ && cont_ == 0)setDialogue("init");
        cont_++;
        if (cont_ < fin)
        {
            out += conespacios[linea_][cont_];
        }
        else if (cont_ >= fin + 100) {
            if (init_) { init_ = false; topDown_->activeQuest = isThisQuest = false; }
            else
            {
                if (end) { ent_->setAlive(false); topDown_->activeQuest = isThisQuest = false;}
                else 
                { 
                    if (currFase == maxFase)setDialogue("reward");
                    else { alive_ = true; topDown_->activeQuest = isThisQuest = false;}
                }
            }
        }
    }
}

    void QuestInfoComponent::render() {
        if ((!topDown_->activeQuest || isThisQuest) && (init_ || !alive_)) {
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

    void QuestInfoComponent::setDialogue(string i) {
        topDown_->activeQuest = true;
        isThisQuest = true;
        string s;
        if (i == "init") 
        { 
            if(maxFase > 0) s = "NEW QUEST: " + text_ + " " + to_string(currFase) + "/" + to_string(maxFase);
            else s = "NEW QUEST: " + text_;
        }
        else if (i == "end") 
        { 
            currFase++;
            if (maxFase > 0)s = "COMPLETED: " + text_ + " " + to_string(currFase) + "/" + to_string(maxFase);
            else s = "COMPLETED: " + text_;
        }
        else {
            if (reward_ == "monedas") 
            { 
                s = "REWARD: " + to_string(coins_) + " monedas"; 
                PropertiesManager::instance()->addMoney(coins_);// añade las monedas
            }
            else 
            { 
                s = "REWARD: " + reward_; 
              if (reward_ == "Area unlock")  static_cast<TopDownState*>(GameStateMachine::instance()->state())->desbloqueoZona();


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

   

#pragma once
#include "Quests.h"
#include "utils/Manager.h"
#include "states/TopDownState.h"

void Quests::pushElement(Entity* q) { quests.push_back(q); }
void Quests::completedQuest(string nombre) {
    auto it = quests.begin();
    bool found = false;
    while (!found && it != quests.end()) {
        QuestInfoComponent* q_ = it.operator*()->getComponent<QuestInfoComponent>(QUESTINFOCOMPONENT_H);
        if (q_->getName() == nombre) { q_->setAlive(false); found = true; }
        ++it;
    }
}

void Quests::actQuests() {// actualiza las quests
    for (auto it = quests.begin(); it != quests.end();) {
        QuestInfoComponent* q_ = it.operator*()->getComponent<QuestInfoComponent>(QUESTINFOCOMPONENT_H);
        if (!q_->getAlive() && q_->getCurrFase() == q_->getMaxFase())
        {
            auto aux = it;
            it = ++it;
            quests.erase(aux);
        }
        else ++it;
    }
}

void Quests::renderQuestList() {
    Texture* t_ = &SDLUtils::instance()->images().at("papiro");
    Font* font_ = &SDLUtils::instance()->fonts().at("TCentury");
    Vector2D a;
    int w, h;

    if (WIN_WIDTH == 1920) {
        a = Vector2D(100, 0);
        w = 500;
        h = 900;
    }
    else {
        a = Vector2D(0, 0);
        w = 400;
        h = 480;
    }
    SDL_Rect dest = build_sdlrect(a, w, h);
    t_->render(dest, 0);

    if (quests.size() == 0) {
        string s;
        if (WIN_WIDTH == 1920)
        {
            a = Vector2D(200, 300);
            s = "    NO TIENES QUESTS PENDIENTES";
        }
        else
        {
            a = Vector2D(85, 170);
            s = "NO TIENES QUESTS PENDIENTES";
        }
        font_->render(GameManager::instance()->getRenderer(), s, a.getX(), a.getY(), { 50,50,0 });
    }
    else {
        int y1 = 310, y2 = 170, i = 1;

        for (auto it = quests.begin(); it != quests.end(); ++it) {
            QuestInfoComponent* q_ = it.operator*()->getComponent<QuestInfoComponent>(QUESTINFOCOMPONENT_H);
            if (WIN_WIDTH == 1920) a = Vector2D(210, y1);
            else a = Vector2D(85, y2);
            string s;
            if (q_->getMaxFase() == 0)s = to_string(i) + ". " + q_->getText();
            else s = to_string(i) + ". " + q_->getText() + " " + to_string(q_->getCurrFase()) +
                "/" + to_string(q_->getMaxFase());
            font_->render(GameManager::instance()->getRenderer(), s, a.getX(), a.getY(), { 50,50,0 });

            y1 += 25;
            y2 += 25;
            i++;
        }
    }

    if (WIN_WIDTH == 1920) a = Vector2D(320, 600);
    else a = Vector2D(150, 300);
    string s = "Press X to close.";
    font_->render(GameManager::instance()->getRenderer(), s, a.getX(), a.getY(), { 50,50,0 });
}



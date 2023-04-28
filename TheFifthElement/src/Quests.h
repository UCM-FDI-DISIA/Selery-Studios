#pragma once
#include "utils/Singleton.h"
#include "components/QuestInfoComponent.h"
class Quests :
    public Singleton<Quests>
{friend Singleton<Quests>;
private:
    list<Entity*> quests;
public:
    void pushElement(Entity* q);
    void completedQuest(string nombre);

    void actQuests();

    void renderQuestList();
};


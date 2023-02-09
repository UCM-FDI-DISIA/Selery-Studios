#pragma once
#include <vector>
#include "Entity.h"
#include "Singleton.h"
using namespace std;

class Manager:public Singleton <Manager> {
protected:
	vector<Entity*> ents_;
public:

	Manager();
	virtual ~Manager();
	Entity* addEntity();
	void refresh();
	void update();
	void render();

};

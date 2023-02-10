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
	template<typename T>
	Entity* addEntity(T* e) {
		e->setAlive(true);
		ents_.push_back(e);
		return e;
	}
	virtual void refresh();
	virtual void update();
	virtual void render();
	virtual void handleEvents() {};
	virtual string getStateID() { return "nothing"; };

};

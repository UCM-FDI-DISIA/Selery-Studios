#pragma once
#include <vector>
#include "Entity.h"
#include "Singleton.h"
#include "../utils/Constants.h"

using namespace std;

class Manager:public Singleton <Manager> {
protected:
	vector<Entity*> ents_;
public:
	Manager();
	virtual ~Manager();
	template<typename T>
	T* addEntity(T* e) {
		e->setAlive(true);
		e->setContext(this);
		e->initEntity();
		ents_.push_back(e);
		return e;
	}
	template<typename T>
	Entity* addEntity(T* e) {
		e->setAlive(true);
		e->setContext(this);
		e->initEntity();
		ents_.push_back(e);
		return e;
	}
	virtual void refresh();
	virtual void update();
	virtual void render();
	virtual void handleEvents() {};
	virtual string getStateID() = 0;
	inline const auto& getEntities() { return ents_; }
	static SDL_Rect camRect_;
};

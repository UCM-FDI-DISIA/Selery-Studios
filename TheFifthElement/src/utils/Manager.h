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

	Entity* addEntity() {
		Entity* e = new Entity();
		e->setAlive(true);
		e->setContext(this);
		ents_.push_back(e);
		return e;
	}

	template<typename T>
	Entity* addEntity(T* e) {
		e->setAlive(true);
		e->setContext(this);
		//e->initEntity();
		ents_.push_back(e);
		return e;
	}

	template<typename T>
	Entity* addEntityAtI(T* e, int i) {
		e->setAlive(true);
		e->setContext(this);
		//e->initEntity();
		ents_.insert(ents_.begin() + i, e);
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

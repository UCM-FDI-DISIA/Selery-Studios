#pragma once
#include <SDL.h>
class Entity;
class Manager;
class Component
{
protected:
	Entity* ent_;
	Manager* mngr_;
public:
	Component() : ent_(), mngr_() {}
	virtual ~Component() {}
	inline void setContext(Entity* ent, Manager* mngr) {
		ent_ = ent;
		mngr_ = mngr;
	}

	virtual void initComponent() { }
	virtual void update() { }
	virtual void render() { }
	virtual void handleEvent(SDL_Event event) { }

};


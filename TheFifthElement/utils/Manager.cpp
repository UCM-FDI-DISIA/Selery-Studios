#include "Manager.h"

Manager::Manager() {
	ents_.reserve(100);
	/*for (auto& grpEnts : entsByGroup_) {
		grpEnts.reserve(100);
	}*///groups
}


Manager::~Manager() {
	for (auto e : ents_) {
		delete e;
	}
}

Entity* Manager::addEntity() {
	Entity* e = new Entity();
	e->setAlive(true);
	ents_.push_back(e);
	return e;
}

void Manager::refresh() {
	ents_.erase(
		remove_if(ents_.begin(), ents_.end(), [](Entity* e) {
			if (e->isAlive()) {
				return false;
			}
			else {
				delete e;
				return true;
			}
			}), 
		ents_.end());
}

void Manager::update() {
	auto n = ents_.size();
	for (auto i = 0; i < n; i++)
		ents_[i]->update();
}

void Manager::render() {
	auto n = ents_.size();
	for (auto i = 0; i < n; i++)
		ents_[i]->render();
}

	


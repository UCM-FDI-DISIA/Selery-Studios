#include "Manager.h"
SDL_Rect Manager::camRect_ = { 0,0, WIN_WIDTH, WIN_HEIGHT };
Manager::Manager() {
	ents_.reserve(100);
}


Manager::~Manager() {
	for (auto e : ents_) {
		delete e;
	}
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
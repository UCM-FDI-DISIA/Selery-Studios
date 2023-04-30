#pragma once
#include "utils/Singleton.h"
#include "utils/Entity.h"
#include "components/Trigger.h"
#include <vector>
class Puzzle1 : public Singleton<Puzzle1>
{ friend Singleton<Puzzle1>;
	private:
		vector<int> orden;
		vector<Entity*> copasv;
		bool finish = false;
	public:
		void copas(vector<Entity*> copas_) {
			copasv = copas_;
		}
		void add(int a) {
			if (!finish) {
				if (orden.size() == 0) orden.push_back(a);
				else if (orden[orden.size() - 1] == a - 1) {
					//es la siguiente copa
					orden.push_back(a);
					if (orden.size() == 4) {
						finish = true;
						copasv[0]->getComponent<Trigger>(TRIGGER_H)->desbloqueozona();
					}
				}
				else {
					orden.clear();
					//cambia la animacion de todos los 
					for (int i = 0; i < copasv.size(); i++) {
						copasv[i]->getComponent<Trigger>(TRIGGER_H)->setTexture();

					}
				}
			}
			
		}
};


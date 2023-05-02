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
		vector<Entity*> pilares;
		vector<int> pilarespositiony{0,0,0,0};
		bool finish = false;
		bool finish2 = false;
	public:
		void copas(vector<Entity*> copas_) {
			copasv = copas_;
		}
		void pilar(vector<Entity*> pilar_) {
			pilares = pilar_;
		}
		void add(int a) {
			
				if (orden.size() == 0) orden.push_back(a);
				else if (orden[orden.size() - 1] == a - 1) {
					if (!finish) {
						//es la siguiente copa
						orden.push_back(a);
						if (orden.size() == 4) {
							finish = true;
							copasv[0]->getComponent<Trigger>(TRIGGER_H)->desbloqueozona();
						}
					}
				}
				else {
					orden.clear();
					if (!finish2) {

						//cambia la animacion de todos los 
						for (int i = 0; i < copasv.size(); i++) {
							copasv[i]->getComponent<Trigger>(TRIGGER_H)->setTexture();

						}
					}
				}
			
			
		}
		void move(int a) {
			if (!finish) {
				pilarespositiony[a - 1]++;
				if (pilarespositiony[a - 1] > 5) {
					for (int i = 0; i < 4; i++) {
						pilares[i]->getComponent<Trigger>(TRIGGER_H)->changemove(pilarespositiony[i]); //reseteo de las posiciones
						pilarespositiony[i] = 0; //reseteo de los valores

					}
				}
				else if (pilarespositiony[a - 1] == 5) {
					if (pilarespositiony[0] == 5 && pilarespositiony[1] == 5 && pilarespositiony[2] == 5 && pilarespositiony[3] == 5) {
						pilares[0]->getComponent<Trigger>(TRIGGER_H)->desbloqueozona();
						finish2 = true;
					}

				}
			}
		}
		bool fin() { return  finish2; }
};


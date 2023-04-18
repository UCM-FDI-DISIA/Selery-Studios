#pragma once
#include "Singleton.h"
#include <vector>
#include "Entity.h"
/*Clase para manejar las propiedades de fuerza 
y vida al comprar en la tienda. Consta de dos 
vectores y un entero, m�todos getter y setter para modificar/obtener
los valores requeridos y m�todos para la econom�a*/
class PropertiesManager : public Singleton<PropertiesManager> {

	friend Singleton<PropertiesManager>;
	
private: 
	vector<float>strength;
	vector<float>lives;
	int currentMoney_;
	PropertiesManager() {
		for (int i = 0; i < 4; i++) {
			strength.push_back(1.0f);
			lives.push_back((int)10);
			currentMoney_ = 500; // poner a 0 en versi�n final
		}
	}
	
public: 	
	
	virtual ~PropertiesManager() {
		
	}
	void setStrength(int i, float cuantity) { strength[i] += cuantity; }
	void setLives(int i, float cuantity) { lives[i] += cuantity; }
	
	float getStrength(int i) { return strength[i]; }
	float getLives(int i) { return lives[i]; }
	float getMoney() { return currentMoney_; }

	inline void addMoney(int cuantity) {
		if (cuantity + currentMoney_ < MAX_MONEY) {
			currentMoney_ += cuantity;		
		}
	}
	bool can_Substract(int cuantity) {
		bool a = false;
		
		if (cuantity <= currentMoney_) {
			currentMoney_ -= cuantity;
			a = true;
		}
		return a;
	}

};

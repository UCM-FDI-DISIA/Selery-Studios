#pragma once
#include "Singleton.h"
#include <vector>
#include "Entity.h"
/*Clase para manejar las propiedades de fuerza 
y vida al comprar en la tienda. Consta de dos 
vectores y métodos getter y setter para modificar/obtener
los valores requeridos*/
class PropertiesManager : public Singleton<PropertiesManager> {

	friend Singleton<PropertiesManager>;
	
private: 
	vector<float>strength;
	vector<float>lives;
	PropertiesManager() {
		for (int i = 0; i < 4; i++) {
			strength.push_back(1.0f);
			lives.push_back((int)10);
		}
	}
	
public: 	
	
	virtual ~PropertiesManager() {
		
	}
	void setStrength(int i, float cuantity) { strength[i] += cuantity; }
	void setLives(int i, float cuantity) { lives[i] += cuantity; }
	float getStrength(int i) { return strength[i]; }
	float getLives(int i) { return lives[i]; }
	
};

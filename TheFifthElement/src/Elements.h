#pragma once
#include "./utils/Singleton.h"
class Elements :  public Singleton <Elements> {
	friend Singleton<Elements>;

private:
	bool elements[4];

	Elements() {
		elements[0] = true; // aire
		elements[1] = false; // fuego
		elements[2] = false; // agua
		elements[3] = false; // tierra
	}

public:
	bool getElementsList(int i) { return elements[i]; }
	void setAir(bool b = true) { elements[0] = b; }
	void setFire (bool b = true) { elements[1] = b; }
	void setWater (bool b = true) { elements[2] = b; }
	void setEarth (bool b = true) { elements[3] = b; }
	void initBlock(){
		elements[1] = false; // fuego
		elements[2] = false; // agua
		elements[3] = false; // tierra
	}
	bool getAir() { return elements[0]; }
	bool getFire() { return elements[1]; }
	bool getWater() { return elements[2]; }
	bool getEarth() { return elements[3]; }
};
#pragma once
#include <sstream>
#include <iostream>
#include <string>
#include "../utils/Component.h"
using namespace std;
class  PlayerNPC : public Component
{
private:
	int colnpc = 5;
public:
	PlayerNPC() {

		colnpc = 5;
	}
	virtual ~PlayerNPC() {}
	int getcol() { return colnpc; }
	void setcol() { colnpc =-1; }
	void setcolnpc(int num) { 
		if (colnpc == -1)colnpc = num;  
	}
};

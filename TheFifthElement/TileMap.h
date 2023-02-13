#pragma once
#include "Layer.h"
#include <vector>
using namespace std;
class GameMap
{
private:
	vector<Layer*> map_layers_;
	
public:
	void render();
	void update();

};


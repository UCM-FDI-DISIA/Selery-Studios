#pragma once
#include "../src/utils/Vector2D.h"

class Saving:public Singleton<Saving>
{
private:
	Vector2D position{ 0,0 };
public:
	Vector2D getPos() { return position; }
	void setPos(Vector2D pos) { position = pos; }
	void deletePos() { position = Vector2D(0,0); }
	virtual ~Saving() {};
};

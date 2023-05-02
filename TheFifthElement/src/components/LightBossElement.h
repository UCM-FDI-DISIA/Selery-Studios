#pragma once
#ifndef LIGHTBOSSELEMENT_H_
#define LIGHTBOSSELEMENT_H_
#include "../utils/Component.h"
#include "../utils/ecs.h"

class LightBossElement : public Component
{
public:
	void initComponent() { returning = false; }
	bool getReturning() { return returning; }
	void setReturning() { returning = true; }
private:
	bool returning;
};

#endif 

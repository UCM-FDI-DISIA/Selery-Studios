#pragma once

#include "../utils/Entity.h"
#include "../components/Transform.h"
#include "../utils/Collision.h"
#include "../components/FramedImage.h"

class Trigger : public Component
{
private:
	FramedImage* framed;
	Transform* trans_player;
	SDL_Rect* colision;
	SDL_Rect* player;
	bool istrigger_ = false;
	string name;
public:
	Trigger(string name,Transform* player, Transform* trans_col_, FramedImage* framed_);
	virtual ~Trigger();
	void initComponent();
	void update();
	bool istrigger() { return istrigger_; } //getter para el trigger
	void setTexture();
	void desbloqueozona();
};

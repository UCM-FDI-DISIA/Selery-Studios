#pragma once
#ifndef SHOPCOMPONENT_H
#define SHOPCOMPONENT_H_
#include "../utils/Component.h"
#include "../utils/Vector2D.h"
#include "EconomyComponent.h"
#include "Damage.h"
#include "LifeTD.h"
class DialogueComponent;

class ShopComponent : public Component {

private:
	Vector2D shopPos_;
	
	DialogueComponent* dialog_ = nullptr;

	Transform* playerTr_;

	Texture* shopBackground_ = &SDLUtils::instance()->images().at("ShopBackground");
	Texture* airAvatar_ = &SDLUtils::instance()->images().at("AirAvatar");
	Texture* fireAvatar_ = &SDLUtils::instance()->images().at("FireAvatar");
	Texture* waterAvatar_ = &SDLUtils::instance()->images().at("WaterAvatar");
	Texture* earthAvatar_ = &SDLUtils::instance()->images().at("EarthAvatar");
	Texture* avatarFrame_ = &SDLUtils::instance()->images().at("ShopFrame");
	int avatarOffsetX_ = 30;
	int avatarOffsetY_ = 25;

	int frameOffsetX_ = 30;
	int frameOffsetY_ = 25;

	int backgroundOffsetX_ = 135;
	int backgroundOffsetY_ = 140;


	// Texto mejoras
	int u1 = 0;
	int u2 = 0;
	int u3 = 0;
	int u4 = 0;
	int u5 = 0;
	int u6 = 0;
	int u7 = 0;
	int u8 = 0;
	Font* font_;
	string textUp_;
	int textX;
	int textY;
	int textOffsetX_ = 87;
	int textOffsetY_ = 35;
	SDL_Color color_;

	EconomyComponent* economyComp_;
	int price1_ = 10;
	int price2_ = 10;
	int price3_ = 10;
	int price4_ = 10;
	int price5_ = 10;
	int price6_ = 10;
	int price7_ = 10;
	int price8_ = 10;
	string textCoin_;

	Damage* damage_;
	LifeTD* life_;
	
public:
	ShopComponent(EconomyComponent* economyComp, Damage* damage, LifeTD* life);
	void initComponent();
	void update();
	void render();	
	int increase(int& i);
	void showUpgradeText(int value, int offsetXup, int offsetYup, int offsetXcoin, int offsetYcoin, int price);
	void shopEconomy();
	void showShopBackground();
	void showShopAvatar(Vector2D avatarPos, Vector2D framePos, Texture* avatar, Texture* frame);
	
};
#endif

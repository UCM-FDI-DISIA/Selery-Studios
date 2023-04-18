#pragma once
#ifndef SHOPCOMPONENT_H
#define SHOPCOMPONENT_H_
#include "../utils/Component.h"
#include "../utils/Vector2D.h"
#include "EconomyComponent.h"
#include "DialogueComponent.h"
#include "Damage.h"
#include "LifeTD.h"

class ShopComponent : public Component {

private:
	Vector2D shopPos_ = { 250 * WIN_WIDTH / 900, 100 * WIN_HEIGHT / 600 };
	
	DialogueComponent* dialog_ = nullptr;

	Texture* shopBackground_ = &SDLUtils::instance()->images().at("ShopBackground");
	Texture* airAvatar_ = &SDLUtils::instance()->images().at("AirAvatar");
	Texture* fireAvatar_ = &SDLUtils::instance()->images().at("FireAvatar");
	Texture* waterAvatar_ = &SDLUtils::instance()->images().at("WaterAvatar");
	Texture* earthAvatar_ = &SDLUtils::instance()->images().at("EarthAvatar");
	Texture* avatarFrame_ = &SDLUtils::instance()->images().at("ShopFrame");
	int frameOffsetY_ = 50;

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
	int textX = 300;
	int textY = 270;
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
	void showUpgradeText(int value, int offsetXup, int offsetYup, int offsetXcoin, int offsetYcoin, int price);
	int increase(int& i);
	void shopEconomy();
	void showShopBackground();
	void showShopAvatar(Vector2D avatarPos, Vector2D framePos, Texture* avatar, Texture* frame);
};
#endif

﻿#pragma once
#include "ShopComponent.h"
#include "../states/TopDownState.h"
#include "DialogueComponent.h"

ShopComponent::ShopComponent(EconomyComponent* economyComp, Damage* damage, LifeTD* life) {
    if (WIN_WIDTH / 900 == 1920 / 900)font_ = &SDLUtils::instance()->fonts().at("TCenturyScale");
    else font_ = &SDLUtils::instance()->fonts().at("TCentury");
	color_ = { 0,0,0 };
    economyComp_ = economyComp;
    damage_ = damage;
    life_ = life; 
}

void ShopComponent::initComponent() {  
    dialog_ = ent_->getComponent<DialogueComponent>(DIALOGCOMPONENT_H);  
    playerTr_ = ent_->getComponent<Transform>(TRANSFORM_H);    
}

void ShopComponent::update() {
    if (dialog_->getopenedShop()) 
    {
        shopPos_ = { (playerTr_->getPos().getX() - mngr_->camRect_.x) * WIN_WIDTH / 900 - backgroundOffsetX_, (playerTr_->getPos().getY() - mngr_->camRect_.y) * WIN_HEIGHT / 600 - backgroundOffsetY_ };
    }   
}

void ShopComponent::render() {
    // si la tienda está abierta, renderizamos background, avatares y textos
    if (dialog_->getopenedShop()) {
        showShopBackground();

        showShopAvatar(Vector2D((playerTr_->getPos().getX() - mngr_->camRect_.x) * WIN_WIDTH / 900 + (WIN_WIDTH / 900 * avatarOffsetX_), (playerTr_->getPos().getY() - mngr_->camRect_.y) * WIN_HEIGHT / 600 + avatarOffsetY_), Vector2D((playerTr_->getPos().getX() - mngr_->camRect_.x) * WIN_WIDTH / 900 + frameOffsetX_, (playerTr_->getPos().getY() - mngr_->camRect_.y) * WIN_HEIGHT / 600 + frameOffsetY_), airAvatar_, avatarFrame_);
        showShopAvatar(Vector2D((playerTr_->getPos().getX() - mngr_->camRect_.x) * WIN_WIDTH / 900 + (WIN_WIDTH / 900 * avatarOffsetX_), (50 + playerTr_->getPos().getY() - mngr_->camRect_.y) * WIN_HEIGHT / 600 + avatarOffsetY_), Vector2D((playerTr_->getPos().getX() - mngr_->camRect_.x) * WIN_WIDTH / 900 + (WIN_WIDTH / 900 * frameOffsetX_), (50 + playerTr_->getPos().getY() - mngr_->camRect_.y) * WIN_HEIGHT / 600 + frameOffsetY_), fireAvatar_, avatarFrame_);
        showShopAvatar(Vector2D((playerTr_->getPos().getX() - mngr_->camRect_.x) * WIN_WIDTH / 900 + (WIN_WIDTH / 900 * avatarOffsetX_), (100 + playerTr_->getPos().getY() - mngr_->camRect_.y) * WIN_HEIGHT / 600 + avatarOffsetY_), Vector2D((playerTr_->getPos().getX() - mngr_->camRect_.x) * WIN_WIDTH / 900 + (WIN_WIDTH / 900 * frameOffsetX_), (100 + playerTr_->getPos().getY() - mngr_->camRect_.y) * WIN_HEIGHT / 600 + frameOffsetY_), waterAvatar_, avatarFrame_);
        showShopAvatar(Vector2D((playerTr_->getPos().getX() - mngr_->camRect_.x) * WIN_WIDTH / 900 + (WIN_WIDTH / 900 * avatarOffsetX_), (150 + playerTr_->getPos().getY() - mngr_->camRect_.y) * WIN_HEIGHT / 600 + avatarOffsetY_), Vector2D((playerTr_->getPos().getX() - mngr_->camRect_.x) * WIN_WIDTH / 900 + (WIN_WIDTH / 900 * frameOffsetX_), (150 + playerTr_->getPos().getY() - mngr_->camRect_.y) * WIN_HEIGHT / 600 + frameOffsetY_), earthAvatar_, avatarFrame_);

        showUpgradeText(u1, 0, 0, 90, 0, price1_);
        showUpgradeText(u2, 0, 50, 90, 50, price2_);
        showUpgradeText(u3, 0, 100, 90, 100, price3_);
        showUpgradeText(u4, 0, 150 , 90, 150, price4_);
        showUpgradeText(u5, 250, 0, 170, 0, price5_);
        showUpgradeText(u6, 250, 50, 170, 50, price6_);
        showUpgradeText(u7, 250, 100, 170, 100, price7_);
        showUpgradeText(u8, 250, 150, 170, 150, price8_);
    }

}

// incrementa los valores de las mejoras en la tienda
int ShopComponent::increase(int& i) {
    return i++;
}

// logica para manejar las compras en la tienda
void ShopComponent::shopEconomy() {
    TopDownState* topdownstate = static_cast<TopDownState*>(mngr_);
    if (topdownstate->getShopButton(0)->getBool() && u1 < MAX_UPGRADE && economyComp_->getMoney() >= price1_) { // si el bot�n es clicado(isClicked=true en Button), si "u1" es menor que el m�ximo de mejoras y si nuestro dinero es mayor o igual al precio del art�culo
        purchase_ = true;
        increase(u1); // incremento del valor de mejora
        economyComp_->can_Substract(price1_);// restamos nuestro dinero actual
        price1_ += 10; // actualizamos precio en la tienda
        damage_->addDamage(0, 0.2f); // el 0 corresponde al personaje(en este caso aire), y el 0,2 a la cantidad de daño que aumenta
    }
    else if (topdownstate->getShopButton(1)->getBool() && u2 < MAX_UPGRADE && economyComp_->getMoney() >= price2_) {
        purchase_ = true;
        increase(u2);
        economyComp_->can_Substract(price2_);
        price2_ += 10;
        damage_->addDamage(1, 0.2f);
    }
    else if (topdownstate->getShopButton(2)->getBool() && u3 < MAX_UPGRADE && economyComp_->getMoney() >= price3_) {
        purchase_ = true;
        increase(u3);
        economyComp_->can_Substract(price3_);
        price3_ += 10;
        damage_->addDamage(2, 0.2f);
    }
    else if (topdownstate->getShopButton(3)->getBool() && u4 < MAX_UPGRADE && economyComp_->getMoney() >= price4_) {
        purchase_ = true;
        increase(u4);
        economyComp_->can_Substract(price4_);
        price4_ += 10;
        damage_->addDamage(3, 0.2f);
    }
    else if (topdownstate->getShopButton(4)->getBool() && u5 < MAX_UPGRADE && economyComp_->getMoney() >= price5_) {
        purchase_ = true;
        increase(u5);
        economyComp_->can_Substract(price5_);
        price5_ += 10;
        life_->addLife(0, 5.0f); // el 0 corresponde al personaje(en este caso aire), y el 5 a la cantidad de vida que aumenta
    }
    else if (topdownstate->getShopButton(5)->getBool() && u6 < MAX_UPGRADE && economyComp_->getMoney() >= price6_) {
        purchase_ = true;
        increase(u6);
        economyComp_->can_Substract(price6_);
        price6_ += 10;
        life_->addLife(1, 5.0f);
    }
    else if (topdownstate->getShopButton(6)->getBool() && u7 < MAX_UPGRADE && economyComp_->getMoney() >= price7_) {
        purchase_ = true;
        increase(u7);
        economyComp_->can_Substract(price7_);
        price7_ += 10;
        life_->addLife(2, 5.0f);
    }
    else if (topdownstate->getShopButton(7)->getBool() && u8 < MAX_UPGRADE && economyComp_->getMoney() >= price8_) {
        purchase_ = true;
        increase(u8);
        economyComp_->can_Substract(price8_);
        price8_ += 10;
        life_->addLife(3, 5.0f);
    }
    else {
        purchase_ = false;
    }
}

void ShopComponent::showUpgradeText(int value, int offsetXup, int offsetYup, int offsetXcoin, int offsetYcoin, int price) {
    // Textos mejoras
    textX = (playerTr_->getPos().getX() - mngr_->camRect_.x) * WIN_WIDTH / 900 - textOffsetX_;
    textY = (playerTr_->getPos().getY() - mngr_->camRect_.y) * WIN_HEIGHT / 600 + textOffsetY_;
    textUp_ = std::to_string(value) + "/" + std::to_string(MAX_UPGRADE);
    font_->render(GameManager::instance()->getRenderer(), textUp_, (textX + offsetXup) * WIN_WIDTH / 900,
        (textY + offsetYup) * WIN_HEIGHT / 600, color_);
    // Textos monedas
    textCoin_ = std::to_string(price);
    font_->render(GameManager::instance()->getRenderer(), textCoin_, (textX + offsetXcoin) * WIN_WIDTH / 900,
        (textY + offsetYcoin) * WIN_HEIGHT / 600, color_);
}

void ShopComponent::showShopBackground() {
    SDL_Rect background = build_sdlrect(shopPos_, (SHOP_WIDTH / 2) * WIN_WIDTH / 900, (SHOP_HEIGHT / 2)*WIN_HEIGHT/600);
    shopBackground_->render(background, 0);
}

void ShopComponent::showShopAvatar(Vector2D avatarPos, Vector2D framePos, Texture* avatar, Texture* frame) {
    SDL_Rect frameRect = build_sdlrect(framePos, (SHOP_FRAME_WIDTH / 2) * WIN_WIDTH / 900, (SHOP_FRAME_HEIGHT / 2) * WIN_HEIGHT / 600);
    frame->render(frameRect, 0);
    SDL_Rect avatarRect = build_sdlrect(avatarPos, (AVATAR_WIDTH / 2) * WIN_WIDTH / 900, (AVATAR_HEIGHT / 2) * WIN_HEIGHT / 600);
    avatar->render(avatarRect, 0);
}

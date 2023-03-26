#pragma once
#include "ShopComponent.h"

ShopComponent::ShopComponent() {
	font_ = &SDLUtils::instance()->fonts().at("TCentury");
	color_ = { 0,0,0 };
}

void ShopComponent::initComponent() {
    upturnButtonTr_ = ent_->getComponent<Transform>(TRANSFORM_H);
    dialog_ = ent_->getComponent<DialogueComponent>(DIALOGCOMPONENT_H);
    upturnButtonX = upturnButtonTr_->getPos().getX();
    upturnButtonY = upturnButtonTr_->getPos().getY();
    upturnButtonPos_ = Vector2D(upturnButtonX + upturnButtonOffsetX / 2, upturnButtonY + upturnButtonOffsetY / 2);

    if (dialog_->getopenedShop()) {
        for (int i = 0; i < 4; i++) {
            upturnButton_ = new Entity();
            upturnButton_->setContext(mngr_);
            upturnButtonTr_ = upturnButton_->addComponent<Transform>(TRANSFORM_H, Vector2D(upturnButtonPos_.getX(), upturnButtonY + upturnButtonOffsetY + i * 50), UPTURNBUTTON_WIDTH / 2, UPTURNBUTTON_HEIGHT / 2, 1);
            upturnButtonComp_ = upturnButton_->addComponent<Button>(BUTTON_H, "UPTURN");
            upturnButton_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("UpturnButton"), UPTURNBUTTON_WIDTH, UPTURNBUTTON_HEIGHT, upturnButtonTr_);
            /*economyComp_ = upturnButton_->addComponent<EconomyComponent>(ECONOMYCOMPONENT_H);*/
            mngr_->addEntity(upturnButton_);
            buttons.push_back(upturnButton_);
        }
        for (int i = 0; i < 4; i++) {
            upturnButton_ = new Entity();
            upturnButton_->setContext(mngr_);
            upturnButtonTr_ = upturnButton_->addComponent<Transform>(TRANSFORM_H, Vector2D(upturnButtonPos_.getX() + upturnButtonOffsetX, upturnButtonY + upturnButtonOffsetY + i * 50), UPTURNBUTTON_WIDTH / 2, UPTURNBUTTON_HEIGHT / 2, 1);
            upturnButtonComp_ = upturnButton_->addComponent<Button>(BUTTON_H, "UPTURN");
            upturnButton_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("UpturnButton"), UPTURNBUTTON_WIDTH, UPTURNBUTTON_HEIGHT, upturnButtonTr_);
            /*economyComp_ = upturnButton_->addComponent<EconomyComponent>(ECONOMYCOMPONENT_H);*/
            mngr_->addEntity(upturnButton_);
            buttons.push_back(upturnButton_);
        }
        exitShopButton_ = new Entity();
        exitShopButton_->setContext(mngr_);
        exitShopButtonTr_ = exitShopButton_->addComponent<Transform>(TRANSFORM_H, Vector2D(upturnButtonX + SHOP_WIDTH / 14, upturnButtonY + upturnButtonOffsetY + 300), 557 / 2, 131 / 2, 1);
        exitShopButton_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("ExitShop"), 557, 131, exitShopButtonTr_);
        exitShopButtonComp_ = exitShopButton_->addComponent<Button>(BUTTON_H, "EXITSHOP");
        mngr_->addEntity(exitShopButton_);
    }


    /*upturnButtonComp_ = ent_->getComponent<Button>(BUTTON_H);*/
}

void ShopComponent::update() {
    /*if (dialog_->getopenedShop()) {

        for (auto e : buttons) {
            mngr_->addEntity(e);
        }

    }*/
}

void ShopComponent::handleEvent(SDL_Event event) {
    for (auto e : buttons) {
        e->handleEvent(event);
        /* shopEconomy();*/
    }
    exitShopButtonComp_->handleEvent(event);

}

void ShopComponent::render() {
    if (dialog_->getopenedShop()) {
        showShopBackground();

        showShopAvatar(Vector2D(420, 265), Vector2D(415, 260), airAvatar_, avatarFrame_);
        showShopAvatar(Vector2D(420, 315), Vector2D(415, 310), fireAvatar_, avatarFrame_);
        showShopAvatar(Vector2D(420, 365), Vector2D(415, 360), waterAvatar_, avatarFrame_);
        showShopAvatar(Vector2D(420, 415), Vector2D(415, 410), earthAvatar_, avatarFrame_);

        showUpgradeText(u1, 0, 0, 90, 0, price1_);
        showUpgradeText(u2, 0, 50, 90, 50, price2_);
        showUpgradeText(u3, 0, 100, 90, 100, price3_);
        showUpgradeText(u4, 0, 150, 90, 150, price4_);
        showUpgradeText(u5, 250, 0, 170, 0, price5_);
        showUpgradeText(u6, 250, 50, 170, 50, price6_);
        showUpgradeText(u7, 250, 100, 170, 100, price7_);
        showUpgradeText(u8, 250, 150, 170, 150, price8_);
    }

}

void ShopComponent::showUpgradeText(int value, int offsetXup, int offsetYup, int offsetXcoin, int offsetYcoin, int price) {
    // Textos mejoras
    textUp_ = std::to_string(value) + "/" + std::to_string(MAX_UPGRADE);
    font_->render(GameManager::instance()->getRenderer(), textUp_, textX + offsetXup, textY + offsetYup, color_);
    // Textos monedas
    textCoin_ = std::to_string(price);
    font_->render(GameManager::instance()->getRenderer(), textCoin_, textX + offsetXcoin, textY + offsetYcoin, color_);
}

// incrementa los valores de las mejoras en la tienda
int ShopComponent::increase(int& i) {
    return i++;
}

// l�gica para manejar las compras en la tienda
void ShopComponent::shopEconomy() {
    if (/*upturnButtonComp_->getBool() && */u1 < MAX_UPGRADE && economyComp_->getMoney() >= price1_) { // si el bot�n es clicado(isClicked=true en Button), si "u1" es menor que el m�ximo de mejoras y si nuestro dinero es mayor o igual al precio del art�culo
        increase(u1); // incremento del valor de mejora
        economyComp_->can_Substract(price1_);// restamos nuestro dinero actual
        price1_ += 10; // actualizamos precio en la tienda
        /*damage_->addDamage(1);*/
    }
    else if (/*upturnButtonComp_->getBool() && */u2 < MAX_UPGRADE && economyComp_->getMoney() >= price2_) {
        increase(u2);
        economyComp_->can_Substract(price2_);
        price2_ += 10;
        /*damage_->addDamage(1);*/
    }
    else if (/*upturnButtonComp_->getBool() && */u3 < MAX_UPGRADE && economyComp_->getMoney() >= price3_) {
        increase(u3);
        economyComp_->can_Substract(price3_);
        price3_ += 10;
        /*damage_->addDamage(1);*/
    }
    else if (/*upturnButtonComp_->getBool() && */u4 < MAX_UPGRADE && economyComp_->getMoney() >= price4_) {
        increase(u4);
        economyComp_->can_Substract(price4_);
        price4_ += 10;
        /*damage_->addDamage(1);*/
    }
    else if (/*upturnButtonComp_->getBool() && */u5 < MAX_UPGRADE && economyComp_->getMoney() >= price5_) {
        increase(u5);
        economyComp_->can_Substract(price5_);
        price5_ += 10;
        /*life_->addLife(1);*/
    }
    else if (/*upturnButtonComp_->getBool() && */u6 < MAX_UPGRADE && economyComp_->getMoney() >= price6_) {
        increase(u6);
        economyComp_->can_Substract(price6_);
        price6_ += 10;
        /*life_->addLife(1);*/
    }
    else if (/*upturnButtonComp_->getBool() && */u7 < MAX_UPGRADE && economyComp_->getMoney() >= price7_) {
        increase(u7);
        economyComp_->can_Substract(price7_);
        price7_ += 10;
        /*life_->addLife(1);*/
    }
    else if (/*upturnButtonComp_->getBool() && */u8 < MAX_UPGRADE && economyComp_->getMoney() >= price8_) {
        increase(u8);
        economyComp_->can_Substract(price8_);
        price8_ += 10;
        /*life_->addLife(1);*/
    }
}

void ShopComponent::showShopBackground() {
    SDL_Rect background = build_sdlrect(shopPos_, SHOP_WIDTH / 2, SHOP_HEIGHT / 2);
    shopBackground_->render(background, 0);
}

void ShopComponent::showShopAvatar(Vector2D avatarPos, Vector2D framePos, Texture* avatar, Texture* frame) {
    SDL_Rect frameRect = build_sdlrect(framePos, SHOP_FRAME_WIDTH / 2, SHOP_FRAME_HEIGHT / 2);
    frame->render(frameRect, 0);
    SDL_Rect avatarRect = build_sdlrect(avatarPos, AVATAR_WIDTH / 2, AVATAR_HEIGHT / 2);
    avatar->render(avatarRect, 0);
}

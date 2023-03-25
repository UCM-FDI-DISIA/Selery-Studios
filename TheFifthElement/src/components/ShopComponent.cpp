#pragma once
#include "ShopComponent.h"

ShopComponent::ShopComponent(Entity* upturnButton) {
	upturnButton_ = upturnButton;
	upturnButtonPos_ = Vector2D(5890,850);

	upturnButtonTr_ = upturnButton_->addComponent<Transform>(TRANSFORM_H, upturnButtonPos_, UPTURNBUTTON_WIDTH/2, UPTURNBUTTON_HEIGHT/2, 1);
	upturnButton_->addComponent<Button>(BUTTON_H, "UPTURN");
	upturnButton_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("UpturnButton"));
}

void ShopComponent::initComponent() {

}

void ShopComponent::update() {

}

void ShopComponent::render() {

}
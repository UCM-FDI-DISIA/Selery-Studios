#include "LifeBar.h"

LifeBar::LifeBar(float life, string type, Entity* ent) {
	maxLife_ = life_ = life;
	type_ = type;
	entTransform_ = ent->getComponent<Transform>(TRANSFORM_H);
	barWidth_ = backWidth_ = borderWidth_ = entTransform_->getW()/4;
	barHeight_ = backHeight_ = borderHeight_ = entTransform_->getH()/11;
	chooseTexture();
	setAll();
}

void LifeBar::subLife(float life) {
	life_ = life;
	barWidth_ = ((life_ * backWidth_) / maxLife_);
	//barTransform_->setW(barWidth_);
}

void LifeBar::updatePos()
{
	pos_ = entTransform_->getPos();

	/*barTransform_->setPos(pos_);
	backTransform_->setPos(pos_);
	borderTransform_->setPos(pos_);*/
}

void LifeBar::renderAll() {
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.h = 50;
	src.w = 400;

	SDL_Rect dest;

	dest.x = pos_.getX() + 55;
	dest.y = pos_.getY() + 35;
	dest.h = backHeight_;
	dest.w = backWidth_;
	backTexture_->render(src, dest);


	dest.h = barHeight_;
	dest.w = barWidth_;
	barTexture_->render(src, dest);


	dest.h = borderHeight_;
	dest.w = borderWidth_;
	borderTexture_->render(src, dest);
}

void LifeBar::chooseTexture() {
	if (type_ == "fire") {
		barTexture_ = &SDLUtils::instance()->images().at("Fire_LifeBar");
		backTexture_ = &SDLUtils::instance()->images().at("Fire_LifeBarBack");
		borderTexture_ = &SDLUtils::instance()->images().at("Fire_LifeBarBorder");
	}

	else if (type_ == "wind") {
		barTexture_ = &SDLUtils::instance()->images().at("Air_LifeBar");
		backTexture_ = &SDLUtils::instance()->images().at("Air_LifeBarBack");
		borderTexture_ = &SDLUtils::instance()->images().at("Air_LifeBarBorder");
	}

	else if (type_ == "water") {
		barTexture_ = &SDLUtils::instance()->images().at("Water_LifeBar");
		backTexture_ = &SDLUtils::instance()->images().at("Water_LifeBarBack");
		borderTexture_ = &SDLUtils::instance()->images().at("Water_LifeBarBorder");
	}

	else if (type_ == "earth") {
		barTexture_ = &SDLUtils::instance()->images().at("Earth_LifeBar");
		backTexture_ = &SDLUtils::instance()->images().at("Earth_LifeBarBack");
		borderTexture_ = &SDLUtils::instance()->images().at("Earth_LifeBarBorder");
	}
}

void LifeBar::setAll() {
	pos_ = entTransform_->getPos();
	//SDL_Rect dest = build_sdlrect(entTransform_->getPos(), entTransform_->getW(), entTransform_->getH());

	//borderTransform_ = addComponent<Transform>(TRANSFORM_H, pos_, borderWidth_, borderHeight_);// border
	////borderImage_ = addComponent<Image>(IMAGE_H, borderTexture_, borderWidth_, borderHeight_, borderTransform_, dest);

	//backTransform_ = addComponent<Transform>(TRANSFORM_H, pos_, backWidth_, backHeight_);// back
	////backImage_ = addComponent<Image>(IMAGE_H, backTexture_, backWidth_, backHeight_, backTransform_, dest);

	//barTransform_ = addComponent<Transform>(TRANSFORM_H, pos_, barWidth_, barHeight_);// bar
	////barImage_ = addComponent<Image>(IMAGE_H, barTexture_, barWidth_, barHeight_, barTransform_, dest);

}

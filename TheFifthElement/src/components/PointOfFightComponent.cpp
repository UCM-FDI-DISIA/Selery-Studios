#include "PointOfFightComponent.h"
PointOfFightComponent::PointOfFightComponent(float margin_, float height_) {
	margin = margin_;
	height = height_;
}

void PointOfFightComponent::initComponent() {
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
}

void PointOfFightComponent::update() {
	center = Vector2D(tr_->getPos().getX() + tr_->getW() / 2, tr_->getPos().getY() + tr_->getH() - height);
	pointLeftFight = center - Vector2D(margin, 0);
	pointRightFight = center + Vector2D(margin, 0);
}

void PointOfFightComponent::render() {
	SDL_Rect rect = build_sdlrect(pointLeftFight.getX(), pointLeftFight.getY(), 2, 2);
	rect.x -= mngr_->camRect_.x;
	rect.y -= mngr_->camRect_.y;
	SDL_SetRenderDrawColor(sdlutils().renderer(), 255, 255, 255, 0);
	SDL_RenderDrawRect(sdlutils().renderer(), &rect);
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 0);
	SDL_Rect rect1 = build_sdlrect(pointRightFight.getX(), pointRightFight.getY(), 2, 2);
	rect1.x -= mngr_->camRect_.x;
	rect1.y -= mngr_->camRect_.y;
	SDL_SetRenderDrawColor(sdlutils().renderer(), 255, 255, 255, 0);
	SDL_RenderDrawRect(sdlutils().renderer(), &rect1);
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 0);
}
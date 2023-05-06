#include "ShadowComponent.h"

ShadowComponent::ShadowComponent() {
	
}
ShadowComponent::~ShadowComponent() {
	
}
void ShadowComponent::initComponent() {
	trans_player = ent_->getComponent<Transform>(TRANSFORM_H);
	assert(trans_player != nullptr);
	Jump_player = ent_->getComponent<JumpComponent>(JUMP_H);
	assert(Jump_player != nullptr);
	i = (trans_player->getW() / 2);
 }
void ShadowComponent::update() {

 }
void ShadowComponent::render() {
	if (Jump_player->isJumpEnabled()) {
		rect.x = trans_player->getPos().getX() - mngr_->camRect_.x + (trans_player->getW()) / 2 
			- ((trans_player->getW()) / 2) / 2;
		rect.y = trans_player->getPos().getY() - mngr_->camRect_.y + (trans_player->getH())
			- src_width / 2;
		rect.h = src_width;
		rect.w = (trans_player->getW()) / 2;
		i =init_i= (trans_player->getW() / 2);
	}
	else {
		if (trans_player->getDir().getY() > 0) { //abajo
			++i;
			rect.h = src_width;
			rect.w =  i;
			rect.x = trans_player->getPos().getX() - mngr_->camRect_.x + init_i-(i / 2);
			rect.y = jump_poss_y - mngr_->camRect_.y + (trans_player->getH()) - src_width / 2;
		}
		else {
			--i;
			rect.h = src_width;
			rect.w = i;
			rect.x = trans_player->getPos().getX()  - mngr_->camRect_.x+ init_i - (i / 2);
			rect.y = jump_poss_y - mngr_->camRect_.y+(trans_player->getH()) - src_width / 2;
		}
		

	}
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.h = src_height;
	src.w = src_width;
	t->render(src, rect, 0, nullptr);
 }
void ShadowComponent::handleEvent(SDL_Event event) {

 }
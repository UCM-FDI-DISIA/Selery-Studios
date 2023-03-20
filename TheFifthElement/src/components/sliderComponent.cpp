#include "sliderComponent.h"
void sliderComponent::initComponent() {
	sliderTransform = ent_->getComponent<Transform>(TRANSFORM_H);
	im_ = ent_->getComponent<Image>(IMAGE_H);
	topeDer = sliderTransform->getPos().getX() + 60;
	topeIzq = sliderTransform->getPos().getX() - 60;

	bright = ent_->getComponent<brightSliderComponent>(BRIGHTSLIDER_H);
}

void sliderComponent::updateMousePosition() {
	SDL_GetMouseState(&mousePosX, &mousePosY);
	mousePos = Vector2D(mousePosX + mngr_->camRect_.x, mousePosY + mngr_->camRect_.y);
}

void sliderComponent::update() {
	mouseRect = build_sdlrect(mousePos, mouseWidth, mouseHeight);
	cout << mousePosX << " " << mousePosY << endl;
	cout << sliderTransform->getPos().getX() << " " << sliderTransform->getPos().getY() << endl;
	if (clicked && (sliderTransform->getPos().getX() + sliderTransform->getW() / 2 <= topeDer && sliderTransform->getPos().getX() - sliderTransform->getW() / 2 >= topeIzq)){
		sliderTransform->setPos(Vector2D(mousePosX - sliderTransform->getW() / 2, sliderTransform->getPos().getY()));
	}
	else if(sliderTransform->getPos().getX() + sliderTransform->getW() / 2 >topeDer){
		sliderTransform->setPos(Vector2D(topeDer - sliderTransform->getW() / 2, sliderTransform->getPos().getY()));
	}
	else if (sliderTransform->getPos().getX() - sliderTransform->getW() / 2 < topeIzq){
		sliderTransform->setPos(Vector2D(topeIzq + sliderTransform->getW()/2, sliderTransform->getPos().getY()));
	}

	if (!clicked){ //Actualizar sonido o lo que sea.
		valor = sliderTransform->getPos().getX() - sliderTransform->getW()/2 - topeIzq;
		if (bright != nullptr) bright->channgeBrightness(valor);
	}


	if (Collision::collides(sliderTransform->getPos(), sliderTransform->getW(), sliderTransform->getH(), mousePos, mouseRect.w, mouseRect.h)){
		currentPositionState = MOUSE_OVER;
	}
	else{
		currentPositionState = MOUSE_OUT;
	}
	updateMousePosition();
}

void sliderComponent::handleEvent(SDL_Event event){
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT  && currentPositionState == 1 ) {
			clicked = true;
		}
	}
	else if (event.type == SDL_MOUSEBUTTONUP){
		if (event.button.button == SDL_BUTTON_LEFT) {
			clicked = false;
		}
	}
}

void sliderComponent ::render() {
	SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 250, 0, 0);
	SDL_RenderDrawRect(GameManager::instance()->getRenderer(), &mouseRect);
	SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 0, 0, 255);
}
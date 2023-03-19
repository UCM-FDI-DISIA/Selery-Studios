#include "OptionsState.h"

OptionsState::OptionsState() {
	cout << "OPTIONS";
	CreateInteractuableObjects();
}

void OptionsState::CreateInteractuableObjects() {
	Entity* slider = Manager::addEntity();
	slider->addComponent<Transform>(TRANSFORM_H, Vector2D(220, 10), 20, 20, 1);
	slider->addComponent<sliderComponent>(SLIDERCOMPONENT_H);
}
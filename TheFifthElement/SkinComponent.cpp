#include "SkinComponent.h"
#include "utils/Entity.h"
#include "utils/ecs.h"

void SkinComponent::initComponent() {
	ent_->addComponent<Image>(int(IMAGE_H), fire, nframes, nframes, fila_);
}
void SkinComponent::update() {
	
}

void SkinComponent::changeSkin(string skin)
{
	if (skin == "fire")
	{
		ent_->addComponent<Image>(int(IMAGE_H), fire, nframes, nframes, fila_);
	}
	else if (skin == "air")
	{
		ent_->addComponent<Image>(int(IMAGE_H), air, nframes, nframes, fila_);
	}
	else if (skin == "water")
	{
		ent_->addComponent<Image>(int(IMAGE_H), water, nframes, nframes, fila_);
	}
	else if (skin == "earth")
	{
		ent_->addComponent<Image>(int(IMAGE_H), earth, nframes, nframes, fila_);
	}
}
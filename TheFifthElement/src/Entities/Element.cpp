//#include "Element.h"
//Element::Element(PlayerTD* player, Vector2D pos, Portal* portal) : Entity()
//{
//	portal_ = portal;
//	elementPosition_ = pos;
//	player_ = player;
//	tr = addComponent<Transform>(TRANSFORM_H, elementPosition_, elementWidth_, elementHeight_, elementRotation_, elementSpeed, nframes, true);
//	trPlayer_ = player_->getComponent<Transform>(TRANSFORM_H);
//	t = &SDLUtils::instance()->images().at("fireball");
//	addComponent<Image>(IMAGE_H, t, nframes, nframes, 0, ELEMENT_WIDTH, ELEMENT_HEIGHT);
//	addComponent<ObjectsComponent>(OBJECTSCOMPONENT_H);
//	ch = addComponent<CheckCollision>(CHECKCOLLISION_H, player_, "element");
//}
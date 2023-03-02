//#include ""
//
//
////void ColliderTile::update() {
////
////	
////}
//void ColliderTile::onPlayerCollision()
//{
//	int dir = chooseDirection();
//	
//	//p->onCollision(dir);
//}
//
//int ColliderTile::chooseDirection() {
//	Transform* tp = p->getComponent<Transform>(TRANSFORM_H);
//
//	Vector2D pTopLeft = tp->getPos();
//	Vector2D  pBottomLeft = { pTopLeft.getX(), pTopLeft.getY() + tp->getHeight() };
//	Vector2D pTopRight = { pTopLeft.getX() + tp->getWidth(), pTopLeft.getY() };
//
//	if (bottomLeft_.getY() <= pTopLeft.getY() + margin_) {
//		return 0;
//	}
//	else if (topLeft_.getY() >= pBottomLeft.getY() - margin_) {
//		return 2;
//	}
//	else if (topLeft_.getX() >= pTopRight.getX() - margin_) {
//		return 1;
//	}
//	else { // if (topRight_.getX() <= pTopLeft().getX() + margin_)
//		return 3;
//	}
//}

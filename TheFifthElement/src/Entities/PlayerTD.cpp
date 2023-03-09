#include "PlayerTD.h"
PlayerTD::PlayerTD(string skin, Manager* m, Vector2D pos) : Entity() {
	PlayerPosition_ = pos;
	sk = addComponent<SkinComponent>(SKINCOMPONENT_H, skin);
	sk->changeState(SkinComponent::Idle);
	sk->changeMov();

	tr = addComponent<Transform>(TRANSFORM_H, PlayerPosition_, PlayerWidth_, PlayerHeigth_, PlayerRotation_, speed_, nframes_, matrix_);

	fila_ = 0;
	t_ = &SDLUtils::instance()->images().at(sk->getTexture());
	im_ = addComponent<Image>(IMAGE_H, t_, nframes_, nframes_, fila_, PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME);

	mov = addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);

	in_ = addComponent<InputComponent>(INPUTCOMPONENT_H);
	in_->initComponent();
	in_->setContext(this, m);
	addComponent<EconomyComponent>(ECONOMYCOMPONENT_H);
}
#include "AttackLightBossComponent.h"
#include "ColDetectorComponent.h"

AttackLightBossComponent::AttackLightBossComponent(Entity* player)
{
	player_ = player;
	contAtks = 0;
	dirMov = Vector2D(0, 0);
	fightState = 1;
}

void AttackLightBossComponent::initComponent()
{
	movBoss_ = ent_->getComponent<MovementLightBossComponent>(MOVEMENTLIGHTBOSSCOMPONENT_H);
	playerTrans = player_->getComponent<Transform>(TRANSFORM_H);
	bossTrans = ent_->getComponent<Transform>(TRANSFORM_H);
	timer = sdlutils().currRealTime() + 3000;
	timerRand = sdlutils().currRealTime() + 5000;
	blackScreenTex_ = &SDLUtils::instance()->images().at("BlackScreen");
	random = &SDLUtils::instance()->rand();
	animBoss_ = ent_->getComponent<AnimationLightBossComponent>(ANIMATIONLIGHTBOSSCOMPONENT_H);
	imBoss_ = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
}

void AttackLightBossComponent::setState(int state)
{
	fightState = state;
}

void AttackLightBossComponent::update()
{
	distX = (playerTrans->getPos().getX()+playerTrans->getW()/2) - (bossTrans->getPos().getX()+ bossTrans->getW()/2);
	distY = playerTrans->getPos().getY() - bossTrans->getPos().getY();

	if (fightState == 2) 
	{
		if (timerRand <= sdlutils().currRealTime())
		{
			//escoge una x al azar y mueve al boss a ese sitio, ademas realiza un ataque debo añadir unbooleano de ataque para que no realize ataques muy seguidos
			int limitX = bossTrans->getPos().getX();
			int limitI=0, limitD=0;
			if (limitX-500<=0)
			{
				limitI = 100;
				limitD = limitX + 500;
			}
			else if (limitX + 500 <= 0)
			{
				limitD = BACKGROUNDBEU_WIDTH-100;
				limitI = limitX - 500;
			}
			else { limitI = limitX - 500; limitD = limitX + 500; }
			int newX = random->nextInt(limitI,limitD);
			movBoss_->teleport(Vector2D(newX, bossTrans->getPos().getY()));
			timerRand = sdlutils().currRealTime() + 5000;
		}
	}

	else if (fightState == 3) //marcamos la excepcion del teletransporte esto deberia sere el 3 y el state 2 aleatorio y cada 5 segundos
	{
		if (distX<closeX && distX>negCloseX )
		{
			Vector2D newPos=Vector2D (0,bossTrans->getPos().getY());
			if (distX <= 0 && bossTrans->getPos().getX() <= (BACKGROUNDBEU_WIDTH - 500)) //player a la izquierda y boss lejos del borde derecho
			{
				newPos.setX(bossTrans->getPos().getX() + 400);
			}
			else if (distX <= 0 && bossTrans->getPos().getX() >= (BACKGROUNDBEU_WIDTH - 500)) //player a la izquierda y boss cerca del borde derecho
			{
				newPos.setX(bossTrans->getPos().getX() - 500);
			}
			else if (distX >= 0 && bossTrans->getPos().getX() >= 500) //player a la derecha y boss lejos del borde izquierdo
			{
				newPos.setX(bossTrans->getPos().getX() - 400);
			}
			else if (distX >= 0 && bossTrans->getPos().getX() <= 500) //player a la derecha y boss cerca del borde izquierdo
			{
				newPos.setX(bossTrans->getPos().getX() + 500);
			}
			//newPos.setY(playerTrans->getPos().getY()); //siemre hace tp a la altura del player
			movBoss_->teleport(newPos);//paso por el movement ya que esto es un movimiento y este script no debe modificar transforms, solo hacer gets
			attack1();
		}
	}	

	if (timer <= sdlutils().currRealTime() && !attacking) //añadir sonidos
	{
		contAtks++;
		if (contAtks == 3)
		{		
			animBoss_->newAnim(AnimationLightBossComponent::Attack2); //el ataque 2 sale del lateral derecho 
			attacking = true;
			atk2 = true;
		}

		else 
		{ 
			animBoss_->newAnim(AnimationLightBossComponent::Attack);
			attacking = true;
			atk1 = true;
		}
	}

	if (attacking)
	{
		if (imBoss_->getCol() >= 8 && atk1)
		{
			timer = sdlutils().currRealTime() + 3000;
			attack1();
			atk1 = false;
			attacking = false;
		}

		if (imBoss_->getCol() >= 9 && atk2)
		{
			timer = sdlutils().currRealTime() + 3000;
			attack2();
			contAtks = 0;
			atk2 = false;
			attacking = false;
		}
	}
}

void AttackLightBossComponent::render()
{
	if (distX <= 0)
	{
		imBoss_->setFlip(SDL_FLIP_HORIZONTAL);
	}
	else if (distX > 0)
	{
		imBoss_->setFlip(SDL_FLIP_NONE);
	}
	if (fightState == 4) 
	{
		if (blacker)
		{
			opacity++;
			if (opacity >= 255)
			{
				blacker = false;
			}
		}
		else if (!blacker)
		{
			opacity--;
			if (opacity <= 0)
			{
				blacker = true;
			}
		}
		blackScreenTex_->setAlpha(opacity);
		SDL_RenderCopy(Gm_->getRenderer(), blackScreenTex_->getSDLTexture(), nullptr, &BSrect);
	}
}

void AttackLightBossComponent::attack1()//esto debe ser para generar siempre bolas y no solo en fase1
{
	if (distX<closeX && distX>negCloseX && distY<closeY && distY>negCloseY)//si esta muy cerca se aleja para disparar
	{
		if (distX <= 0 && bossTrans->getPos().getX() <= (BACKGROUNDBEU_WIDTH - 500)) { dirMov.setX(1); }
		else if (distX <= 0 && bossTrans->getPos().getX() >= (BACKGROUNDBEU_WIDTH - 500)) //player a la izquierda y boss cerca del borde derecho
		{
			dirMov.setX(-1);
		}
		else if (distX >= 0 && bossTrans->getPos().getX() >= 500) //player a la derecha y boss lejos del borde izquierdo
		{
			dirMov.setX(-1);
		}
		else { dirMov.setX(1); } //player a la derecha y cerca del borde izquierdo
		movBoss_->move(dirMov);
	}
	//orden de ejecucion: move, set anim al atk2 y despues crear la flecha
	Entity* sphere = new Entity();
	if (distX <= 0)
	{
		arrowTrans_ = sphere->addComponent<Transform>(TRANSFORM_H, Vector2D(bossTrans->getPos().getX() - 68, bossTrans->getPos().getY() + bossTrans->getH() / 2), 256, 128);
	}
	else
	{
		arrowTrans_ = sphere->addComponent<Transform>(TRANSFORM_H, Vector2D(bossTrans->getPos().getX() + 186, bossTrans->getPos().getY() + bossTrans->getH() / 2), 256, 128);
	}	
	arrowIm_ = sphere->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at("SphereArrow"), 256, 128, 12);
	if (distX <= 0) { dirAtk = Vector2D(-1, 0); arrowIm_->setFlip(SDL_FLIP_HORIZONTAL); }
	else { dirAtk = Vector2D(1, 0); }
	arrowTrans_->setVel(5.0);
	arrowTrans_->setDir(dirAtk);
	sphere->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
	sphere->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(96, 48), 32, 64);//datos metidos a mano deberian ser mediante metodos
	sphere->addComponent<DisableOnExit>(DISABLEONEXIT_H);
	sphere->addComponent<ColDetectorComponent>(COLDETECTORCOMPONENT_H, sphere, player_,ent_);
	sphere->addComponent<LightBossElement>(LIGHTBOSSELEMENT_H);
	mngr_->addEntity(sphere);
}

void AttackLightBossComponent::attack2()
{
	Entity* ray = new Entity();
	if (distX <= 0) 
	{ 
		rayTrans_ = ray->addComponent<Transform>(TRANSFORM_H, Vector2D(0, bossTrans->getPos().getY() + bossTrans->getH() / 2), bossTrans->getPos().getX()-bossTrans->getW(), 128);
	}
	else 
	{
		rayTrans_ = ray->addComponent<Transform>(TRANSFORM_H, Vector2D(bossTrans->getPos().getX() + bossTrans->getW() + 96, bossTrans->getPos().getY() + bossTrans->getH() / 2), BACKGROUNDBEU_WIDTH - bossTrans->getPos().getX(), 128); 
	}		
	ray->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(0, bossTrans->getH() / 4), bossTrans->getH() / 2, rayTrans_->getW());
	ray->addComponent<ColDetectorComponent>(COLDETECTORCOMPONENT_H, ray, player_);
	ray->addComponent<LightBossElement>(LIGHTBOSSELEMENT_H);
	ray->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at("Ray"), 256, 128, 5);
	mngr_->addEntity(ray);
}

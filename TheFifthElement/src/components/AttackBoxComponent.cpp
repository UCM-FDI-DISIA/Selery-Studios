#include "AttackBoxComponent.h"
#include "../utils/Entity.h"
#include "Image.h"
#include "../states/BeatEmUpState.h"


AttackBoxComponent::AttackBoxComponent()
{
}
void AttackBoxComponent::initComponent()
{
	playerTr = ent_->getComponent<Transform>(TRANSFORM_H);
	im_ = ent_->getComponent<Image>(IMAGE_H);
}
void AttackBoxComponent::render()
{
	SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 255, 0, 0);							
	SDL_RenderDrawRect(GameManager::instance()->getRenderer(), &box);
}

void AttackBoxComponent::update()
{
	handleBoxes();
	
	unsigned timer = clock();
	timerExecution = (double(timer) / CLOCKS_PER_SEC);

}

void AttackBoxComponent::handleBoxes()
{	

	if (im_->getRow()==9) 
	{
		if(!boxCreated)
		{
			box = build_sdlrect(playerTr->getPos().getX() + playerTr->getW()/2, playerTr->getPos().getY() + playerTr->getH(),20, 20);
			boxCreated = true;
			angle = 180;
		}
		else
		{
					

			//Para poder cambiar satisfactoriamente la direccion del cuadrado
			if (im_->getFlip() == SDL_FLIP_NONE)
			{
				way = 1;
			}
			else
			{
				way = -1;
			}


			moveBoxCurve(72, Vector2D(playerTr->getPos().getX() + playerTr->getW()/2, playerTr->getPos().getY() + playerTr->getH()), 0.07, angle, 182, way);
			static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(box);

			if (im_->getLastFrame() == 10)
			{
				unsigned timer = clock();
				boxTime = (double(timer) / CLOCKS_PER_SEC);
			}
		}
		
	}
	else if (im_->getRow() == 10)
	{
		if (!boxCreated)
		{
			box = build_sdlrect(playerTr->getPos().getX() + playerTr->getW() / 2, playerTr->getPos().getY() + playerTr->getH(), 20, 20);
			boxCreated = true;
			angle = 180;
		}
		else
		{


			moveBoxCurve(72, Vector2D(playerTr->getPos().getX() + playerTr->getW() / 2, playerTr->getPos().getY() + playerTr->getH()), 0.03, angle, 182, 1);
			static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(box);
			if (im_->getLastFrame() == 10)
			{
				unsigned timer = clock();
				boxTime = (double(timer) / CLOCKS_PER_SEC);
			}
		}

	}
	else
	{
		boxCreated = false;
		if (boxTime + 1000/1000 < timerExecution) { 
			GFY();
			boxTime = 0;
		}
	}
	
	


}

void AttackBoxComponent::moveBox(Vector2D direction, float vel)
{
	box.x += direction.getX() * vel;
	box.y += direction.getY() * vel;
}
void AttackBoxComponent::moveBoxCurve(float radio, Vector2D posCenter, float vel, float& angle,float stoppingAngle, int way)
{
	if (angle<stoppingAngle)
	{
		angle += vel * way;
	}
	

	box.x = posCenter.getX() + (int)(radio * cos(angle));
	box.y = posCenter.getY() + (int)(radio * sin(angle));
	//cout << "Angle:" << angle << "Stop:" << stoppingAngle << endl;
}

void AttackBoxComponent::GFY()
{
	box.x = 1000000000;
	box.y = 1000000000;

}
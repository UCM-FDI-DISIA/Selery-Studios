#include "AttackBoxComponent.h"
#include "../utils/Entity.h"
#include "Image.h"



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
	SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 255, 0, 0);							//Renderizamos el rect?gulo del player
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

	if (im_->getRow()==7) // Ataque basico de fuego
	{
		if(!boxCreated)
		{
			box = build_sdlrect(playerTr->getPos().getX() + ((playerTr->getW() / 2) / 28)-40, playerTr->getPos().getY() + (playerTr->getH() / 1.5f)+30, 10, 10);
			boxCreated = true;
			angle = 270;
		}
		else
		{
			//trFighter->setVel(trFighter->getVel() + (Vector2D(0, -1).rotate(trFighter->getR()) * acceleration));
		/*	moveBox(Vector2D(-1,0).rotate(i), 1);*/

			moveBoxCurve(70, Vector2D(playerTr->getPos().getX() + ((playerTr->getW() / 2) / 28) , playerTr->getPos().getY() + (playerTr->getH() / 1.5f) + 30) , 0.07, angle, 1);
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
		if (boxTime + 1000/1000 < timerExecution) { // The shorterpaddle and biggerpaddle rewards is activated REWARDS_TIME seconds
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
void AttackBoxComponent::moveBoxCurve(float radio, Vector2D posCenter, float vel, float& angle, int way)
{
	angle += vel * way;

	box.x = posCenter.getX() + (int)(radio * cos(angle));
	box.y = posCenter.getY() + (int)(radio * sin(angle));
	cout << "BOX X:" << box.x << "BOX Y:" << box.y << endl;
}

void AttackBoxComponent::GFY()
{
	box.x = 1000000000;
	box.y = 1000000000;

}
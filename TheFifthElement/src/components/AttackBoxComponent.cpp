
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
	for (auto it : boxes)
	{
		SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 255, 0, 0);
		SDL_RenderDrawRect(GameManager::instance()->getRenderer(), &it);
	}


}

void AttackBoxComponent::update()
{
	handleBoxes();

	unsigned timer = clock();
	timerExecution = (double(timer) / CLOCKS_PER_SEC);

}

void AttackBoxComponent::handleBoxes()
{

	if (im_->getRow() == 9 && im_->getCol() <= 8)
	{

		if (!boxCreated)
		{
			boxes.clear();
			for (int i = 0; i < 5; i++)
			{
				boxes.push_back(build_sdlrect(playerTr->getPos().getX() - mngr_->camRect_.x + playerTr->getW() / 2, playerTr->getPos().getY() + playerTr->getH(), 10, 10));
			}
			boxCreated = true;

			//Para poder cambiar satisfactoriamente la direccion del cuadrado
			if (im_->getFlip() == SDL_FLIP_NONE)
			{
				way = 1;
				stoppingAngle = 182;
				for (int i = 0; i < boxes.size(); i++)
				{
					angles[i] = 180;
				}
			}
			else
			{
				way = -1;
				for (int i = 0; i < boxes.size(); i++)
				{
					angles[i] = 0;
				}
				stoppingAngle = -3.1;
			}
		}
		else
		{
			for (int i = 0; i < boxes.size(); i++)
			{

				moveBoxCurve(boxes[i], 40 + 10 * i, Vector2D(playerTr->getPos().getX() - mngr_->camRect_.x + playerTr->getW() / 2, playerTr->getPos().getY() + playerTr->getH()), 0.095, angles[i], stoppingAngle, way);
				static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[i]);
			}


			if (im_->getCol() == 8)
			{
				unsigned timer = clock();
				boxTime = (double(timer) / CLOCKS_PER_SEC);
				boxes.clear();
				boxCreated = false;
			}
		}

	}
	else if (im_->getRow() == 9 && im_->getCol() <= 16)
	{


		if (!boxCreated)
		{

			boxes.push_back(build_sdlrect(playerTr->getPos().getX() - mngr_->camRect_.x + playerTr->getW() / 2, playerTr->getPos().getY() + playerTr->getH() / 2, 140, 60));
			boxCreated = true;

			//Para poder cambiar satisfactoriamente la direccion del cuadrado
			if (im_->getFlip() == SDL_FLIP_NONE)
			{
				way = 1;
				stoppingAngle = 360;
				for (int i = 0; i < boxes.size(); i++)
				{
					angles[i] = 182;
				}
			}
			else
			{
				way = -1;
				for (int i = 0; i < boxes.size(); i++)
				{
					angles[i] = 0;
				}
				stoppingAngle = -3.1;
			}
		}
		else
		{
			if (way == -1)
			{
				moveBoxCurve(boxes[0], 5, Vector2D(playerTr->getPos().getX() - mngr_->camRect_.x - 20 + playerTr->getW() / 3, playerTr->getPos().getY() + playerTr->getH() / 2), 0.195, angles[0], stoppingAngle, way);
				static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0]);
			}
			else
			{
				moveBoxCurve(boxes[0], 5, Vector2D(playerTr->getPos().getX() - mngr_->camRect_.x + playerTr->getW() / 3, playerTr->getPos().getY() + playerTr->getH() / 2), 0.195, angles[0], stoppingAngle, way);
				static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0]);
			}

			if (im_->getCol() == 16)
			{
				unsigned timer = clock();
				boxTime = (double(timer) / CLOCKS_PER_SEC);
				boxes.clear();
				boxCreated = false;
			}
		}
	}

	else if (im_->getRow() == 9 && im_->getCol() <= 24)
	{
		if (!boxCreated)
		{

			boxes.push_back(build_sdlrect(playerTr->getPos().getX() - mngr_->camRect_.x - 30 + playerTr->getW() / 2, playerTr->getPos().getY() + playerTr->getH() / 2, 70, 60));
			boxCreated = true;

			//Para poder cambiar satisfactoriamente la direccion del cuadrado
			if (im_->getFlip() == SDL_FLIP_NONE)
			{
				way = 1;
			}
			else
			{
				way = -1;
			}
		}
		else
		{
			if (way == 1)
			{
				moveBox(boxes[0], Vector2D(1, 0), 2);
				//moveBoxCurve(boxes[0], 5, Vector2D(playerTr->getPos().getX() - mngr_->camRect_.x - 20 + playerTr->getW() / 3, playerTr->getPos().getY() + playerTr->getH() / 2), 0.195, angles[0], stoppingAngle, way);
				static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0]);
			}
			else
			{
				moveBox(boxes[0], Vector2D(-1, 0), 9);
				//moveBoxCurve(boxes[0], 5, Vector2D(playerTr->getPos().getX() - mngr_->camRect_.x + playerTr->getW() / 3, playerTr->getPos().getY() + playerTr->getH() / 2), 0.195, angles[0], stoppingAngle, way);
				static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0]);
			}

			if (im_->getCol() == 24)
			{
				unsigned timer = clock();
				boxTime = (double(timer) / CLOCKS_PER_SEC);
				boxes.clear();
				boxCreated = false;
			}
		}
	}





	else if (im_->getRow() == 10)
	{
		if (!boxCreated)
		{
			//(player_->getComponent<Transform>(TRANSFORM_H)->getPos().getX() + camOffset_) - WIN_WIDTH / 2;
			box = build_sdlrect(playerTr->getPos().getX() + playerTr->getW() / 2, playerTr->getPos().getY() + playerTr->getH(), 20, 20);
			box2 = build_sdlrect(playerTr->getPos().getX() + playerTr->getW() / 2, playerTr->getPos().getY() + playerTr->getH(), 20, 20);
			boxCreated = true;
			angle = 180;
		}
		else
		{


			moveBoxCurve(box, 72, Vector2D(playerTr->getPos().getX() + playerTr->getW() / 2, playerTr->getPos().getY() + playerTr->getH()), 0.03, angle, 182, 1);
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
		if (boxTime + 1000 / 1000 < timerExecution) {
			unsigned timer = clock();
			boxTime = (double(timer) / CLOCKS_PER_SEC);
			boxes.clear();
			boxCreated = false;
		}
	}

}

void AttackBoxComponent::moveBox(SDL_Rect& box, Vector2D direction, float vel)
{
	box.x += direction.getX() * vel;
	box.y += direction.getY() * vel;

}
void AttackBoxComponent::moveBoxCurve(SDL_Rect& box, float radio, Vector2D posCenter, float vel, float& angle, float stoppingAngle, int way)
{

	if (angle < stoppingAngle && way == 1)
	{
		angle += vel;
	}
	else if (angle > stoppingAngle && way == -1)
	{
		angle += vel * -1;
	}

	//cout << angle<<endl;
	box.x = posCenter.getX() + (int)(radio * cos(angle));
	box.y = posCenter.getY() + (int)(radio * sin(angle));

	box2.x = posCenter.getX() + (int)(radio * cos(angle)) - 10;
	box2.y = posCenter.getY() + (int)(radio * sin(angle)) - 10;
	//cout << "Angle:" << angle << "Stop:" << stoppingAngle << endl;
}






#include "AttackBoxComponent.h"
#include "../utils/Entity.h"
#include "Image.h"
#include "../states/BeatEmUpState.h"


AttackBoxComponent::AttackBoxComponent() {

}
void AttackBoxComponent::initComponent()
{
	isPlayer = ent_->hasComponent(INPUTCOMPONENTBEU_H);
	if (!isPlayer) {
		im_ = ent_->getComponent<Image>(IMAGE_H);
	}
	entityTr = ent_->getComponent<Transform>(TRANSFORM_H);
	if (ent_->hasComponent(INPUTCOMPONENTBEU_H))
	{
		im_ = ent_->getComponent<Image>(IMAGE_H);
		type = im_->getType();

		sk_ = ent_->getComponent<SkinBEUComponent>(SKINBEUCOMPONENT_H);
	}
	else if(ent_->hasComponent(ANIMATIONENEMYBEUCOMPONENT_H))
	{
		anim_ = ent_->getComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H);
		type = anim_->getType();
	}

}
void AttackBoxComponent::render()
{
	for (auto it : boxes)
	{
		SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 255, 0, 0);
		SDL_RenderDrawRect(GameManager::instance()->getRenderer(), &it);
	}
}

void AttackBoxComponent::update(){
	if (isPlayer) {
		type = im_->getType();
		handleBoxes();
		unsigned timer = clock();
		timerExecution = (double(timer) / CLOCKS_PER_SEC);
	}
	else {
		handleBoxes();
		unsigned timer = clock();
		timerExecution = (double(timer) / CLOCKS_PER_SEC);
	}
}

void AttackBoxComponent::handleBoxes()
{
	if (isPlayer) {
		if (im_->getRow() == 9)
		{
			//cout << "COL: " << im_->getCol() << endl;
		}

		if (sk_->getSkin() == "Player_BEU_fire")
		{

			//Comprobamos que animación estamos ejecutando y en que punto de la animación estamos 
			if (im_->getRow() == 9 && im_->getCol() <= 8)
			{

				if (!boxCreated)
				{
					boxes.clear();
					for (int i = 0; i < 5; i++)
					{
						boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + entityTr->getW() / 2, entityTr->getPos().getY() + entityTr->getH(), 10, 10));
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
							angles[i] = 5;
						}
						stoppingAngle = 3.5;
					}
				}
				else
				{

					cout << angles[0] << endl;
					for (int i = 0; i < boxes.size(); i++)
					{

						moveBoxCurve(boxes[i], 40 + 10 * i, Vector2D(entityTr->getPos().getX() - mngr_->camRect_.x + entityTr->getW() / 2, entityTr->getPos().getY() + entityTr->getH()), 0.075, angles[i], stoppingAngle, way);
						static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[i], type, true);
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

			else if (im_->getRow() == 9 && im_->getCol() <= 15)
			{
				if (!boxCreated)
				{

					boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + entityTr->getW() / 2, entityTr->getPos().getY() + entityTr->getH() / 2, 140, 60));
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
						moveBoxCurve(boxes[0], 5, Vector2D(entityTr->getPos().getX() - mngr_->camRect_.x - 20 + entityTr->getW() / 3, entityTr->getPos().getY() + entityTr->getH() / 2), 0.195, angles[0], stoppingAngle, way);
						static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0], type, true);
					}
					else
					{
						moveBoxCurve(boxes[0], 5, Vector2D(entityTr->getPos().getX() - mngr_->camRect_.x + entityTr->getW() / 3, entityTr->getPos().getY() + entityTr->getH() / 2), 0.195, angles[0], stoppingAngle, way);
						static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0], type, true);
					}

					if (im_->getCol() == 15)
					{
						unsigned timer = clock();
						boxTime = (double(timer) / CLOCKS_PER_SEC);
						boxes.clear();
						boxCreated = false;

					}
				}
			}

			else if (im_->getRow() == 9 && im_->getCol() > 15 && im_->getCol() <= 24)
			{
				if (!boxCreated)
				{
					boxes.clear();
					boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 30 + entityTr->getW() / 2, entityTr->getPos().getY() + entityTr->getH() / 2, 70, 60));
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
					moveBox(boxes[0], Vector2D(1, 0) * way, 2);
					static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0], type, true);
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
					boxes.clear();
					for (int i = 0; i < 5; i++)
					{
						boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + entityTr->getW() / 2, entityTr->getPos().getY() + entityTr->getH(), 30, 30));
					}
					boxCreated = true;

					//Para poder cambiar satisfactoriamente la direccion del cuadrado
					if (im_->getFlip() == SDL_FLIP_NONE)
					{
						way = 1;
						stoppingAngle = 218;
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
							angles[i] = 30;
						}
						stoppingAngle = -3.1;
					}
				}
				else
				{
					for (int i = 0; i < boxes.size(); i++)
					{
						if (way == 1)
						{
							moveBoxCurve(boxes[i], 40 + 10 * i, Vector2D(entityTr->getPos().getX() - mngr_->camRect_.x + entityTr->getW() / 2, entityTr->getPos().getY() + entityTr->getH()), 0.03, angles[i], stoppingAngle, way);
						}
						else
						{
							moveBoxCurve(boxes[i], 40 + 10 * i, Vector2D(entityTr->getPos().getX() - 10 - mngr_->camRect_.x + entityTr->getW() / 2, entityTr->getPos().getY() + entityTr->getH()), 0.025, angles[i], stoppingAngle, way);

						}

						static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[i], type, true);
					}


					if (im_->getCol() == 17)
					{
						unsigned timer = clock();
						boxTime = (double(timer) / CLOCKS_PER_SEC);
						boxes.clear();
						boxCreated = false;
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
		else if (sk_->getSkin() == "Player_BEU_water")
		{
			if (im_->getRow() == 9 && im_->getCol() <= 7)
			{

				if (!boxCreated)
				{
					boxes.clear();
					//Para poder cambiar satisfactoriamente la direccion del cuadrado
					if (im_->getFlip() == SDL_FLIP_NONE)
					{
						way = 1;
					}
					else
					{
						way = -1;
					}

					for (int i = 0; i < 7; i++)
					{
						boxes.push_back(build_sdlrect(entityTr->getPos().getX() + 8 * i * way - mngr_->camRect_.x + entityTr->getW() / 2, entityTr->getPos().getY() + 30 + entityTr->getH() / 2, 10, 10));
					}
					//boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x  + entityTr->getW() / 2, entityTr->getPos().getY() +30+ entityTr->getH() / 2, 70, 10));
					boxCreated = true;


				}
				else
				{

					for (int i = 0; i < boxes.size(); i++)
					{

						moveBox(boxes[i], Vector2D(1, 0) * way, 1);
						/*moveBoxCurve(boxes[i], 40 + 10 * i, Vector2D(entityTr->getPos().getX() - mngr_->camRect_.x + entityTr->getW() / 2, entityTr->getPos().getY() + entityTr->getH()), 0.095, angles[i], stoppingAngle, way);
						*/static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[i], type, true);
					}

					if (im_->getCol() == 7)
					{
						unsigned timer = clock();
						boxTime = (double(timer) / CLOCKS_PER_SEC);
						boxes.clear();
						boxCreated = false;
					}
				}

			}

			else if (im_->getRow() == 9 && im_->getCol() <= 17)
			{
				Vector2D lastBox;
				if (!boxCreated)
				{
					boxes.clear();
					//Para poder cambiar satisfactoriamente la direccion del cuadrado
					if (im_->getFlip() == SDL_FLIP_NONE)
					{
						way = 1;
					}
					else
					{
						way = -1;
					}

					if (im_->getCol() > 11 && im_->getCol() < 15)
					{
						for (int i = 0; i < 7; i++)
						{
							boxes.push_back(build_sdlrect(entityTr->getPos().getX() + 8 * i * way - mngr_->camRect_.x + entityTr->getW() / 2, entityTr->getPos().getY() + 30 + entityTr->getH() / 2, 10, 10));

						}
						boxCreated = true;
					}



				}
				else
				{

					for (int i = 0; i < boxes.size(); i++)
					{

						moveBox(boxes[i], Vector2D(1, 0) * way, 2);
						lastBox = Vector2D(boxes[boxes.size() - 1].x, boxes[boxes.size() - 1].y);
						static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[i], type, true);
					}


					if (im_->getCol() == 15)
					{

						boxes.clear();
						unsigned timer = clock();
						boxTime = (double(timer) / CLOCKS_PER_SEC);
						boxes.push_back(build_sdlrect(lastBox.getX(), lastBox.getY() - 5, 25, 25));
						boxCreated = false;
					}
				}
			}

			else if (im_->getRow() == 9 && im_->getCol() <= 23)
			{
				if (!boxCreated)
				{
					boxes.clear();
					boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 30 + entityTr->getW() / 2, entityTr->getPos().getY() + entityTr->getH() / 2, 70, 60));
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
					moveBox(boxes[0], Vector2D(1, 0) * way, 2);

					static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0], type, true);
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
					boxes.clear();

					//Para poder cambiar satisfactoriamente la direccion del cuadrado
					if (im_->getFlip() == SDL_FLIP_NONE)
					{
						boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + 40 + entityTr->getW() / 2, entityTr->getPos().getY() + 40 + entityTr->getH() / 2, 35, 35));
						way = 1;
					}
					else
					{
						boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 75 + entityTr->getW() / 2, entityTr->getPos().getY() + 40 + entityTr->getH() / 2, 35, 35));

						way = -1;
					}
					boxCreated = true;

				}
				else
				{


					if (im_->getCol() < 6)
					{
						moveBox(boxes[0], Vector2D(0, -1), 2);
					}
					else if (im_->getCol() < 13 && im_->getCol() > 8)
					{
						moveBox(boxes[0], Vector2D(0, 1), 3);
					}
					else if (im_->getCol() >= 13 && im_->getCol() < 14)
					{
						boxes.clear();
						if (way == 1)boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + 10 + entityTr->getW() / 2, entityTr->getPos().getY() + 13 + entityTr->getH() / 2, 90, 50));
						else boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 100 + entityTr->getW() / 2, entityTr->getPos().getY() + 13 + entityTr->getH() / 2, 90, 50));

					}
					static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0], type, true);
					if (im_->getCol() == 14)
					{
						unsigned timer = clock();
						boxTime = (double(timer) / CLOCKS_PER_SEC);
						boxes.clear();
						boxCreated = false;
					}
				}
			}
			else
			{
				boxCreated = false;
				if (boxTime + 750 / 1000 < timerExecution) {
					unsigned timer = clock();
					boxTime = (double(timer) / CLOCKS_PER_SEC);
					boxes.clear();
					boxCreated = false;
				}
			}
		}
	}
	else { // Para el jefe de tierra
		if (im_->getRow() == 2 && im_->getCol() >= 7) {
			if (!boxCreated) {
				boxes.clear();
				
				//Para poder cambiar satisfactoriamente la direccion del cuadrado
				if (im_->getFlip() == SDL_FLIP_NONE) {
					boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + entityTr->getW() / 2, entityTr->getPos().getY() + entityTr->getH() / 2 - 20, 70, 70));
				}
				else {
					boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 70 + entityTr->getW() / 2, entityTr->getPos().getY() + entityTr->getH() / 2 - 20, 70, 70));
				}
				boxCreated = true;
			}
			else {
				static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0], "earth", false);
				if (im_->getCol() == 16)
				{
					unsigned timer = clock();
					boxTime = (double(timer) / CLOCKS_PER_SEC);
					boxes.clear();
					boxCreated = false;
				}
			}
		}
		//cout << entityTr->getPos() << endl;
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





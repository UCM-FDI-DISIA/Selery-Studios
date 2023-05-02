
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
		im_ = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
	}
	entityTr = ent_->getComponent<Transform>(TRANSFORM_H);
	if (ent_->hasComponent(INPUTCOMPONENTBEU_H))
	{
		im_ = ent_->getComponent<FramedImage>(FRAMEDIMAGE_H);
		type = im_->getType();

		sk_ = ent_->getComponent<SkinBEUComponent>(SKINBEUCOMPONENT_H);
	}
	else if (ent_->hasComponent(ANIMATIONENEMYBEUCOMPONENT_H))
	{
		anim_ = ent_->getComponent<AnimationEnemyBEUComponent>(ANIMATIONENEMYBEUCOMPONENT_H);
		type = anim_->getType();
	}
}
void AttackBoxComponent::render()
{
	for (auto it : boxes)
	{
		//it.w *= entityTr->getS();
		//it.h *= entityTr->getS();
		SDL_SetRenderDrawColor(GameManager::instance()->getRenderer(), 0, 255, 0, 0);
		SDL_RenderDrawRect(GameManager::instance()->getRenderer(), &it);
	}
}

void AttackBoxComponent::update() {
	if (isPlayer) {
		type = im_->getType();
	}
	else
	{
		if(im_->getRow()==2)
		cout << im_->getCol()<<endl;
	}
	handleBoxes();
	unsigned timer = clock();
	timerExecution = (double(timer) / CLOCKS_PER_SEC);
}

void AttackBoxComponent::handleBoxes()
{
	if (isPlayer) {
		if (type == "fire")
		{
			//Comprobamos que animaci�n estamos ejecutando y en que punto de la animaci�n estamos 
			if (im_->getTexKey() == "Player_BEU_fire_attack3" && im_->getCol() < 8)
			{

				if (!boxCreated && im_->getCol() != 0)
				{
					boxes.clear();

					if (im_->getCol() != 8)
					{
						for (int i = 0; i < 7; i++)
						{
							boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + (entityTr->getW()) / 2, entityTr->getPos().getY() + (entityTr->getH()), 10 * entityTr->getSW(), 10 * entityTr->getSH()));
						}
						boxCreated = true;
					}
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
					for (int i = 0; i < boxes.size(); i++)
					{

						moveBoxCurve(boxes[i], 45 + 10 * i * entityTr->getSW(), Vector2D(entityTr->getPos().getX() - mngr_->camRect_.x + (entityTr->getW()) / 2,
						entityTr->getPos().getY() + (entityTr->getH())), 0.075, angles[i], stoppingAngle, way);
						static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[i], type, false);
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

			else if (im_->getTexKey() == "Player_BEU_fire_attack3" && im_->getCol() < 15 && im_->getCol() > 8)
			{

				if (!boxCreated)
				{
					boxes.clear();

					if (im_->getCol() != 14)
					{
						boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + (entityTr->getW()) / 2, entityTr->getPos().getY() + (entityTr->getH()) / 2, 140 *entityTr->getSW(), 60 * entityTr->getSH()));
						boxCreated = true;

					}


					//Para poder cambiar satisfactoriamente la direccion del cuadrado
					if (im_->getFlip() == SDL_FLIP_NONE)
					{
						way = 1;
						stoppingAngle = 360;
						angles[0] = 182;
					}
					else
					{
						way = -1;
						angles[0] = 0;
						stoppingAngle = -3.1;
					}
				}
				else
				{
					if (way == -1)
					{
						moveBoxCurve(boxes[0], 5, Vector2D(entityTr->getPos().getX() - mngr_->camRect_.x - 20 + (entityTr->getW()) / 3, entityTr->getPos().getY() + (entityTr->getH()) / 2), 0.195, angles[0], stoppingAngle, way);
						static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0], type, false);
					}
					else
					{
						moveBoxCurve(boxes[0], 5, Vector2D(entityTr->getPos().getX() - mngr_->camRect_.x + (entityTr->getW()) / 3, entityTr->getPos().getY() + (entityTr->getH()) / 2), 0.195, angles[0], stoppingAngle, way);
						static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0], type, false);
					}

					if (im_->getCol() == 14)
					{
						unsigned timer = clock();
						boxTime = (double(timer) / CLOCKS_PER_SEC);
						boxes.clear();
						boxCreated = false;

					}
				}
			}

			else if (im_->getTexKey() == "Player_BEU_fire_attack3" && im_->getCol() > 16 && im_->getCol() <= 24)
			{
				if (!boxCreated)
				{
					boxes.clear();
					if (im_->getCol() != 24)
					{
						boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 30 + (entityTr->getW()) / 2, entityTr->getPos().getY() + (entityTr->getH()) / 2, 70 * entityTr->getSW(), 60 * entityTr->getSH()));
						boxCreated = true;

					}
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
					moveBox(boxes[0], Vector2D(1, 0) * way , 3);
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

			else if (im_->getTexKey() == "Player_BEU_fire_super")
			{

				if (!boxCreated)
				{
					boxes.clear();
					for (int i = 0; i < 7; i++)
					{
						boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + (entityTr->getW()) / 2, entityTr->getPos().getY() + (entityTr->getH()  ), 30 * entityTr->getSW(), 30 * entityTr->getSH()));
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
							moveBoxCurve(boxes[i], 40 + 10 * i * entityTr->getSW(), Vector2D(entityTr->getPos().getX() - mngr_->camRect_.x + (entityTr->getW()  ) / 2, entityTr->getPos().getY() + (entityTr->getH()  )), 0.03, angles[i], stoppingAngle, way);
						}
						else
						{
							moveBoxCurve(boxes[i], 40 + 10 * i * entityTr->getSW(), Vector2D(entityTr->getPos().getX() - 10 - mngr_->camRect_.x + (entityTr->getW()  ) / 2, entityTr->getPos().getY() + (entityTr->getH()  )), 0.025, angles[i], stoppingAngle, way);

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
		else if (type == "water")
		{
			if (im_->getTexKey() == "Player_BEU_water_attack3" && im_->getCol() <= 7)
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
					if (im_->getCol() != 7)
					{
						for (int i = 0; i < 7; i++)
						{
							boxes.push_back(build_sdlrect(entityTr->getPos().getX() + 8 * i * way * entityTr->getSW() -mngr_->camRect_.x + (entityTr->getW()) / 2, entityTr->getPos().getY() + 30 * entityTr->getSH() + (entityTr->getH()) / 2, 10 * entityTr->getSW(), 10 * entityTr->getSH()));
						}
						boxCreated = true;
					}

				}
				else
				{

					for (int i = 0; i < boxes.size(); i++)
					{

						moveBox(boxes[i], Vector2D(1, 0) * way, 1);
						/*moveBoxCurve(boxes[i], 40 + 10 * i, Vector2D(entityTr->getPos().getX() - mngr_->camRect_.x + (entityTr->getW()  ) / 2, entityTr->getPos().getY() + (entityTr->getH()  )), 0.095, angles[i], stoppingAngle, way);
						*/static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[i], type, false);
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

			else if (im_->getTexKey() == "Player_BEU_water_attack3" && im_->getCol() <= 17)
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
							boxes.push_back(build_sdlrect(entityTr->getPos().getX() + 8 * i * way * entityTr->getSW() - mngr_->camRect_.x + (entityTr->getW()) / 2, entityTr->getPos().getY() + 30 * entityTr->getSH() + (entityTr->getH()) / 2, 10 * entityTr->getSW(), 10 * entityTr->getSH()));

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
						static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[i], type, false);
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

			else if (im_->getTexKey() == "Player_BEU_water_attack3" && im_->getCol() <= 23)
			{
				if (!boxCreated)
				{
					boxes.clear();
					boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 30 + (entityTr->getW()  ) / 2, entityTr->getPos().getY() + (entityTr->getH()  ) / 2, 70 * entityTr->getSW(), 60 * entityTr->getSH()));
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

			else if (im_->getTexKey() == "Player_BEU_water_super")
			{

				if (!boxCreated)
				{
					boxes.clear();

					//Para poder cambiar satisfactoriamente la direccion del cuadrado
					if (im_->getFlip() == SDL_FLIP_NONE)
					{
						boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + 40*entityTr->getSW() + (entityTr->getW()  ) / 2, entityTr->getPos().getY() + 40 + (entityTr->getH()  ) / 2, 35 * entityTr->getSW(), 35 * entityTr->getSH()));
						way = 1;
					}
					else
					{
						boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 75* entityTr->getSW() + (entityTr->getW()  ) / 2, entityTr->getPos().getY() + 40 + (entityTr->getH()  ) / 2, 35 * entityTr->getSW(), 35 * entityTr->getSH()));

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
						if (way == 1)boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + 10 * entityTr->getSW() + (entityTr->getW()) / 2, entityTr->getPos().getY() + 13 + (entityTr->getH()) / 2, 90 * entityTr->getSW(), 50 * entityTr->getSH()));
						else boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 100 * entityTr->getSW() + (entityTr->getW()) / 2, entityTr->getPos().getY() + 13 + (entityTr->getH()) / 2, 90 * entityTr->getSW(), 50 * entityTr->getSH()));

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
		else if (type == "air")
		{
			//Comprobamos que animaci�n estamos ejecutando y en que punto de la animaci�n estamos 
			if (im_->getTexKey() == "Player_BEU_air_attack3" && im_->getCol() <= 6)
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
					if (im_->getCol() != 6 && im_->getCol() != 0)
					{
						for (int i = 0; i < 5; i++)
						{
							if (im_->getCol() != 6)boxes.push_back(build_sdlrect(entityTr->getPos().getX() + i * 6 * way * entityTr->getSW() - mngr_->camRect_.x + (entityTr->getW()) / 2, entityTr->getPos().getY() + (entityTr->getH()) - 30 * entityTr->getSH(), 10 * entityTr->getSW(), 10 * entityTr->getSH()));
						}
						boxCreated = true;
					}


				}
				else
				{
					if (im_->getCol() < 3)
					{
						for (int i = 0; i < boxes.size(); i++)
						{
							moveBox(boxes[i], Vector2D(1, 0) * way, 1);
							static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[i], type, false);
						}
					}
					else if (im_->getCol() >= 3 && im_->getCol() < 4)
					{

						for (int i = 0; i < boxes.size(); i++)
						{
							boxes[i].y -= 5;
							moveBox(boxes[i], Vector2D(-1, 0) * way + Vector2D(0, 1), 8);
							static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[i], type, false);
						}
					}

					if (im_->getCol() == 6)
					{
						unsigned timer = clock();
						boxTime = (double(timer) / CLOCKS_PER_SEC);
						boxes.clear();
						boxCreated = false;
					}
				}
			}

			else if (im_->getTexKey() == "Player_BEU_air_attack3" && im_->getCol() > 6 && im_->getCol() <= 13)
			{
				if (!boxCreated)
				{
					if (im_->getFlip() == SDL_FLIP_NONE)
					{
						boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + 20 * entityTr->getSW() + (entityTr->getW()) / 2, entityTr->getPos().getY() + 10 * entityTr->getSH() + (entityTr->getH()) / 2, 50* entityTr->getSW(), 50* entityTr->getSH()));
						way = 1;
					}
					else
					{
						boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 60*entityTr->getSW() + (entityTr->getW()  ) / 2, entityTr->getPos().getY() + 10 * entityTr->getSH() + (entityTr->getH()  ) / 2, 50*entityTr->getSW(), 50 * entityTr->getSH()));

						way = -1;
					}
					boxCreated = true;

				}
				else
				{


					static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0], type, false);


					if (im_->getCol() == 13)
					{
						unsigned timer = clock();
						boxTime = (double(timer) / CLOCKS_PER_SEC);
						boxes.clear();
						boxCreated = false;

					}
				}
			}

			else if (im_->getTexKey() == "Player_BEU_air_attack3" && im_->getCol() > 13 && im_->getCol() <= 25)
			{
				if (!boxCreated)
				{
					if (im_->getCol() != 25)
					{
						boxes.clear();
						boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 30 * entityTr->getSW() + (entityTr->getW()) / 2, entityTr->getPos().getY() + (entityTr->getH()) / 2, 40 * entityTr->getSW(), 60 * entityTr->getSH()));
						boxCreated = true;

					}


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
					if (im_->getCol() < 24)
					{
						moveBox(boxes[0], Vector2D(1, 0) * way, 3);
					}

					static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0], type, true);
					if (im_->getCol() == 25)
					{

						unsigned timer = clock();
						boxTime = (double(timer) / CLOCKS_PER_SEC);
						boxes.clear();
						boxCreated = false;
					}

				}

			}
			else if (im_->getTexKey() == "Player_BEU_air_super") {
				if (!boxCreated) {
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
					boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + entityTr->getW() / 2, entityTr->getPos().getY() + 10 * entityTr->getSH() + entityTr->getH() / 2, 30 * entityTr->getSW(), 60* entityTr->getSH()));
					boxCreated = true;
				}
				else
				{
					if (im_->getCol() < 6)
					{
						moveBox(boxes[0], Vector2D(1, 0) * way* entityTr->getSW(), 2);
						actualized = false;
					}
					else if (im_->getCol() >= 6 && im_->getCol() < 14)
					{
						if (!actualized)
						{
							actualized = true;
							Vector2D newBoxPos = entityTr->getPos();
							boxes[0].x = newBoxPos.getX() - mngr_->camRect_.x + (entityTr->getW()  ) / 2 - boxes[0].w;
							boxes[0].y = newBoxPos.getY() - 10 * entityTr->getSH();
							boxes[0].w = 90 * entityTr->getSW();
							boxes[0].h = 50 * entityTr->getSH();
						}
						else
						{
							moveBox(boxes[0], Vector2D(0, 1)*entityTr->getSW(), 3);
						}
					}
					else if (im_->getCol() >= 14 && im_->getCol() < 18)
					{
						if (actualized)
						{
							actualized = false;
							Vector2D newBoxPos = entityTr->getPos();
							if (way == 1)
							{
								boxes[0].x = newBoxPos.getX() - mngr_->camRect_.x + 130 * entityTr->getSW();
							}
							else
							{
								boxes[0].x = newBoxPos.getX() - mngr_->camRect_.x;
							}
							boxes[0].y = newBoxPos.getY() - 30 + (entityTr->getW()  ) / 2;
							boxes[0].w = 50 * entityTr->getSW();
							boxes[0].h = 80* entityTr->getSH();
						}
						else
						{
							moveBox(boxes[0], Vector2D(-1, 0) * way*entityTr->getSW(), 3);
						}

					}
					else if (im_->getCol() >= 18 && im_->getCol() < 26)
					{
						if (!actualized)
						{
							actualized = true;
							Vector2D newBoxPos = entityTr->getPos();
							if (way == 1)
							{
								boxes[0].x = newBoxPos.getX() - mngr_->camRect_.x;
							}
							else
							{
								boxes[0].x = newBoxPos.getX() - mngr_->camRect_.x + 120* entityTr->getSW();
							}

							boxes[0].y = newBoxPos.getY() - 30 + (entityTr->getW()  ) / 2;
							boxes[0].w = 50*entityTr->getSW();
							boxes[0].h = 80* entityTr->getSH();
						}
						else
						{
							moveBox(boxes[0], Vector2D(1, 0) * way* entityTr->getSW(), 3);
						}

					}

					static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0], type, true);

					if (im_->getCol() == 27)
					{
						unsigned timer = clock();
						boxTime = (double(timer) / CLOCKS_PER_SEC);
						boxes.clear();
						boxCreated = false;
						actualized = false;
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
		else
		{
			//Comprobamos que animaci�n estamos ejecutando y en que punto de la animaci�n estamos 
			if (im_->getTexKey() == "Player_BEU_earth_attack3" && im_->getCol() <= 4)
			{
				if (!boxCreated)
				{
					boxes.clear();

					if (im_->getCol() != 4 && im_->getCol() != 0)
					{

						//Para poder cambiar satisfactoriamente la direccion del cuadrado
						if (im_->getFlip() == SDL_FLIP_NONE)
						{
							way = 1;
							boxes.push_back(build_sdlrect(entityTr->getPos().getX() + 15* entityTr->getSW() - mngr_->camRect_.x + (entityTr->getW()) / 2, entityTr->getPos().getY() + (entityTr->getH()) - 45 * entityTr->getSH(), 30*entityTr->getSW(), 30* entityTr->getSH()));

						}
						else
						{
							way = -1;
							boxes.push_back(build_sdlrect(entityTr->getPos().getX() - 40 * entityTr->getSW() - mngr_->camRect_.x + (entityTr->getW()) / 2, entityTr->getPos().getY() + (entityTr->getH()) - 45 * entityTr->getSH(), 30* entityTr->getSW(), 30* entityTr->getSH()));

						}
						boxCreated = true;

					}



				}
				else
				{
					static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0], type, false);
					if (im_->getCol() == 4)
					{
						unsigned timer = clock();
						boxTime = (double(timer) / CLOCKS_PER_SEC);
						boxes.clear();
						boxCreated = false;
					}
				}
			}

			else if (im_->getTexKey() == "Player_BEU_earth_attack3" && im_->getCol() > 4 && im_->getCol() <= 9)
			{
				if (!boxCreated)
				{
					boxes.clear();

					if (im_->getCol() != 9 && im_->getCol() != 0)
					{

						if (im_->getFlip() == SDL_FLIP_NONE)
						{
							boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + 20* entityTr->getSW() + (entityTr->getW()) / 2, entityTr->getPos().getY() + 20 * entityTr->getSH() + (entityTr->getH()) / 2, 30* entityTr->getSW(), 30* entityTr->getSH()));
							way = 1;
						}
						else
						{
							boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 50* entityTr->getSW() + (entityTr->getW()) / 2, entityTr->getPos().getY() + 20 * entityTr->getSH() + (entityTr->getH()) / 2, 30* entityTr->getSW(), 30* entityTr->getSH()));
							way = -1;
						}
						boxCreated = true;

					}
				}
				else
				{
					static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0], type, false);
					if (im_->getCol() == 9)
					{
						unsigned timer = clock();
						boxTime = (double(timer) / CLOCKS_PER_SEC);
						boxes.clear();
						boxCreated = false;

					}
				}
			}

			else if (im_->getTexKey() == "Player_BEU_earth_attack3" && im_->getCol() > 15 && im_->getCol() <= 22)
			{
				if (!boxCreated)
				{
					boxes.clear();


					if (im_->getCol() != 22 && im_->getCol() != 0)
					{

						//Para poder cambiar satisfactoriamente la direccion del cuadrado
						if (im_->getFlip() == SDL_FLIP_NONE)
						{
							boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + 20* entityTr->getSW() + (entityTr->getW()  ) / 2, entityTr->getPos().getY() + 50 * entityTr->getSH() + (entityTr->getH()  ) / 2, 20* entityTr->getSW(), 10* entityTr->getSH()));
							way = 1;
						}
						else
						{
							boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 35* entityTr->getSW() + (entityTr->getW()  ) / 2, entityTr->getPos().getY() + 50 * entityTr->getSH() + (entityTr->getH()  ) / 2, 20* entityTr->getSW(), 10* entityTr->getSH()));
							way = -1;
						}

						boxCreated = true;
					}
				}
				else
				{


					if (im_->getCol() > 17)
					{
						boxes.clear();
						if (way == 1)
						{
							boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + 35 * entityTr->getSW() + (entityTr->getW()) / 2, entityTr->getPos().getY() + 50 * entityTr->getSH() + (entityTr->getH()) / 2, 60 * entityTr->getSW(), 10 * entityTr->getSH()));
							boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + 45 * entityTr->getSW() + (entityTr->getW()) / 2, entityTr->getPos().getY() + (entityTr->getH()) / 2, 40* entityTr->getSW(), 60* entityTr->getSH()));
						}
						else
						{
							boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 90 * entityTr->getSW() + (entityTr->getW()  ) / 2, entityTr->getPos().getY() + 50 * entityTr->getSH() + (entityTr->getH()  ) / 2, 60 * entityTr->getSW(), 10 * entityTr->getSH()));
							boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 80 * entityTr->getSW() + (entityTr->getW()  ) / 2, entityTr->getPos().getY() + (entityTr->getH()  ) / 2, 40* entityTr->getSW(), 60* entityTr->getSH()));
						}
						for (auto i : boxes)
						{
							static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(i, type, false);
						}
					}
					if (im_->getCol() == 22)
					{

						unsigned timer = clock();
						boxTime = (double(timer) / CLOCKS_PER_SEC);
						boxes.clear();
						boxCreated = false;
					}

				}

			}

			else if (im_->getTexKey() == "Player_BEU_earth_super")
			{

				if (im_->getCol() > 3 && im_->getCol() < 5)
				{
					if (!boxCreated)
					{
						if (im_->getFlip() == SDL_FLIP_NONE)
						{
							boxes.push_back(build_sdlrect(entityTr->getPos().getX() + 20 * entityTr->getSW() - mngr_->camRect_.x + entityTr->getW() / 2, entityTr->getPos().getY() + 10 * entityTr->getSH() + entityTr->getH() / 2, 40 * entityTr->getSW(), 40* entityTr->getSH()));
						}
						else
						{
							boxes.push_back(build_sdlrect(entityTr->getPos().getX() - 50 * entityTr->getSW() - mngr_->camRect_.x + entityTr->getW() / 2, entityTr->getPos().getY() + 10 * entityTr->getSH() + entityTr->getH() / 2, 40* entityTr->getSW(), 40* entityTr->getSH()));
						}
						static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0], type, true);
						boxCreated = true;
					}
				}
				else if (im_->getCol() > 5 && im_->getCol() < 17)
				{
					boxes.clear();
					boxCreated = false;
				}
				else if (im_->getCol() > 18 && im_->getCol() < 20)
				{
					if (!boxCreated)
					{

						if (im_->getFlip() == SDL_FLIP_NONE)
						{
							boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + entityTr->getW() / 2, entityTr->getPos().getY() + 10*entityTr->getSH() + entityTr->getH() / 2, 80* entityTr->getSW(), 80* entityTr->getSH()));
						}
						else
						{
							boxes.push_back(build_sdlrect(entityTr->getPos().getX() - 80* entityTr->getSW() - mngr_->camRect_.x + entityTr->getW() / 2, entityTr->getPos().getY() + 10* entityTr->getSW() + entityTr->getH() / 2, 80* entityTr->getSW(), 80* entityTr->getSH()));
						}
						static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0], type, true);
						boxCreated = true;
					}
				}


				if (im_->getCol() == 27)
				{
					unsigned timer = clock();
					boxTime = (double(timer) / CLOCKS_PER_SEC);
					boxes.clear();
					boxCreated = false;
					actualized = false;
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
	}
	else if (im_->getType() == "earth") { // Para el jefe de tierra
		if ((im_->getTexKey() == "GolemFase1_attack" || im_->getTexKey() == "GolemFase2_attack") && im_->getCol() >= 7) {
			if (!boxCreated && im_->getCol() == 7) {
				boxes.clear();

				//Para poder cambiar satisfactoriamente la direccion del cuadrado
				if (im_->getFlip() == SDL_FLIP_NONE) {
					boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 10* entityTr->getSW() + (entityTr->getW()) / 2, entityTr->getPos().getY() + (entityTr->getH()) / 2 - 20 * entityTr->getSH(),
						100 * entityTr->getSW(), 100 * entityTr->getSH()));
				}
				else {
					boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 80 * entityTr->getSW() + (entityTr->getW()  ) / 2, entityTr->getPos().getY() + (entityTr->getH()  ) / 2 - 20 * entityTr->getSH(),
						100 * entityTr->getSW(), 100 * entityTr->getSH()));
				}
				boxCreated = true;
			}
			else {
				if (boxCreated) {
					static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionE(boxes[0], "earth", ent_->getComponent<AttackEarthBossComponent>(ATTACKEARTHBOSSCOMPONENT_H)->getExtraDamage());
				}
				if (im_->getCol() >= 11)
				{
					unsigned timer = clock();
					boxTime = (double(timer) / CLOCKS_PER_SEC);
					boxes.clear();
					boxCreated = false;
				}
			}
		}
		else if ((im_->getTexKey() == "Moose_attack") && im_->getCol() >= 8) {
			if (!boxCreated && im_->getCol() < 16) {
				boxes.clear();

				//Para poder cambiar satisfactoriamente la direccion del cuadrado
				if (im_->getFlip() == SDL_FLIP_NONE) {
					boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + 80 *entityTr->getSW() + (entityTr->getW()) / 2, entityTr->getPos().getY() + (entityTr->getH()) / 2 - 20 * entityTr->getSH(), 100 * entityTr->getSW(), 100 * entityTr->getSW()));
				}
				else {
					boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 170 * entityTr->getSW() + (entityTr->getW()  ) / 2, entityTr->getPos().getY() + (entityTr->getH()  ) / 2 - 20 * entityTr->getSH(), 100 * entityTr->getSW(), 100 * entityTr->getSH()));
				}
				boxCreated = true;
			}
			else {
				if (im_->getCol() < 16) {
					static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionE(boxes[0], "earth", ent_->getComponent<AttackEarthBossComponent>(ATTACKEARTHBOSSCOMPONENT_H)->getExtraDamage());
				}
				else if (im_->getCol() == 16)
				{
					unsigned timer = clock();
					boxTime = (double(timer) / CLOCKS_PER_SEC);
					boxes.clear();
					boxCreated = false;
				}
			}
		}
		else if (im_->getTexKey() == "v1stone1")
		{
			if (!boxCreated) {
				boxes.clear();
				boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + (entityTr->getW()  ) / 2 - 25 * entityTr->getSW(), entityTr->getPos().getY() + (entityTr->getH()  ) / 2 - 25 * entityTr->getSW(), 50 * entityTr->getSW(), 50 * entityTr->getSH()));
				boxCreated = true;
			}
			else {
				boxes[0] = build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + (entityTr->getW()  ) / 2 - 25 * entityTr->getSW(), entityTr->getPos().getY() + (entityTr->getH()  ) / 2 - 25 * entityTr->getSH(), 50 * entityTr->getSW(), 50 * entityTr->getSH());
				boxes[0].x += mngr_->camRect_.x;
				static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionP(boxes[0], "earth", false);
			}
		}
	}
	else if (im_->getType() == "FireBoss") {	//para jefe fuego

		if (im_->getRow() == 2 && im_->getCol() > 3 && im_->getCol() <= 15) {
			if (!boxCreated) {
				boxes.clear();
				for (int i = 0; i < 4; i++) {
					boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + entityTr->getW() / 2, entityTr->getPos().getY() + entityTr->getH(), 40 * entityTr->getSW(), 35* entityTr->getSW()));
				}
				boxCreated = true;

				//Para poder cambiar satisfactoriamente la direccion del cuadrado
				if (im_->getFlip() == SDL_FLIP_HORIZONTAL) {
					way = 1;
					stoppingAngle = 182;
					for (int i = 0; i < boxes.size(); i++)
					{
						angles[i] = 180;
					}
				}
				else {
					way = -1;
					for (int i = 0; i < boxes.size(); i++) {
						angles[i] = 5;
					}
					stoppingAngle = 3.5;
				}
			}
			else {
				for (int i = 0; i < boxes.size(); i++) {

					moveBoxCurve(boxes[i], 80 + 40 * i * entityTr->getSW(), Vector2D(entityTr->getPos().getX() - mngr_->camRect_.x + entityTr->getW() / 2, entityTr->getPos().getY() + entityTr->getH()), 0.04, angles[i], stoppingAngle, way);
					static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionE(boxes[i], type, 0);
				}


				if (im_->getCol() >= 13)
				{
					
					unsigned timer = clock();
					boxTime = (double(timer) / CLOCKS_PER_SEC);
					boxes.clear();
					boxCreated = false;
				}
			}

		}
	}
	else
	{
		if (anim_->getEnemy() == "skeleton")
		{
			if (anim_->getState() == 1)
			{

				if (im_->getFlip() == SDL_FLIP_NONE)
				{

					if (im_->getCol() >= 6 && im_->getCol() < 7 && !boxCreated)
					{
						boxCreated = true;
						boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + (entityTr->getW()  ) / 2, entityTr->getPos().getY() - 30 * entityTr->getSW() + (entityTr->getH()) / 2, 60 * entityTr->getSW(), 40 * entityTr->getSH()));
						static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionE(boxes[0], type, 0);
					}

				}
				else
				{
					if (im_->getCol() >= 6 && im_->getCol() < 7 && !boxCreated)
					{
						boxCreated = true;
						boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 80 * entityTr->getSW() + (entityTr->getW()  ) / 2, entityTr->getPos().getY() - 30*entityTr->getSW() + (entityTr->getH()  ) / 2, 60 * entityTr->getSW(), 40 * entityTr->getSH()));
						static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionE(boxes[0], type, 0);
					}

				}
				if (im_->getCol() == 7)
				{
					unsigned timer = clock();
					boxTime = (double(timer) / CLOCKS_PER_SEC);
					boxes.clear();
				}
			}
			else
			{
				if (boxTime + 300 / 1000 < timerExecution) {
					unsigned timer = clock();
					boxTime = (double(timer) / CLOCKS_PER_SEC);
					boxes.clear();
					boxCreated = false;
				}
			}
		}
		else if (anim_->getEnemy() == "bat" || anim_->getEnemy() == "shroom")
		{

			if (anim_->getState() == 1)
			{
				if (im_->getFlip() == SDL_FLIP_NONE)
				{

					if (im_->getCol() >= 6 && im_->getCol() < 7 && !boxCreated)
					{
						boxCreated = true;
						boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + (entityTr->getW()  ) / 2, entityTr->getPos().getY() - 10 * entityTr->getSH() + (entityTr->getH()  ) / 2, 40 * entityTr->getSW(), 30 * entityTr->getSH()));
						static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionE(boxes[0], type, 0);
					}

				}
				else
				{
					if (im_->getCol() >= 6 && im_->getCol() < 7 && !boxCreated)
					{
						boxCreated = true;
						boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 50 * entityTr->getSW() + (entityTr->getW()  ) / 2, entityTr->getPos().getY() - 10 * entityTr->getSH() + (entityTr->getH()  ) / 2, 40 * entityTr->getSW(), 30 * entityTr->getSH()));
						static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionE(boxes[0], type, 0);
					}

				}
				if (im_->getCol() == 7)
				{
					boxCreated = false;
					unsigned timer = clock();
					boxTime = (double(timer) / CLOCKS_PER_SEC);
					boxes.clear();
				}
			}
			else
			{
				if (boxTime + 300 / 1000 < timerExecution) {
					unsigned timer = clock();
					boxTime = (double(timer) / CLOCKS_PER_SEC);
					boxes.clear();
					boxCreated = false;
				}
			}
		}
		else
		{
			if (anim_->getState() == 1)
			{
				if (im_->getFlip() == SDL_FLIP_NONE)
				{

					if (im_->getCol() >= 6 && im_->getCol() < 7 && !boxCreated)
					{
						boxCreated = true;
						boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x + 10 * entityTr->getSW() * entityTr->getSW() + (entityTr->getW()  ) / 2, entityTr->getPos().getY() - 10 * entityTr->getSH() + (entityTr->getH()  ) / 2, 50 * entityTr->getSW(), 30 * entityTr->getSH()));
						static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionE(boxes[0], type, 0);
					}

				}
				else
				{
					if (im_->getCol() >= 6 && im_->getCol() < 7 && !boxCreated)
					{
						boxCreated = true;
						boxes.push_back(build_sdlrect(entityTr->getPos().getX() - mngr_->camRect_.x - 60* entityTr->getSW() + (entityTr->getW()) / 2, entityTr->getPos().getY() - 10 * entityTr->getSH() + (entityTr->getH()) / 2, 50 * entityTr->getSW(), 30* entityTr->getSH()));
						static_cast<BeatEmUpState*>(mngr_)->getColManager()->checkCollisionE(boxes[0], type, 0);
					}

				}
				if (im_->getCol() == 7)
				{
					boxCreated = false;
					unsigned timer = clock();
					boxTime = (double(timer) / CLOCKS_PER_SEC);
					boxes.clear();
				}
			}
			else
			{
				if (boxTime + 300 / 1000 < timerExecution) {
					unsigned timer = clock();
					boxTime = (double(timer) / CLOCKS_PER_SEC);
					boxes.clear();
					boxCreated = false;
				}
			}
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

	box.x = posCenter.getX() + (int)(radio * cos(angle));
	box.y = posCenter.getY() + (int)(radio * sin(angle));

	box2.x = posCenter.getX() + (int)(radio * cos(angle)) - 10;
	box2.y = posCenter.getY() + (int)(radio * sin(angle)) - 10;
}


#pragma once
#include "CheckCollision.h"
#include "utils/Entity.h"
using namespace std;
cmpId_type p = int(TRANSFORM_H);

CheckCollision::CheckCollision(PlayerTD* player, GameManager* gm_) :Component() {
	player_ = player;
	gm = gm_;
}

CheckCollision::CheckCollision(PlayerTD* player,GameManager* gm_, float lookingRange, float lookingWidth, float side) :Component() {
	player_ = player;
	gm = gm_;
	side_ = side;								//side==-1 ------>mira a la derecha					//			side==1-------->mira a la izquierda
	lookingRange_ = lookingRange;
	lookingHeight_ = lookingWidth;

}
void CheckCollision::initComponent() {
	tr1 = ent_->getComponent<Transform>(p);
	tr2 = player_->getComponent<Transform>(p);

	lookingRange_ *=side_;
	offset = tr1->getW() / 7;
	if (side_==1)
	{
		offset = (tr1->getW() / 7)-60;
	}
	




	rectPlayer = getPlayerRect();
	rectFight = getRectFight();														
	rectDetection = getRectDetection();
}
void CheckCollision::update() 
{
	
	if (ent_->getComponent<Transform>(p))
	{
    	if (Collision::collides(Vector2D(rectPlayer.x,rectPlayer.y), rectPlayer.w,rectPlayer.h, Vector2D(rectFight.x,rectFight.y),rectFight.w,rectFight.h))					//Aumentado el numero por el que dividimos las alturas y anchuras, tambien aumentamos lo que tarda en detectarnos el enemigo
		{
			cout << "FIGHT!";
		}
		else if (Collision::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, Vector2D(rectDetection.x, rectDetection.y), rectDetection.w, rectDetection.h))
		{
			cout << "as";

			//SDLUtils::instance()->soundEffects().at("prueba").play();
		}
	}
	else
	{
		cout << "LO QUE HACE EL NPC";
		
	}
	updateRects();
	
	/*SDL_Rect mierda=build_sdlrect(tr1->getPos().getX() + offset * -side_, tr1->getPos().getY() - (lookingHeight_ / 2) / 2, lookingRange_ + 50 * side_, tr1->getH() + lookingHeight_ / 2
	if(Collision::collides(,)
	{
		cout << "PUTA MIERDA";
	}*/
	
}


void CheckCollision::render()
{ 

	SDL_SetRenderDrawColor(gm->getRenderer(), 0, 255, 0, 0);							//	Renderizamos el rectángulo del player
	SDL_RenderDrawRect(gm->getRenderer(), &rectPlayer);
	
	SDL_SetRenderDrawColor(gm->getRenderer(), 120, 50, 255, 0);							//	Renderizamos el rectángulo de detección del enemigo
	SDL_RenderDrawRect(gm->getRenderer(), &rectDetection);


	SDL_SetRenderDrawColor(gm->getRenderer(), 225, 100, 255, 0);
	SDL_RenderDrawRect(gm->getRenderer(), &rectFight);									// Renderizamos el rectángulo de combate del enemigo
	

	SDL_SetRenderDrawColor(gm->getRenderer(), 0, 0, 0, 255);							//ponemos el fondo a negro
}

void CheckCollision::updateRects()														
{
	rectFight = getRectFight();
	rectPlayer = getPlayerRect();
														//Método para actualizar los rectángulos
	rectDetection= getRectDetection();
}
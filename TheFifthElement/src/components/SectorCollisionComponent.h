//#pragma once
//#ifndef SECTORCOLLISIONCOMPONENT_H_
//#define SECTORCOLLISIONCOMPONENT_H_
//#include "Transform.h"
//#include "../utils/Vector2D.h"
//#include "../utils/Collision.h"
//#include "../sdlutils/SDLUtils.h"
//#include "../GameManager.h"
//#include "../utils/Entity.h"
//#include "../states/TopDownState.h"
//#include "../utils/ecs.h"
//
//
//class SectorCollisionComponent : public Component 
//{
//private:
//	Entity* player_;
//	Transform* tr1;
//	Transform* tr2;
//	SDL_Rect rectPlayer, rectSector;
//	int idSector;
//public:
//	virtual ~SectorCollisionComponent() {};
//	inline SDL_Rect getPlayerRect() { return build_sdlrect(tr2->getPos(), tr2->getW(), tr2->getH()); }
//	inline SDL_Rect getRectSector() { return build_sdlrect(tr1->getPos(), tr1->getW(), tr1->getH()); }
//	void traspaso(int id, bool nowSector);
//	SectorCollisionComponent(Entity* player, int sector)
//	{
//		player_ = player;
//		idSector = sector;
//	}
//	void initComponent() 
//	{
//		//Hacemos los getComponent de los Transform
//		tr1 = ent_->getComponent<Transform>(TRANSFORM_H);
//		tr2 = player_->getComponent<Transform>(TRANSFORM_H);
//		rectSector = getRectSector();
//		rectPlayer = getPlayerRect();
//		//rectPlayer= build_sdlrect(player_->getComponent<Transform>(TRANSFORM_H)->getPos(), player_->getComponent<Transform>(TRANSFORM_H)->getW(), player_->getComponent<Transform>(TRANSFORM_H)->getH());
//	}
//	void update()
//	{
//		if (Collision::collides(Vector2D(rectPlayer.x, rectPlayer.y), rectPlayer.w, rectPlayer.h, Vector2D(rectSector.x, rectSector.y), rectSector.w, rectSector.h))
//		{
//			traspaso(idSector, true);			
//		}
//		else { traspaso(idSector, false); }
//		updateRects();
//	}
//	void updateRects()
//	{
//		//Modo para actualizar los rect?gulos
//		rectPlayer = getPlayerRect();
//		rectSector = getRectSector();
//	}
//};
//
//
//#endif
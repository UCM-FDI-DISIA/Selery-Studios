#pragma once
#include "utils/Manager.h"
#include "utils/Collision.h"
#include "components/Transform.h"
#include "components/LifeComponent.h"


//Este manager existira en la escena y sera el encargado de gestionar los ataques jugador->enemigo y enemigo->jugador
//Su constructora recibe un puntero al manager para acceder a lalista de entidades, como hacemos en TPV2.

//Sus unicos metodos, recibiran la caja del ataque y comprobara si choca con algun objetivo, este metodo debe ser llamado en el AttackBoxComponent
class ColManager
{
private:
	Manager* mngr_;
public:

	ColManager(Manager* manager): mngr_(manager) {};
	void checkCollisionP(SDL_Rect boxAttack);

};


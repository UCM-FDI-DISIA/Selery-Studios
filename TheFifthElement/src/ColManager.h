#pragma once
#include "utils/Manager.h"
#include "utils/PropertiesManager.h"
#include "utils/Collision.h"
#include "components/ColliderComponent.h"
#include "components/LifeComponent.h"
#include "components/LifeEarthBossComponent.h"
#include "components/WaterBossLife.h"
#include "components/FireBossComponent.h"
#include "components/LifeBasicComponent.h"


//Este manager existira en la escena y sera el encargado de gestionar los ataques jugador->enemigo y enemigo->jugador
//Su constructora recibe un puntero al manager para acceder a lalista de entidades, como hacemos en TPV2.

//Sus unicos metodos, recibiran la caja del ataque y comprobara si choca con algun objetivo, este metodo debe ser llamado en el AttackBoxComponent
class ColManager
{
private:
	Manager* mngr_;
	PropertiesManager* props_;
	int enemiesNearPlayer = 0;
public:
	ColManager(Manager* manager) : mngr_(manager) {};
	void checkCollisionP(SDL_Rect boxAttack, string type, bool strongAttack);
	void checkCollisionE(SDL_Rect boxAttack, string type, int extraDamage);

	void update();
	int howManyNear();

};


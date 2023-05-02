#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/PropertiesManager.h"
#include "../ColManager.h"
#include "../components/AttackBoxComponent.h"
#include "../components/AnimationEnemyBEUComponent.h"
#include "../components/Transform.h"
#include "../components/InputComponent.h"
#include "../components/LifeComponent.h"
#include "../components/MovementComponent.h"
#include "../components/EnemyBEUDirectionComponent.h"
#include "../components/ColliderComponent.h"
#include "../components/ColDetectorComponent.h"
#include "../components/JumpComponent.h"
#include "../components/InputComponentBEU.h"
#include "../components/LimitBEU.h"
#include "../components/Image.h"
#include "../components/MovementEarthBossComponent.h"
#include "../components/AnimationEarthBossComponent.h"
#include "../components/LifeEarthBossComponent.h"
#include "../Saving.h"
#include "../components/PointOfFightComponent.h"
#include "../components/ShadowComponent.h"
#include "../components/AttackEarthBossComponent.h"
#include "../components/rouletteComponent.h"
#include "../components/MovementLightBossComponent.h"
#include "../components/LifeLightBossComponent.h"
#include "../components/AttackLightBossComponent.h"
#include "../components/AnimationLightBossComponent.h"
#include "../components/WaterBossIA.h"
#include "../components/WaterBossLife.h"
#include "../components/FireBossComponent.h"
#include "../components/PowerUpControler.h"
#include "../Quests.h"

using name = string;
using damage = int;


class SkinBEUComponent;
class BeatEmUpState: public Manager {
private:
	//PLAYER
	Entity* player_;
	SkinBEUComponent* sk_;
	Transform* trans_player_;
	InputComponentBEU* in_;
	Texture* texture_player_;
	Saving* savePos;

	//BACKGROUND
	Entity* background_;
	RandomNumberGenerator* random;

	//ENEMIGOS
	Entity* enemy_;
	AnimationEnemyBEUComponent* animation_;
	Texture* enemy_texture;
	int shakeme;
	int numEnemies;
	float timeNextGeneration;
	const int delayGenerateEnemies = 15000;
	Entity* enemySender;

	//COLISIONES
	ColManager* colManager_;
	Entity* lifebar_;
	float camOffset_ = WIN_WIDTH/3;
	float enemy_width=0, enemy_height=0;
	float scale;

	//HUD
	Entity* Hud_;
	Roulette* roulete;

	//BOSSES
	int fireBossBackgroundWidth;
	bool lockCameraX;
	Entity* earthBoss_;
	bool boss;
	string typeBoss_ = "";

	//PROPERTIES
	bool Shakemyass = false;
	PropertiesManager* props_;

public:
	BeatEmUpState(bool Boss = false, Entity* enemySends = nullptr, string typeBoss = "", int nEnemies = 3, int timeGen = 1000);
	virtual ~BeatEmUpState() { delete colManager_; }
	string getStateID(); // stringID
	void AddEnemies(int i);
	void AddEnemy();
	void AddWaterBoss();
	void AddFireBoss();
	void AddLightBoss();
	void AddEarthBoss();
	string getEnemyType(int i);
	void finishBEU();
	void handleEvents();
	inline Entity* getPlayer() { return player_; }
	ColManager* getColManager() { return colManager_; }
	void update();
	void Background(string file);
	void ShakeCam(bool shakeyourbooty);
};


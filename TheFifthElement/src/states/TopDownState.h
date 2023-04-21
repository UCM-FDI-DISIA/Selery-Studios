#pragma once
#include "../utils/PropertiesManager.h"
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include "GameState.h"
#include "../components/Playernpc.h"
#include "../components/InputComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../include/SDL_mixer.h"
#include "../components/PortalComponent.h"
#include "../components/ColliderTile.h"
#include "../components/CollideTileInteraction.h"
#include "../PuzzleCopas.h"
#include "../components/NPCcollisioncomponent.h"
#include "../components/Transform.h"
#include "../sdlutils/Texture.h"
#include "../GameManager.h"
#include "../components/InputComponent.h"
#include "../components/MovementComponent.h"
#include "../components/Image.h"
#include "../components/SkinComponent.h"
#include "../components/CheckCollision.h"
#include "../components/LifeComponent.h"
#include "../components/Enemy_movementTD_component.h"
#include "../components/ColliderComponent.h"
#include "../components/ObjectsComponent.h"
#include "../components/Button.h"
#include "../components/ShopComponent.h"
#include "../components/RedirectEnemy.h"
#include "../components/DialogueComponent.h"
#include "../components/EconomyComponent.h"
#include "../components/Damage.h"
#include "../components/LifeTD.h"
#include "../components/rouletteComponent.h"
#include "../components/SectorCollisionComponent.h"
#include "../components/BossCollision.h"
#include "../Saving.h"
#include "../components/QuestInfoComponent.h"

using uint = unsigned int;
using tileset_map = std::map<std::string, Texture*>; //mapa con CLAVE:string, ARGUMENTO: puntero a textura
using tilelayer = tmx::TileLayer;

struct MapInfo {
	tmx::Map* tile_MAP;//mapa
	string path;	//ruta
	int rows, cols;	//fila columna
	int tile_width, tile_height;	//ancho y alto del tile
	map<uint, Texture*> tilesets;	//mapa con CLAVE: int, ARGUMENTO: puntero a textura
	//MapInfo() {
	//	tile_MAP = nullptr;
	//	path = "";
	//	rows = cols = tile_width = tile_height = 0;
	//	//tilesets
	//}
	~MapInfo() {
		if (tile_MAP != nullptr)
			delete tile_MAP;
	}
};

class TopDownState : public Manager {
private:
	//TILE
	tileset_map tilesets_;	// textures map (string -> texture)
	SDL_Texture* background_0;
	SDL_Texture* background_1;
	SDL_Texture* background_2;
	SDL_Texture* background_3;
	//SDL_Texture* background_;
	MapInfo mapInfo;	//struct
	vector<bool> sectors{ true,false,false,false };
	Entity* pruebaCollider;
	int idSector = 0;
	//PLAYER 
	Entity* player_;
	Transform* trans_player_;
	InputComponent* in_;
	SkinComponent* sk_;
	Texture* texture_player_;
	PlayerNPC* Playernpc_;
	int contnpc = 4;
	MovementComponent* movcomp_player_;
	//NPCS
	Entity* Npc_;
	Entity* Contexto;
	Entity* Blacksmith_;
	int contBlksm = 0;
	//HUD
	Entity* Hud_;
	EconomyComponent* economyComp_;
	Roulette* roulete;
	Damage* damage_;
	LifeTD* life_;
	
	//ENEMIGOS 
	vector<Entity*> enemies_;
	Entity* redirect_;
	SDL_Rect redBox_;
	Entity* enemy_;
	float enemy_width, enemy_height;
	string type_;

	//Boss
	Entity* boss_;

	Saving* save_;
	GameManager* Gm_;

	//COLISIONES TILE-PLAYER
	vector<Entity*> collisions_; //vector colision player-mapa
	vector<ColliderTileInteraction*> interactions_; //vector colision player-mapa
	float camOffset_ = 60.0f;

	int fondowidth_, fondoheight_;

	DialogueComponent* dialog_;

	// SHOP
	Entity* upturnButton_;
	Entity* exitShopButton_;
	vector<Entity*> buttons1;
	vector<Entity*> buttons2;
	vector<Button*> buttonsComp;
	ShopComponent* shopComp_;
	Vector2D upturnButtonPos_;
	int upturnButtonX, upturnButtonY;
	int upturnButtonWidth_, upturnButtonHeight_;
	int upturnButtonOffsetX = 57;
	int upturnButtonOffsetY = 20;
	Transform* upturnButtonTr_;
	Button* upturnButtonComp_;
	Transform* exitShopButtonTr_;
	Button* exitShopButtonComp_;

	list<Entity*> quests;

	//void actSectors(int idChange, bool nowValue)
	//{
	//	if (sectors[idChange] != nowValue)
	//	{
	//		sectors[idChange] = nowValue;
	//		printMap();
	//	}
	//	//printMap();
	//}
	bool saved = false;
	bool shopCreated_ = false;
	bool loadGame = false;
	bool questsMenu = false;

public:
	string getStateID(); // stringID
	PuzzleCopas* puzzle1;
	TopDownState();	
	~TopDownState();
	void LoadMap(string const& filename);
	void LoadGame();
	//void printMap();
	void DeleteContexto() {
		Contexto->setAlive(false);
	}
	void SaveGame();
	void update();	
	void handleEvents();
	void render();
	void createShopButtons();
	void cleanShopButtons();
	void newQuest(string nombre, string text, string reward, int coins = 0, int fases = 0);
	void completedQuest(string nombre);
	void actQuests();
	void renderQuestList();
	Texture* npcTexture() {
		int a = SDLUtils::instance()->rand().nextInt(1, 11);
		return &SDLUtils::instance()->images().at("NPC_"+ to_string(a));
	}
	Texture* blacksmithTexture() {
		return &SDLUtils::instance()->images().at("Blacksmith");
	}
	Texture* bossLuzTexture()
	{
		return &SDLUtils::instance()->images().at("TDLightBoss");
	}
	Texture* EnemyTexture() {
		int a = SDLUtils::instance()->rand().nextInt(0, 4);
		if (a == 0) {
			enemy_width = 68;            //habra que cambiar el ancho y alto de cada enemigo dependiendo de cual sea
			enemy_height = 120;
			type_ = "mushroom";
			return &SDLUtils::instance()->images().at("TD_mushroom_idle");
		}
		else if (a == 1) {
			enemy_width = 68;
			enemy_height = 120;
			type_ = "goblin";
			return &SDLUtils::instance()->images().at("TD_goblin_idle");
		}
		else if (a == 2) {
			enemy_width = 68;
			enemy_height = 120;
			type_ = "bat";
			return &SDLUtils::instance()->images().at("TD_bat_idle");
		}
		else if (a == 3) {
			enemy_width = 86;
			enemy_height = 150;
			type_ = "skeleton";
			return &SDLUtils::instance()->images().at("TD_skeleton_idle");
		}

	}
	Entity* getplayer() { return player_; };
	ShopComponent* getShopComp() { return shopComp_; }
	DialogueComponent* getDialog() { return dialog_; }
	Button* getShopButton(int i) { return buttonsComp.at(i); }
	SkinComponent* getPlayerSkin() { return sk_; }
	bool getMenuQuest() { return questsMenu; }
	void setMenuQuest(bool b) { questsMenu = b; }
};


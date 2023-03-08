#pragma once
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include "GameState.h"
#include "../components/InputComponent.h"
#include "../Entities/DialogBox.h"
#include "../Entities/Element.h"
#include "../sdlutils/SDLUtils.h"
#include "../include/SDL_mixer.h"
#include "../Entities/RedirectTile.h"
#include "../Entities/PortalComponent.h"
#include "../components/ColliderTile.h"
#include "../components/CollideTileInteraction.h"
#include "../PuzzleCopas.h"
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
	SDL_Texture* background_;
	MapInfo mapInfo;	//struct
	//PLAYER 
	Entity* player_;
	Transform* trans_player_;
	InputComponent* in_;
	SkinComponent* sk_;
	Texture* texture_player_= &SDLUtils::instance()->images().at(sk_->getSkin());
	
	//NPCS
	Entity* Npc_;
	//Transform* Nptr_;
	int number_npc_ = 0;
	//ENEMIGOS 
	Entity* enemy_;
	float enemy_width, enemy_height;

	GameManager* Gm_;

	//PORTAL
	Entity* portal_;
	//ELEMENT
	Entity* element_;
	//DIALOGO
	bool dialog_;

	//COLISIONES TILE-PLAYER
	vector<ColliderTile*> collisions_; //vector colision player-mapa
	vector<ColliderTileInteraction*> interactions_; //vector colision player-mapa
	float camOffset_ = 60.0f;

	int fondowidth_, fondoheight_;
public:
	string getStateID(); // stringID
	DialogBox* d;
	PuzzleCopas* puzzle1;
	TopDownState();	
	~TopDownState() {}
	void LoadMap(string const& filename);
	void dialog(int a);	
	void update();	
	void handleEvents();
	void render();
	Texture* npcTexture() {
		int a = SDLUtils::instance()->rand().nextInt(0, 1);
		if (a == 0) {
			return &SDLUtils::instance()->images().at("NPC_1");
		}
		else if (a == 1) {
			return &SDLUtils::instance()->images().at("NPC_2");
		}
		
	}
	Texture* EnemyTexture() {
		int a = SDLUtils::instance()->rand().nextInt(0, 3);
		if (a == 0) {
			return &SDLUtils::instance()->images().at("TD_wind_mushroom");
			enemy_width = 68;			//habra que cambiar el ancho y alto de cada enemigo dependiendo de cual sea
			enemy_height =120;
		}
		else if (a == 1) {
			return &SDLUtils::instance()->images().at("TD_wind_goblin");
			enemy_width = 68;
			enemy_height = 120;
		}
		else if (a == 2) {
			return &SDLUtils::instance()->images().at("TD_wind_bat");
			enemy_width = 68;
			enemy_height = 120;

		}
		else if (a == 3) {
			return &SDLUtils::instance()->images().at("TD_wind_skeleton");
			enemy_width = 68;
			enemy_height = 120;

		}

	}
	Entity* getplayer() { return player_; };
};


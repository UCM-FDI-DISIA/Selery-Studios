#pragma once
#include "GameState.h"
#include "../Entities/Npc.h"
#include "../Entities/PlayerTD.h"
#include "../Entities/Enemy.h"
#include "../Entities/PlayerBEU.h"
#include "../components/InputComponent.h"
#include "../components/InputComponentBEU.h"
#include "../Entities/DialogBox.h"
#include "../Entities/Portal.h"
#include "../Entities/Element.h"
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include "../sdlutils/SDLUtils.h"
//#include "../Entities/Camera.h"
#include "../include/SDL_mixer.h"
#include "../Entities/RedirectTile.h"
#include "../components/ColliderTile.h"
#include "../components/CollideTileInteraction.h"
#include "../PuzzleCopas.h"
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
	Enemy* enemy_;
	GameManager* Gm_;
	PlayerTD* player_;
	InputComponent* in_;
	PlayerBEU* playerBEU_;
	InputComponentBEU* inBEU_;
	tileset_map tilesets_; // textures map (string -> texture)
	SDL_Texture* background_;
	MapInfo mapInfo;//struct
	bool dialog_;
	/*Camera* cam_;*/
	Portal* p;
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
};


#pragma once
#include "GameState.h"
#include "../Npc.h"
#include "../PlayerTD.h"
#include "../Enemy.h"
#include "../PlayerBEU.h"
#include "../InputComponent.h"
#include "../InputComponentBEU.h"
#include "../DialogBox.h"
#include "../Camera.h"
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"

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
public:
	virtual string getStateID() { return "top-down"; }; // stringID

	TopDownState(GameManager* gm_) {
		Gm_ = gm_;
		LoadMap("assets/MapAssets/tiledPrueba.tmx");
		player_ = addEntity(new PlayerTD(Gm_));
		dialog_ = false;
		addEntity(new Npc(Gm_, player_));
		//playerBEU_ = new PlayerBEU(Gm_);

	//	cmpId_type b = int(INPUTCOMPONENTBEU_H);
		//inBEU_ = playerBEU_->getComponent<InputComponentBEU>(b);
		cmpId_type w = int(INPUTCOMPONENT_H);
		in_ = player_->getComponent<InputComponent>(w);
		
		//addEntity(playerBEU_);
		//addEntity(new DialogBox(Gm_));
		addEntity(new Enemy(Gm_, player_, 100));
		//cam_ = addEntity(new Camera(Gm_, player_));
		addEntity(new Camera(Gm_, player_));

	}
	void LoadMap(string const& filename);
	void dialog(int a) {
		if (dialog_ == false ) {
			addEntity(new DialogBox(Gm_, a));
			dialog_ = true;
		}
		else {
			
		}
	}
	void handleEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			in_->handleEvents(event);
			//inBEU_->handleEvents(event);
;		}
	}
	~TopDownState() {

	}
	void render();
private:
	GameManager* Gm_;
	PlayerTD* player_;
	InputComponent* in_;
	PlayerBEU* playerBEU_;
	InputComponentBEU* inBEU_;
	/*Camera* cam_;*/
	/*Entity* cam_;*/
	/*Manager* mngr_;*/
	tileset_map tilesets_; // textures map (string -> texture)
	SDL_Texture* background_;
	MapInfo mapInfo;//struct
	bool dialog_;
};


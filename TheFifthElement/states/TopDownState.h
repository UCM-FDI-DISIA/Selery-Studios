#pragma once
#include "GameState.h"
#include "../Npc.h"
#include "../PlayerTD.h"
#include "../Enemy.h"
#include "../map/ColisionTile.h"
#include <map>
#include <vector>
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include ".././RenderComponent.h"
#include "./../Transform.h"




#define TILE_SIZE 16

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
		addEntity(new Npc(Gm_));
		player_ = new PlayerTD(Gm_);
		addEntity(player_);
		addEntity(new Enemy(Gm_,player_));
		LoadMap("assets/MapAssets/tiledPrueba.tmx");
		//.\\Src\\TilemapSrc\\MainMap.tmx
		/*Transform* transform = new Transform({ 0,0 }, { 0,0 }, 100, 100, 0);
		int uno = 1;
		Texture* t = new Texture(Gm_->getRenderer(), background_, 100, 100);
		RenderComponent* render = new RenderComponent(t, transform, uno);
		render->render();
		SDL_RenderPresent(Gm_->getRenderer());*/
	}
	~TopDownState() {}
	void LoadMap(string const& filename);
private:
	GameManager* Gm_;
	PlayerTD* player_;


	vector<ColisionTile*> collisions_;
	vector<Enemy*>enemyContainer_;//aqui irán los enemigos que habra en el topdown con los que se interactuarán
	MapInfo mapInfo;//struct
	tileset_map tilesets_; // textures map (string -> texture)
	SDL_Texture* background_;
};


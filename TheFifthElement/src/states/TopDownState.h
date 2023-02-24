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
#include "../Entities/Camera.h"
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
	string getStateID(); // stringID
	DialogBox* d;
	TopDownState() {
		LoadMap("assets/MapAssets/MapaInicial.tmx");
		player_ = addEntity(new PlayerTD());
		dialog_ = false;
		addEntity(new Npc(player_,{0,10},&SDLUtils::instance()->images().at("NPC_1")));
		addEntity(new Npc(player_, { 50,10 }, &SDLUtils::instance()->images().at("NPC_2")));
		//playerBEU_ = new PlayerBEU(Gm_);

	//	cmpId_type b = int(INPUTCOMPONENTBEU_H);
		//inBEU_ = playerBEU_->getComponent<InputComponentBEU>(b);
		cmpId_type w = int(INPUTCOMPONENT_H);
		in_ = player_->getComponent<InputComponent>(w);
		
		//addEntity(playerBEU_);
		//addEntity(new DialogBox(Gm_));
		addEntity(new Enemy(player_, 100));
		cam_ = addEntity(new Camera(player_)); // entidad de camara
		Portal* p = addEntity(new Portal(player_));
		addEntity(new Element(player_, Vector2D(100, 100), p));
		addEntity(new Element(player_, Vector2D(300, 100), p));
		addEntity(new Element(player_, Vector2D(200, 200), p));
		
	}
	void LoadMap(string const& filename);
	void dialog(int a) {
		if (dialog_ != false) {
			in_->changebool();
			cout << "sd"<<endl;
			d->~DialogBox();//cris hija haz delete(d)
			dialog_= false;
		}
		else  {
			d = new DialogBox(a);
			addEntity(d);
			dialog_ = true;
			cout << "d" << endl;

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
	tileset_map tilesets_; // textures map (string -> texture)
	SDL_Texture* background_;
	MapInfo mapInfo;//struct
	bool dialog_;
	Camera* cam_;
};

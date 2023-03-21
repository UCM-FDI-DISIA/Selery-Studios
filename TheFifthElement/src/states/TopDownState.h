#pragma once
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include "GameState.h"
#include "../components/Playernpc.h"
#include "../components/InputComponent.h"
#include "../Entities/DialogBox.h"
#include "../Entities/Element.h"
#include "../sdlutils/SDLUtils.h"
#include "../include/SDL_mixer.h"
#include "../Entities/PortalComponent.h"
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
	Texture* texture_player_;
	PlayerNPC* Playernpc_;
	int contnpc = 0;
	//NPCS
	Entity* Npc_;
	//Transform* Nptr_;
	int number_npc_ = 0;
	
	
	//ENEMIGOS 
	vector<Entity*> enemies_;
	Entity* redirect_;
	SDL_Rect redBox_;
	Entity* enemy_;
	float enemy_width, enemy_height;
	string type_;

	GameManager* Gm_;
	
	//DIALOGO
	bool dialog_;

	//COLISIONES TILE-PLAYER
	vector<Entity*> collisions_; //vector colision player-mapa
	vector<ColliderTileInteraction*> interactions_; //vector colision player-mapa
	float camOffset_ = 60.0f;

	int fondowidth_, fondoheight_;

	
	#pragma region SHOP
	// Entidad de tienda
	Entity* shop_;
	// Entidades botones
	Entity* upturnButtonFireAtt_;
	Entity* upturnButtonWaterAtt_;
	Entity* upturnButtonEarthAtt_;
	Entity* upturnButtonAirAtt_;
	Entity* upturnButtonFireHP_;
	Entity* upturnButtonWaterHP_;
	Entity* upturnButtonEarthHP_;
	Entity* upturnButtonAirHP_;
	Entity* exitShopButton_;

	// Propiedades tienda
	Transform* shopTr_;
	bool openShop_ = false;
	Transform* upturnButtonTr_;
	int upturnButtonX, upturnButtonY;
	int upturnButtonWidth_, upturnButtonHeight_;
	int upturnButtonOffsetX = 165;
	int upturnButtonOffsetY = 150;
	Vector2D upturnButtonPos_;

	// Transform Botones
	Transform* upturnButtonAirAttTr_;
	Transform* upturnButtonFireAttTr_;
	Transform* upturnButtonWaterAttTr_;
	Transform* upturnButtonEarthAttTr_;
	Transform* upturnButtonAirHPTr_;
	Transform* upturnButtonFireHPTr_;
	Transform* upturnButtonWaterHPTr_;
	Transform* upturnButtonEarthHPTr_;
	Transform* exitShopButtonTr_;

	// Tipo Botones
	Button* upturnButtonComp1_;
	Button* upturnButtonComp2_;
	Button* upturnButtonComp3_;
	Button* upturnButtonComp4_;
	Button* upturnButtonComp5_;
	Button* upturnButtonComp6_;
	Button* upturnButtonComp7_;
	Button* upturnButtonComp8_;
	Button* exitShopButtonComp_;

	// Texto mejoras
	int u1 = 0;
	int u2 = 0;
	int u3 = 0;
	int u4 = 0;
	int u5 = 0;
	int u6 = 0;
	int u7 = 0;
	int u8 = 0;
	Font* font_;
	string textUp_;
	int textX = 150;
	int textY = 200;
	SDL_Color color_;

	//Texto monedas
	EconomyComponent* economyComp_;
	int price1_ = 10;
	int price2_ = 10;
	int price3_ = 10;
	int price4_ = 10;
	int price5_ = 10;
	int price6_ = 10;
	int price7_ = 10;
	int price8_ = 10;
	string textCoin_;

	// Avatares
	Entity* shopFrame_;
	Entity* airAvatar_;
	Entity* fireAvatar_;
	Entity* waterAvatar_;
	Entity* earthAvatar_;
	Transform* shopFrameTr_;
	Transform* airAvatarTr_;
	Transform* fireAvatarTr_;
	Transform* waterAvatarTr_;
	Transform* earthAvatarTr_;
	Vector2D shopFramePos_;
	#pragma endregion

	


	//HUDTD* hudTD = new HUDTD();
public:
	string getStateID(); // stringID
	//DialogBox* d;
	PuzzleCopas* puzzle1;
	TopDownState();	
	~TopDownState() {}
	void LoadMap(string const& filename);
	void dialog(int a);	
	void update();	
	void handleEvents();
	void render();
	void createShopButtons();
	void createExitShopButton();
	void createUpgradeText(int value, int offsetX, int offsetY, int offsetXcoin, int offsetYcoin, int price);
	int increase(int& o);
	void shopEconomy();
	void showAvatar(Entity* entity, Transform* transform, int i, string id);
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

};


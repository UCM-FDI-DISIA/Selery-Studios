#pragma once
using uint = unsigned int;

const uint WIN_WIDTH = 900; // anchura de ventana
const uint WIN_HEIGHT = 600; // altura de ventana
const float FRAME_RATE = 3.0f; // número de frames que tardará en actualizarse el juego

const uint PLAYERBEU_WIDTH_FRAME = 208; // anchura de PlayerBEU
const uint PLAYERBEU_HEIGHT_FRAME = 128; // altura de PlayerBEU
const uint PlayerPosition_X =30; //pos inicial de PlayerBEU
const uint PlayerPosition_Y = 300;
const float speed_ = 1.0f; //velocidad PlayerBEU


const uint PLAYERTD_WIDTH_FRAME = 68; // anchura de PlayerTD
const uint PLAYERTD_HEIGHT_FRAME = 120; // altura de PlayerTD
const float PLAYERTD_SPEED = 3.0f; //velocidad PlayerTD
const uint PLAYERTD_NUMFRAMES = 7; //numero de frames PlayerTD

const uint BACKGROUNDAIR_WIDTH_FRAME = 3840; // anchura de BackgroundAir
const uint BACKGROUNDAIR_HEIGHT_FRAME = 2160; // altura de BackgroundAir

const uint DIALOGUE_WIDTH = 1200; // anchura de Dialogue
const uint DIALOGUE_HEIGHT = 852; // anchura de Dialogue

const uint ELEMENT_WIDTH = 64; // anchura de Element
const uint ELEMENT_HEIGHT = 64; // altura de Element

//const uint ENEMYTD_WIDTH = 68; // anchura de EnemyTD
//const uint ENEMYTD_HEIGHT = 120; // altura de EnemyTD
const uint ENEMYTD_NUMFRAMES = 7; //numero de frames EnemyTD
const uint ENEMYBEU_MAXLIFE = 10;//maxima vida de enemigos

const uint ENEMYBEU_WIDTH = 150; // anchura de EnemyBEU
const uint ENEMYBEU_HEIGHT = 150; // altura de EnemyBEU

const uint NPC_WIDTH = 68; // anchura de NPC
const uint NPC_HEIGHT = 120; // altura de NPC
const uint NPC_FRAMES = 7; // frame del npcs

const uint PORTAL_WIDTH = 290; // anchura de Portal
const uint PORTAL_HEIGHT = 192; // altura de Portal

#pragma region enemy_data

const int enemy_fire_dmg = 200;
const int enemy_water_dmg = 150;
const int enemy_wind_dmg = 175;
const int enemy_rock_dmg = 200;

const int enemy_fire_life = 300;
const int enemy_water_life = 270;
const int enemy_wind_life = 190;
const int enemy_rock_life = 200;

#pragma endregion

#pragma region EarthBoss_data

const int EARTHBOSS_WIDTH = 224;
const int EARTHBOSS_HEIGHT = 192;

#pragma endregion

// SHOP
const uint SHOP_WIDTH = 747;
const uint SHOP_HEIGHT = 876;
const uint UPTURNBUTTON_WIDTH = 88;
const uint UPTURNBUTTON_HEIGHT = 84;
/*const string FUEGO = "fire";
const string AIRE = "wind";
const string AGUA = "water";
const string TIERRA = "earth";

const string SETA = "shroom";
const string ESQUELETO = "skeleton";
const string DUENDE = "goblin";
const string MURCIELAGO = "bat";*/
	


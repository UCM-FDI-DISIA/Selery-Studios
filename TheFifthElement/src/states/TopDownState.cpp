﻿#include "TopDownState.h"


TopDownState::TopDownState() {
    puzzle1 = new PuzzleCopas();
     dialog_ = false;
    LoadMap("assets/Scenes/Maps/MapaInicial.tmx");

   /* addEntity(new Element(player_, Vector2D(100, 100), p));
    addEntity(new Element(player_, Vector2D(300, 100), p));
    addEntity(new Element(player_, Vector2D(200, 200), p));*/


    // PRUEBAS PATHING ENEMIGO
    //addEntity(new RedirectTile(Vector2D(1, 0), Vector2D(680, 170), enemy_)); //der
    //addEntity(new RedirectTile(Vector2D(0, 1), Vector2D(870, 170), enemy_)); //ab
    //addEntity(new RedirectTile(Vector2D(-1, 0), Vector2D(870, 360), enemy_)); //iz
    //addEntity(new RedirectTile(Vector2D(0, -1), Vector2D(680, 360), enemy_)); //arr
}

void TopDownState::LoadMap(string const& filename) {

    mapInfo.tile_MAP = new tmx::Map();  //crea el mapa
    mapInfo.tile_MAP->load(filename);   // CARGA DE INFO DESDE EL .TMX


    tmx::Vector2u mapsize_ = mapInfo.tile_MAP->getTileCount();    // TAMAÑO MAPA
    mapInfo.rows = mapsize_.y;
    mapInfo.cols = mapsize_.x;


    tmx::Vector2u tilesize_ = mapInfo.tile_MAP->getTileSize();   // TAMAÑO TILE
    mapInfo.tile_width = tilesize_.x;
    mapInfo.tile_height = tilesize_.y;


    int fondowidth_ = mapInfo.tile_width * mapInfo.cols;//ancho del fondo= ancho tile * numcols
    int fondoheight_ = mapInfo.tile_height * mapInfo.rows;//alto del fondo= alto del tile* numrows


    // convertir a textura
    background_ = SDL_CreateTexture(Gm_->getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, fondowidth_, fondoheight_);
    SDL_SetTextureBlendMode(background_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(Gm_->getRenderer(), background_);


    //Cargamos y almacenamos los tilesets utilizados por el tilemap
    vector<tmx::Tileset> mapTilesets = mapInfo.tile_MAP->getTilesets();

    for (const tmx::Tileset tile : mapTilesets) {
        string name = tile.getName();
        //string ruta = tile.getImagePath();
        //Texture* texture =tilesets_.find(name)->second;
        //Texture* texture = tilesets_.find(name)->second;;
        Texture* texture = sdlutils().tilesets().find(name)->second; //PORQUE ASI?????????????
        mapInfo.tilesets.insert(pair<uint, Texture*>(tile.getFirstGID(), texture));  //inserta en el mapa de Map_Info: llamado tilesets el ID del tileset y su textura
    }
     
    // Cargar la canción
    //sdlutils().musics().at("Title").setMusic(30);
   
  
    
    
    SDLUtils::instance()->soundEffects().at("Title").play(); 


    // recorremos cada una de las capas (de momento solo las de tiles) del mapa
    auto& mapLayers = mapInfo.tile_MAP->getLayers();

    for (auto& layer : mapLayers) {
        if (layer->getType() == tmx::Layer::Type::Tile) {
            // cargamos la capa
            tmx::TileLayer* tile_layer = dynamic_cast<tmx::TileLayer*>(layer.get());
            string name = tile_layer->getName();
            auto& layer_tiles = tile_layer->getTiles();
            if (name != "Nada") {
                // recorremos todos los tiles para obtener su informacion
                for (auto y = 0; y < mapInfo.rows; ++y) {
                    for (auto x = 0; x < mapInfo.cols; ++x) {
                        // obtenemos el indice relativo del tile en el mapa de tiles
                        int tile_index = x + (y * mapInfo.cols);

                        // con dicho indice obtenemos el indice del tile dentro de su tileset
                        int cur_gid = layer_tiles[tile_index].ID;

                        // si es 0 esta vacio asi que continuamos a la siguiente iteracion
                        if (cur_gid == 0) continue;

                        // guardamos el tileset que utiliza este tile (nos quedamos con el tileset cuyo gid sea
                        // el mas cercano, y a la vez menor, al gid del tile)           NO ENTIENDO ESTE COMENTARIO????????
                        int tset_gid = -1, tsx_file = 0;
                        for (auto& ts : mapInfo.tilesets) {
                            if (ts.first <= cur_gid) {
                                tset_gid = ts.first;
                                tsx_file++;     //esto para que es???????????????
                            }
                            else
                                break;
                        }

                        // si no hay tileset valido, continuamos a la siguiente iteracion
                        if (tset_gid == -1) continue;

                        // normalizamos el indice            //esto para que es???????????????
                        cur_gid -= tset_gid;

                        // calculamos dimensiones del tileset       //NO LAS TENIA YA???
                        auto ts_width = 0;
                        auto ts_height = 0;
                        SDL_QueryTexture(mapInfo.tilesets[tset_gid]->getSDLTexture(),
                            NULL, NULL, &ts_width, &ts_height);

                        // calculamos el area del tileset que corresponde al dibujo del tile
                        auto region_x = (cur_gid % (ts_width / mapInfo.tile_width)) * mapInfo.tile_width;
                        auto region_y = (cur_gid / (ts_width / mapInfo.tile_width)) * mapInfo.tile_height;

                        // calculamos la posicion del tile
                        auto x_pos = x * mapInfo.tile_width;
                        auto y_pos = y * mapInfo.tile_height;

                        // metemos el tile
                        auto tileTex = mapInfo.tilesets[tset_gid];

                        SDL_Rect src;
                        src.x = region_x; 
                        src.y = region_y;
                        src.w = mapInfo.tile_width;
                        src.h = mapInfo.tile_height;

                        SDL_Rect dest;
                        dest.x = x_pos;
                        dest.y = y_pos ;
                        dest.w = src.w;
                        dest.h = src.h;

                        int tileRot = layer_tiles[tile_index].flipFlags;
                        //float rotCorrection = 75;
                        //SDL_RendererFlip tileFlip = SDL_FLIP_NONE;

                        //Multiplicamos por 45 porque esta multiplicado por factor de 45 (lo que devuelve rot)
                        mapInfo.tilesets[tset_gid]->render(src, dest, tileRot);

                    }
                }


            }
            else if (name == "Col") {

                //CREAR TILES DE COLISIONES


            }


        }
        if (layer->getType() == tmx::Layer::Type::Object) {
            tmx::ObjectGroup* object_layer = dynamic_cast<tmx::ObjectGroup*>(layer.get());


            auto& objs = object_layer->getObjects();

            for (auto obj : objs) {
                auto rect = obj.getAABB();
                string name = object_layer->getName();
                if (name == "Colisiones") {
                    //cout << "colision" << rect.left << " " << rect.top << " " << rect.width << " " << rect.height << endl;
                    auto a = new ColliderTile(Vector2D(rect.left, rect.top), rect.width, rect.height, player_);
                    collisions_.push_back(a);
                }
                else if (name == "Interacctions") {
                  //  cout << "Interaccion" << rect.left << " " << rect.top << " " << rect.width << " " << rect.height << endl;

                    auto a = new ColliderTileInteraction(Vector2D(rect.left, rect.top), rect.width, rect.height, player_, obj.getUID(), puzzle1);
                    interactions_.push_back(a);
                }
                else if (name == "Player") {
                   // cout << "player" << rect.left<<" " << rect.top << " " << rect.width << " " << rect.height << endl;
                    // PLAYER
                    player_ = new Entity();
                    player_->setContext(this);
                    player_->addComponent<Transform>(TRANSFORM_H, obj.getPosition(), PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME, 1, PLAYERTD_SPEED, PLAYERTD_NUMFRAMES, false);
                    sk_ = player_->addComponent<SkinComponent>(SKINCOMPONENT_H, "air");
                    sk_->changeState(SkinComponent::Idle);
                    sk_->changeMov();
                    playerImage_ = player_->addComponent<Image>(IMAGE_H, t_, PLAYERTD_NUMFRAMES, PLAYERTD_NUMFRAMES,0, PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME);
                    player_->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
                    in_ = player_->addComponent<InputComponent>(INPUTCOMPONENT_H);
                    addEntity(player_);
                }
                else if (name == "NPC") {
                    Npc_ = new Entity();
                    Nptr_ = Npc_->addComponent<Transform>(TRANSFORM_H, obj.getPosition(), NpcWidth_, NpcHeight_, NpcRotation_, npcSpeed, nframes, matrix_);
                    //referencia al texture y al transform
                    Npc_->addComponent<Image>(IMAGE_H, t, nframes, nframes, 0, NPC_WIDTH, NPC_HEIGHT);
                    player_ = player;
                    ch = addComponent<CheckCollision>(CHECKCOLLISION_H, player_, a);
                    addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(0, 0), NpcHeight_, NpcWidth_ / nframes);
                    addEntity(new Npc(pl, { 50,10 }, & SDLUtils::instance()->images().at("NPC_2"), 2));
                }
                else if (name == "Enemy") {
                    enemy_ = addEntity(new Enemy(pl, 100));
                }
                else if (name == "Portal") {
                    p = addEntity(new Portal(player_));
                }

            }
        }


    }
    SDL_RenderPresent(Gm_->getRenderer());
    SDL_SetRenderTarget(Gm_->getRenderer(), nullptr);


    //setRenderer(Gm_->getRenderer());

}

void TopDownState::dialog(int a) {
    if (dialog_ != false) {
        if (d->getfinish() == true) {
            in_->changebool();
            d->~DialogBox();
            dialog_ = false;
        }
        else {
            d->setline();
        }

    }
    else {
        d = new DialogBox(a);
        addEntity(d);
        dialog_ = true;
      //  cout << "d" << endl;

    }
}

void TopDownState::update() {
  //  cout << player_->getComponent<Transform>(TRANSFORM_H)->getPos()<<" " << player_->getComponent<Transform>(TRANSFORM_H)->getW() << " " << player_->getComponent<Transform>(TRANSFORM_H)->getH();
    player_->setCollision(false);
    for (auto p : collisions_) {
        p->update();
    }
    for (auto p : interactions_) {
        p->update();
    }
    Manager::update();
    camRect_.x = (player_->getComponent<Transform>(TRANSFORM_H)->getPos().getX() + camOffset_) - WIN_WIDTH / 2;
    camRect_.y = (player_->getComponent<Transform>(TRANSFORM_H)->getPos().getY() + camOffset_) - WIN_HEIGHT / 2;
    // Clamp
    if (camRect_.x < 0) {
        camRect_.x = 0;
    }
    if (camRect_.y < 0) {
        camRect_.y = 0;
    }
}

void TopDownState::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        in_->handleEvents(event);
        //inBEU_->handleEvents(event);
        ;
    }
}

void TopDownState::render() {
    for (auto p : interactions_) {
        p->render();
    }
    for (auto p : collisions_) {
        p->render();
    }
    SDL_Rect dst = { 0,0,1000,1000 };
    // posición según el transform de la Camara
    dst.x -= Manager::camRect_.x/*cam_->getComponent<Transform>(TRANSFORM_H)->getPos().getX()*/;
    dst.y -= Manager::camRect_.y/*cam_->getComponent<Transform>(TRANSFORM_H)->getPos().getY()*/;
    SDL_Rect src = { 0, 0, 5000, 5000 };
    SDL_RenderCopy(Gm_->getRenderer(), background_, &src, &dst);
    Manager::render();
}

string TopDownState::getStateID() {
    return "TopDownState";
}
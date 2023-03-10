#include "TopDownState.h"


TopDownState::TopDownState() {
    puzzle1 = new PuzzleCopas();
    //


    dialog_ = false;
    //addEntity(new Npc(player_, { 50,10 }, &SDLUtils::instance()->images().at("NPC_2"), 2));
    //addEntity(new Npc(player_,{0,10},&SDLUtils::instance()->images().at("NPC_1"),1));	
    // 
    //in_ = player_->getComponent<InputComponent>(INPUTCOMPONENT_H);
    // 
    //enemy_ = addEntity(new Enemy(player_, 100));
    //cam_ = addEntity(new Camera(player_)); // entidad de camara
    //Portal* p = addEntity(new Portal(player_));
    LoadMap("assets/Scenes/Maps/MapaInicial.tmx");

    addEntity(new Element(player_, Vector2D(100, 100), p));
    addEntity(new Element(player_, Vector2D(300, 100), p));
    addEntity(new Element(player_, Vector2D(200, 200), p));


    // PRUEBAS PATHING ENEMIGO
    addEntity(new RedirectTile(Vector2D(1, 0), Vector2D(680, 170), enemy_)); //der
    addEntity(new RedirectTile(Vector2D(0, 1), Vector2D(870, 170), enemy_)); //ab
    addEntity(new RedirectTile(Vector2D(-1, 0), Vector2D(870, 360), enemy_)); //iz
    addEntity(new RedirectTile(Vector2D(0, -1), Vector2D(680, 360), enemy_)); //arr
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


    fondowidth_ = mapInfo.tile_width * mapInfo.cols;//ancho del fondo= ancho tile * numcols
    fondoheight_ = mapInfo.tile_height * mapInfo.rows;//alto del fondo= alto del tile* numrows


    // convertir a textura
    background_ = SDL_CreateTexture(Gm_->getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, fondowidth_, fondoheight_);
    SDL_SetTextureBlendMode(background_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(Gm_->getRenderer(), background_);


    //Cargamos y almacenamos los tilesets utilizados por el tilemap
    vector<tmx::Tileset> mapTilesets = mapInfo.tile_MAP->getTilesets();

    for (const tmx::Tileset tile : mapTilesets) {
        string name = tile.getName();
        
        Texture* texture = sdlutils().tilesets().find(name)->second; 
        mapInfo.tilesets.insert(pair<uint, Texture*>(tile.getFirstGID(), texture));  //inserta en el mapa de Map_Info: llamado tilesets el ID del tileset y su textura
    }
     
    // Cargar la cancióN
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
                                tsx_file++;   
                            }
                            else
                                break;
                        }

                        // si no hay tileset valido, continuamos a la siguiente iteracion
                        if (tset_gid == -1) continue;

                        // normalizamos el indice           
                        cur_gid -= tset_gid;

                        // calculamos dimensiones del tileset       
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
                        src.x = region_x; src.y = region_y;
                        src.w = mapInfo.tile_width;
                        src.h = mapInfo.tile_height;

                        SDL_Rect dest;
                        dest.x = x_pos;
                        dest.y = y_pos;
                        dest.w = src.w;
                        dest.h = src.h;

                        int tileRot = layer_tiles[tile_index].flipFlags;
                        float rotCorrection = 45;
                        //SDL_RendererFlip tileFlip = SDL_FLIP_NONE;

                        //Multiplicamos por 45 porque esta multiplicado por factor de 45 (lo que devuelve rot)
                        mapInfo.tilesets[tset_gid]->render(src, dest, tileRot * rotCorrection);

                    }
                }




            }


        }
        if (layer->getType() == tmx::Layer::Type::Object) {
            tmx::ObjectGroup* object_layer = dynamic_cast<tmx::ObjectGroup*>(layer.get());


            auto& objs = object_layer->getObjects();

            for (auto obj : objs) {
                auto rect = obj.getAABB();

                //   if (obj.getName() == "collision") 

               /* rect.width *= (float)(WIN_WIDTH / cam_->getWidth());
                rect.height *= (float)(WIN_HEIGHT / cam_->getHeight());

                rect.left *= (float)(WIN_WIDTH / cam_->getWidth());
                rect.top *= (float)(WIN_HEIGHT / cam_->getHeight());*/
                string name = object_layer->getName();
                if (name == "Colisiones") {
                    auto a = new ColliderTile(Vector2D(rect.left, rect.top), rect.width, rect.height, player_);
                    collisions_.push_back(a);
                }
                else if (name == "Interacctions") {
                    auto a = new ColliderTileInteraction(Vector2D(rect.left, rect.top), rect.width, rect.height, player_, obj.getUID(), puzzle1);
                    interactions_.push_back(a);
                }
                else if (name == "Player") {
                   // Vector2D pos(28, 4);
                    Vector2D pos(obj.getPosition().getX()/2, obj.getPosition().getY()/2);
                    player_ = addEntity(new PlayerTD("air", this, pos));
                    in_ = player_->getComponent<InputComponent>(INPUTCOMPONENT_H);
                }
                else if (name == "NPC") {
                    addEntity(new Npc(player_, { 50,10 }, & SDLUtils::instance()->images().at("NPC_2"), 2));
                }
                else if (name == "Enemy") {
                    enemy_ = addEntity(new Enemy(player_, 100));
                }
                //else if (name == "Camera") {
                //    cam_ = addEntity(new Camera(player_)); // entidad de camara
                //}
                else if (name == "Portal") {
                    p = addEntity(new Portal(player_));
                }

            }
        }


    }
  //  SDL_RenderPresent(Gm_->getRenderer());
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
        cout << "d" << endl;

    }
}

void TopDownState::update() {
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
    /*if (camRect_.x > (camRect_.w)) {
        camRect_.x = camRect_.w;
    }
    if (camRect_.y > (camRect_.h)) {
        camRect_.y = camRect_.h;
    }*/
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
    SDL_Rect dst = { 0,0,fondowidth_*2,fondoheight_*2};

    // posición según el transform de la Camara
    dst.x -= Manager::camRect_.x/*cam_->getComponent<Transform>(TRANSFORM_H)->getPos().getX()*/;
    dst.y -= Manager::camRect_.y/*cam_->getComponent<Transform>(TRANSFORM_H)->getPos().getY()*/;
    SDL_Rect src = { 0, 0, fondowidth_, fondowidth_ };
    SDL_RenderCopy(Gm_->getRenderer(), background_, &src, &dst);
    Manager::render();
}

string TopDownState::getStateID() {
    return "TopDownState";
}
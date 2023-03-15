#include "TopDownState.h"


TopDownState::TopDownState() {
    puzzle1 = new PuzzleCopas();
     dialog_ = false;
    LoadMap("assets/Scenes/Maps/MapaInicial.tmx");

   /* addEntity(new Element(player_, Vector2D(100, 100), p));
    addEntity(new Element(player_, Vector2D(300, 100), p));
    addEntity(new Element(player_, Vector2D(200, 200), p));*/


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
     

    /*Mix_VolumeMusic(0);
    Mix_Volume(MIX_CHANNELS, 0);*/
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
                        // el mas cercano, y a la vez menor, al gid del tile)         
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
                        mapInfo.tilesets[tset_gid]->render(src, dest, tileRot);

                    }
                }


            }


        }
        if (layer->getType() == tmx::Layer::Type::Object) {
            tmx::ObjectGroup* object_layer = dynamic_cast<tmx::ObjectGroup*>(layer.get());
            auto& objs = object_layer->getObjects();

            for (auto obj : objs) {
                auto rect = obj.getAABB();
                string name = object_layer->getName();
                if (name == "Colisiones") {
                   /* auto a = new ColliderTile(Vector2D(rect.left, rect.top), rect.width, rect.height, player_);
                    collisions_.push_back(a);*/
                }
                else if (name == "Interacctions") {
                    /*auto a = new ColliderTileInteraction(Vector2D(rect.left, rect.top), rect.width, rect.height, player_, obj.getUID(), puzzle1);
                    interactions_.push_back(a);*/
                }
                else if (name == "Player") {
                    // PLAYER
                    player_ = new Entity();
                    player_->setContext(this);
                    trans_player_= player_->addComponent<Transform>(TRANSFORM_H, Vector2D(obj.getPosition().x, obj.getPosition().y), PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME);                
                    sk_ = player_->addComponent<SkinComponent>(SKINCOMPONENT_H, "air");
                    sk_->changeState(SkinComponent::Idle);
                    sk_->changeMov();
                    texture_player_ = &SDLUtils::instance()->images().at(sk_->getSkin());
                    player_->addComponent<Image>(IMAGE_H, texture_player_, PLAYERTD_NUMFRAMES, PLAYERTD_NUMFRAMES,0, PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME);
                    player_->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
                    in_ = player_->addComponent<InputComponent>(INPUTCOMPONENT_H);
                    addEntity(player_);
                }
                else if (name == "NPC") {
                    Npc_ = new Entity();
                    Npc_->setContext(this);
                    Npc_->addComponent<Transform>(TRANSFORM_H,Vector2D(obj.getPosition().x, obj.getPosition().y), NPC_WIDTH, NPC_HEIGHT);
                    Npc_->addComponent<Image>(IMAGE_H,npcTexture(), NPC_FRAMES, NPC_FRAMES, 0, NPC_WIDTH, NPC_HEIGHT);
                    Npc_->addComponent<CheckCollision>(CHECKCOLLISION_H, player_, number_npc_);
					Npc_->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(0, 0), NPC_HEIGHT, NPC_WIDTH / NPC_FRAMES);
                    number_npc_++;
                    addEntity(Npc_);
                    
                }
                else if (name == "Enemy") {
                    if (obj.getName() == "") {
                        enemy_ = new Entity();
                        enemy_->setContext(this);
                        Texture* enemyT_ = EnemyTexture();
                        enemy_->addComponent<Transform>(TRANSFORM_H, Vector2D(obj.getPosition().x, obj.getPosition().y), enemy_width, enemy_height);
                        enemy_->addComponent<Enemy_movementTD_component>(ENEMY_MOVEMENT_TD_H);
                        enemy_->addComponent<Image>(IMAGE_H, enemyT_, ENEMYTD_NUMFRAMES, ENEMYTD_NUMFRAMES, 0, enemy_width, enemy_height);
                        float a = -1.0f;
                        float lookingRange = 150.0f;
                        float lookingWidth = 100.0f;
                        enemy_->addComponent<CheckCollision>(CHECKCOLLISION_H, player_, lookingRange, lookingWidth, a);
                        enemy_->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
                        enemy_->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(0, 0), enemy_height, enemy_width);
                        addEntity(enemy_);
                        enemies_.push_back(enemy_);
                    }
                    else if (obj.getName() == "left") {
                        redirect_ = new Entity();
                        redBox_.x = obj.getPosition().x;
                        redBox_.y = obj.getPosition().y;
                        redBox_.w = 10;
                        redBox_.h = 10;
                        redirect_->addComponent<RedirectEnemy>(REDIRECTENEMY_H, Vector2D(-1, 0), redBox_, enemies_);
                        addEntity(redirect_);
                    }
                    else if (obj.getName() == "right") {
                        redirect_ = new Entity();
                        redBox_.x = obj.getPosition().x;
                        redBox_.y = obj.getPosition().y;
                        redBox_.w = 10;
                        redBox_.h = 10;
                        redirect_->addComponent<RedirectEnemy>(REDIRECTENEMY_H, Vector2D(1, 0), redBox_, enemies_);
                        addEntity(redirect_);
                    }
                    else if (obj.getName() == "up") {
                        redirect_ = new Entity();
                        redBox_.x = obj.getPosition().x;
                        redBox_.y = obj.getPosition().y;
                        redBox_.w = 10;
                        redBox_.h = 10;
                        redirect_->addComponent<RedirectEnemy>(REDIRECTENEMY_H, Vector2D(0, -1), redBox_, enemies_);
                        addEntity(redirect_);
                    }
                    else if (obj.getName() == "down") {
                        redirect_ = new Entity();
                        redBox_.x = obj.getPosition().x;
                        redBox_.y = obj.getPosition().y;
                        redBox_.w = 10;
                        redBox_.h = 10;
                        redirect_->addComponent<RedirectEnemy>(REDIRECTENEMY_H, Vector2D(0, 1), redBox_, enemies_);
                        addEntity(redirect_);
                    }
                }
                else if (name == "Portal") {
                    Entity* portal_ = new Entity();
                    portal_->setContext(this);
                    portal_->addComponent<Transform>(TRANSFORM_H, Vector2D(obj.getPosition().x, obj.getPosition().y), PORTAL_WIDTH, PORTAL_HEIGHT);
                    portal_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("portal"), 1,1, 0, PORTAL_WIDTH, PORTAL_HEIGHT);
                    portal_->addComponent<ObjectsComponent>(OBJECTSCOMPONENT_H);
                    portal_->addComponent<PortalComponent>(PORTALCOMPONENT_H);
                    addEntity(portal_);
                }
                else if (name == "Element") {
                    float element_width = 50, element_height = 50;
                    Entity* element_ = new Entity();
                    element_->addComponent<Transform>(TRANSFORM_H, Vector2D(obj.getPosition().x, obj.getPosition().y), element_width, element_height);
                    element_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("fireball"), 4, 4, 0, ELEMENT_WIDTH, ELEMENT_HEIGHT);
                    element_->addComponent<ObjectsComponent>(OBJECTSCOMPONENT_H);
                    element_->addComponent<CheckCollision>(CHECKCOLLISION_H, player_, "element");
                    addEntity(element_);
                    
                }
                /*else if (name == "Shop") {
                    Entity* shop_ = new Entity();
                    upturnButton_ = new Entity();
                    Transform* shopTr_ = shop_->addComponent<Transform>(TRANSFORM_H, Vector2D(obj.getPosition().x, obj.getPosition().y), SHOP_WIDTH/2, SHOP_HEIGHT/2, 1);
                    shop_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("ShopBackground"), SHOP_WIDTH, SHOP_HEIGHT, shopTr_);
                    shop_->addComponent<ShopComponent>(SHOPCOMPONENT_H, upturnButton_);
                    
                    addEntity(shop_);
                    addEntity(upturnButton_);
                }*/
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
      

    }
}

void TopDownState::update() {
  //  cout << player_->getComponent<Transform>(TRANSFORM_H)->getPos()<<" " << player_->getComponent<Transform>(TRANSFORM_H)->getW() << " " << player_->getComponent<Transform>(TRANSFORM_H)->getH();
   // player_->setCollision(false);
    for (auto p : collisions_) {
        p->update();
    }
    for (auto p : interactions_) {
        p->update();
    }
    Manager::update();
    camRect_.x = (trans_player_->getPos().getX() + camOffset_) - WIN_WIDTH / 2;
    camRect_.y = (trans_player_->getPos().getY() + camOffset_) - WIN_HEIGHT / 2;
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
        //upturnButton_->handleEvent(event); // botón en la tienda
        //inBEU_->handleEvents(event);
    }
}

void TopDownState::render() {
    for (auto p : interactions_) {
        p->render();
    }
    for (auto p : collisions_) {
        p->render();
    }
    SDL_Rect dst = { 0,0,fondowidth_,fondoheight_};
    // posición según el transform de la Camara
    dst.x -= Manager::camRect_.x;
    dst.y -= Manager::camRect_.y;
    SDL_Rect src = { 0, 0, fondowidth_, fondoheight_ };
    SDL_RenderCopy(Gm_->getRenderer(), background_, &src, &dst);
    //hudTD->render();
    Manager::render();
}

string TopDownState::getStateID() {
    return "TopDownState";
}
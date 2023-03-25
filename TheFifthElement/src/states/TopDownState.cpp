#include "TopDownState.h"


TopDownState::TopDownState() {
    puzzle1 = new PuzzleCopas();
    dialog_ = false;
    //CARGAS EL MAPA
    LoadMap("assets/Scenes/Maps/MapaInicial.tmx");
    //HUD
    Hud_ = new Entity();
    Hud_->setContext(this);
    Hud_->addComponent<Damage>(DAMAGE_H);
    Hud_->addComponent<LifeTD>(LIFETDCOMPONENT_H);
    economyComp_ = Hud_->addComponent<EconomyComponent>(ECONOMYCOMPONENT_H);
    addEntity(Hud_);
    // COSAS DE LA TIENDA 
    font_ = &SDLUtils::instance()->fonts().at("TCentury");
    color_ = { 0,0,0 };
    //
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
                
                if (name == "COM") {
                    Entity* colision = new Entity();
                    colision->addComponent<Transform>(TRANSFORM_H, Vector2D(rect.left, rect.top), rect.width, rect.height);
                    collisions_.push_back(colision);
                   // collisions_.push_back(collidertile);
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
                    Playernpc_ = player_->addComponent<PlayerNPC>(PLAYERNPC_H);
                    player_->addComponent <DialogueComponent>(DIALOGCOMPONENT_H);
                    player_->addComponent<Image>(IMAGE_H, texture_player_, PLAYERTD_NUMFRAMES, PLAYERTD_NUMFRAMES,0, PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME);
                    player_->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
                    in_ = player_->addComponent<InputComponent>(INPUTCOMPONENT_H);
                    player_->addComponent<ColliderTile>(COLLIDERTILE_H, collisions_);
                   
                }
                else if (name == "NPC") {
                    contnpc++;
                    Npc_ = new Entity();
                    Npc_->setContext(this);
                    Npc_->addComponent<Transform>(TRANSFORM_H,Vector2D(obj.getPosition().x, obj.getPosition().y), NPC_WIDTH, NPC_HEIGHT);
                    Npc_->addComponent<Image>(IMAGE_H,npcTexture(), NPC_FRAMES, NPC_FRAMES, 0, NPC_WIDTH, NPC_HEIGHT);
                    Npc_->addComponent<NPCcollisioncomponent>(NPCCOLLISIONCOMPONENTT, player_,  contnpc );
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
                        enemy_->addComponent<Image>(IMAGE_H, enemyT_, ENEMYTD_NUMFRAMES, ENEMYTD_NUMFRAMES, 0, enemy_width, enemy_height);
                        float a = -1.0f;
                        float lookingRange = 150.0f;
                        float lookingWidth = 100.0f;
                        enemy_->addComponent<Enemy_movementTD_component>(ENEMY_MOVEMENT_TD_H, type_);
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
                else if (name == "Shop") {
                    
                    shop_ = new Entity();
                    shopTr_ = shop_->addComponent<Transform>(TRANSFORM_H, Vector2D(obj.getPosition().x, obj.getPosition().y), SHOP_WIDTH / 2, SHOP_HEIGHT / 2, 1);
                    shop_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("ShopBackground"), SHOP_WIDTH, SHOP_HEIGHT, shopTr_);
                    addEntity(shop_);

                    showAvatar(airAvatar_, airAvatarTr_, 0, "AirAvatar");
                    showAvatar(fireAvatar_, fireAvatarTr_, 1, "FireAvatar");
                    showAvatar(waterAvatar_, waterAvatarTr_, 2, "WaterAvatar");
                    showAvatar(earthAvatar_, earthAvatarTr_, 3, "EarthAvatar");
                    createShopButtons();
                }
            }
        }


    }
    addEntity(player_);
    SDL_RenderPresent(Gm_->getRenderer());
    SDL_SetRenderTarget(Gm_->getRenderer(), nullptr);


    //setRenderer(Gm_->getRenderer());

}

void TopDownState::dialog(int a) {
   /* if (dialog_ != false) {
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
      

    }*/
}

void TopDownState::update() {
  //  cout << player_->getComponent<Transform>(TRANSFORM_H)->getPos()<<" " << player_->getComponent<Transform>(TRANSFORM_H)->getW() << " " << player_->getComponent<Transform>(TRANSFORM_H)->getH();
   // player_->setCollision(false);
    Playernpc_->setcol();
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
        // Botones en la tienda
        upturnButtonAirAtt_->handleEvent(event);
        upturnButtonFireAtt_->handleEvent(event);
        upturnButtonWaterAtt_->handleEvent(event);
        upturnButtonEarthAtt_->handleEvent(event);
        upturnButtonAirHP_->handleEvent(event);
        upturnButtonFireHP_->handleEvent(event);
        upturnButtonWaterHP_->handleEvent(event);
        upturnButtonEarthHP_->handleEvent(event);
        exitShopButtonComp_->handleEvent(event);

        shopEconomy(); // Actualización de economía

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

    createUpgradeText(u1, 0, 0, 90, 0, price1_);
    createUpgradeText(u2, 0, 50, 90, 50, price2_);
    createUpgradeText(u3, 0, 100, 90, 100, price3_);
    createUpgradeText(u4, 0, 150, 90, 150, price4_);
    createUpgradeText(u5, 250, 0, 170, 0, price5_);
    createUpgradeText(u6, 250, 50, 170, 50, price6_);
    createUpgradeText(u7, 250, 100, 170, 100, price7_);
    createUpgradeText(u8, 250, 150, 170, 150, price8_);
}

#pragma region SHOP
void TopDownState::createShopButtons() {

    // Entidades
    upturnButtonAirAtt_ = new Entity();
    upturnButtonFireAtt_ = new Entity();
    upturnButtonWaterAtt_ = new Entity();
    upturnButtonEarthAtt_ = new Entity();
    upturnButtonAirHP_ = new Entity();
    upturnButtonFireHP_ = new Entity();
    upturnButtonWaterHP_ = new Entity();
    upturnButtonEarthHP_ = new Entity();

    // Parámetros
    upturnButtonX = shopTr_->getPos().getX();
    upturnButtonY = shopTr_->getPos().getY();
    upturnButtonPos_ = Vector2D(upturnButtonX + upturnButtonOffsetX / 2, upturnButtonY + upturnButtonOffsetY / 2);

    // Transform
    upturnButtonAirAttTr_ = upturnButtonAirAtt_->addComponent<Transform>(TRANSFORM_H, Vector2D(upturnButtonPos_.getX(), upturnButtonY + upturnButtonOffsetY), UPTURNBUTTON_WIDTH / 2, UPTURNBUTTON_HEIGHT / 2, 1);
    upturnButtonFireAttTr_ = upturnButtonFireAtt_->addComponent<Transform>(TRANSFORM_H, Vector2D(upturnButtonPos_.getX(), upturnButtonY + upturnButtonOffsetY + 50), UPTURNBUTTON_WIDTH / 2, UPTURNBUTTON_HEIGHT / 2, 1);
    upturnButtonWaterAttTr_ = upturnButtonWaterAtt_->addComponent<Transform>(TRANSFORM_H, Vector2D(upturnButtonPos_.getX(), upturnButtonY + upturnButtonOffsetY + 100), UPTURNBUTTON_WIDTH / 2, UPTURNBUTTON_HEIGHT / 2, 1);
    upturnButtonEarthAttTr_ = upturnButtonEarthAtt_->addComponent<Transform>(TRANSFORM_H, Vector2D(upturnButtonPos_.getX(), upturnButtonY + upturnButtonOffsetY + 150), UPTURNBUTTON_WIDTH / 2, UPTURNBUTTON_HEIGHT / 2, 1);
    upturnButtonAirHPTr_ = upturnButtonAirHP_->addComponent<Transform>(TRANSFORM_H, Vector2D(upturnButtonPos_.getX() + upturnButtonOffsetX, upturnButtonY + upturnButtonOffsetY), UPTURNBUTTON_WIDTH / 2, UPTURNBUTTON_HEIGHT / 2, 1);
    upturnButtonFireHPTr_ = upturnButtonFireHP_->addComponent<Transform>(TRANSFORM_H, Vector2D(upturnButtonPos_.getX() + upturnButtonOffsetX, upturnButtonY + upturnButtonOffsetY + 50), UPTURNBUTTON_WIDTH / 2, UPTURNBUTTON_HEIGHT / 2, 1);
    upturnButtonWaterHPTr_ = upturnButtonWaterHP_->addComponent<Transform>(TRANSFORM_H, Vector2D(upturnButtonPos_.getX() + upturnButtonOffsetX, upturnButtonY + upturnButtonOffsetY + 100), UPTURNBUTTON_WIDTH / 2, UPTURNBUTTON_HEIGHT / 2, 1);
    upturnButtonEarthHPTr_ = upturnButtonEarthHP_->addComponent<Transform>(TRANSFORM_H, Vector2D(upturnButtonPos_.getX() + upturnButtonOffsetX, upturnButtonY + upturnButtonOffsetY + 150), UPTURNBUTTON_WIDTH / 2, UPTURNBUTTON_HEIGHT / 2, 1);

    // Button
    upturnButtonComp1_ = upturnButtonAirAtt_->addComponent<Button>(BUTTON_H, "UPTURN");
    upturnButtonComp2_ = upturnButtonFireAtt_->addComponent<Button>(BUTTON_H, "UPTURN");
    upturnButtonComp3_ = upturnButtonWaterAtt_->addComponent<Button>(BUTTON_H, "UPTURN");
    upturnButtonComp4_ = upturnButtonEarthAtt_->addComponent<Button>(BUTTON_H, "UPTURN");
    upturnButtonComp5_ = upturnButtonAirHP_->addComponent<Button>(BUTTON_H, "UPTURN");
    upturnButtonComp6_ = upturnButtonFireHP_->addComponent<Button>(BUTTON_H, "UPTURN");
    upturnButtonComp7_ = upturnButtonWaterHP_->addComponent<Button>(BUTTON_H, "UPTURN");
    upturnButtonComp8_ = upturnButtonEarthHP_->addComponent<Button>(BUTTON_H, "UPTURN");

    // Image
    upturnButtonAirAtt_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("UpturnButton"), UPTURNBUTTON_WIDTH, UPTURNBUTTON_HEIGHT, upturnButtonAirAttTr_);
    upturnButtonFireAtt_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("UpturnButton"), UPTURNBUTTON_WIDTH, UPTURNBUTTON_HEIGHT, upturnButtonFireAttTr_);
    upturnButtonWaterAtt_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("UpturnButton"), UPTURNBUTTON_WIDTH, UPTURNBUTTON_HEIGHT, upturnButtonWaterAttTr_);
    upturnButtonEarthAtt_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("UpturnButton"), UPTURNBUTTON_WIDTH, UPTURNBUTTON_HEIGHT, upturnButtonEarthAttTr_);
    upturnButtonAirHP_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("UpturnButton"), UPTURNBUTTON_WIDTH, UPTURNBUTTON_HEIGHT, upturnButtonAirHPTr_);
    upturnButtonFireHP_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("UpturnButton"), UPTURNBUTTON_WIDTH, UPTURNBUTTON_HEIGHT, upturnButtonFireHPTr_);
    upturnButtonWaterHP_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("UpturnButton"), UPTURNBUTTON_WIDTH, UPTURNBUTTON_HEIGHT, upturnButtonWaterHPTr_);
    upturnButtonEarthHP_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("UpturnButton"), UPTURNBUTTON_WIDTH, UPTURNBUTTON_HEIGHT, upturnButtonEarthHPTr_);

    // Economy
   

    createExitShopButton();// Creo botón de salida

    // Añado entidades
    addEntity(upturnButtonAirAtt_);
    addEntity(upturnButtonFireAtt_);
    addEntity(upturnButtonWaterAtt_);
    addEntity(upturnButtonEarthAtt_);
    addEntity(upturnButtonAirHP_);
    addEntity(upturnButtonFireHP_);
    addEntity(upturnButtonWaterHP_);
    addEntity(upturnButtonEarthHP_);


}

void TopDownState::createExitShopButton() {
    exitShopButton_ = new Entity();
    exitShopButtonTr_ = exitShopButton_->addComponent<Transform>(TRANSFORM_H, Vector2D(upturnButtonX + SHOP_WIDTH / 14, upturnButtonY + upturnButtonOffsetY + 300), 557 / 2, 131 / 2, 1);
    exitShopButton_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("ExitShop"), 557, 131, exitShopButtonTr_);
    exitShopButtonComp_ = exitShopButton_->addComponent<Button>(BUTTON_H, "EXITSHOP");
    addEntity(exitShopButton_);
}

void TopDownState::createUpgradeText(int value, int offsetXup, int offsetYup, int offsetXcoin, int offsetYcoin, int price) {
    // Textos mejoras
    textUp_ = std::to_string(value) + "/" + std::to_string(MAX_UPGRADE);
    font_->render(GameManager::instance()->getRenderer(), textUp_, textX + offsetXup, textY + offsetYup, color_);
    // Textos monedas
    textCoin_ = std::to_string(price);
    font_->render(GameManager::instance()->getRenderer(), textCoin_, textX + offsetXcoin, textY + offsetYcoin, color_);
}

// incrementa los valores de las mejoras en la tienda
int TopDownState::increase(int& i) {
    return i++;
}

// lógica para manejar las compras en la tienda
void TopDownState::shopEconomy() {
    if (upturnButtonComp1_->getBool() && u1 < MAX_UPGRADE && economyComp_->getMoney() >= price1_) { // si el botón es clicado(isClicked=true en Button), si "u1" es menor que el máximo de mejoras y si nuestro dinero es mayor o igual al precio del artículo
        increase(u1); // incremento del valor de mejora
        economyComp_->can_Substract(price1_);// restamos nuestro dinero actual
        price1_ += 10; // actualizamos precio en la tienda
    }
    if (upturnButtonComp2_->getBool() && u2 < MAX_UPGRADE && economyComp_->getMoney() >= price2_) {
        increase(u2);
        economyComp_->can_Substract(price2_);
        price2_ += 10;
    }
    else if (upturnButtonComp3_->getBool() && u3 < MAX_UPGRADE && economyComp_->getMoney() >= price3_) {
        increase(u3);
        economyComp_->can_Substract(price3_);
        price3_ += 10;
    }
    else if (upturnButtonComp4_->getBool() && u4 < MAX_UPGRADE && economyComp_->getMoney() >= price4_) {
        increase(u4);
        economyComp_->can_Substract(price4_);
        price4_ += 10;
    }
    else if (upturnButtonComp5_->getBool() && u5 < MAX_UPGRADE && economyComp_->getMoney() >= price5_) {
        increase(u5);
        economyComp_->can_Substract(price5_);
        price5_ += 10;
    }
    else if (upturnButtonComp6_->getBool() && u6 < MAX_UPGRADE && economyComp_->getMoney() >= price6_) {
        increase(u6);
        economyComp_->can_Substract(price6_);
        price6_ += 10;
    }
    else if (upturnButtonComp7_->getBool() && u7 < MAX_UPGRADE && economyComp_->getMoney() >= price7_) {
        increase(u7);
        economyComp_->can_Substract(price7_);
        price7_ += 10;
    }
    else if (upturnButtonComp8_->getBool() && u8 < MAX_UPGRADE && economyComp_->getMoney() >= price8_) {
        increase(u8);
        economyComp_->can_Substract(price8_);
        price8_ += 10;
    }
}


// Muestra los avatares dentro de unos marcos en la tienda
void TopDownState::showAvatar(Entity* entity, Transform* transform, int i, string id) {

    entity = new Entity();
    shopFrame_ = new Entity();
    shopFramePos_ = shopTr_->getPos();
    shopFrameTr_ = shopFrame_->addComponent<Transform>(TRANSFORM_H, shopFramePos_ + Vector2D(165, 152 + i * 50), 40, 40, 1);
    shopFrame_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("ShopFrame"), 40, 40, shopFrameTr_);
    transform = entity->addComponent<Transform>(TRANSFORM_H, shopFramePos_, 40, 40, 1);
    entity->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at(id), 32, 32, transform);

    addEntity(shopFrame_);
    addEntity(entity);
}

#pragma endregion

string TopDownState::getStateID() {
    return "TopDownState";
}
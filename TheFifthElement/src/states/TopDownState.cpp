#include "TopDownState.h"
#include "../Game.h"

#include <fstream>
#include "../Elements.h"
#include "../Quests.h"
TopDownState::TopDownState() {
    puzzle1 = new PuzzleCopas();
    ////HUD
    //Hud_ = new Entity();
    //Hud_->setContext(this);
    //roulete = Hud_->addComponent<Roulette>(ROULETTECOMPONENT_H);
    //damage_ =  Hud_->addComponent<Damage>(DAMAGE_H);
    //life_ = Hud_->addComponent<LifeTD>(LIFETDCOMPONENT_H);
    //economyComp_ = Hud_->addComponent<EconomyComponent>(ECONOMYCOMPONENT_H);
    //CARGAS EL MAPA
    //HUD
    Hud_ = new Entity();
    Hud_->setContext(this);
    roulete = Hud_->addComponent<Roulette>(ROULETTECOMPONENT_H);
    LoadMap("assets/Scenes/Maps/MapaInicial.tmx");
    addEntity(Hud_);  
    SDLUtils::instance()->soundEffects().at("Title").play();
    dialog_->inicombe();
    //trans_player_->setPos({ 11668 ,547 });
}

TopDownState::~TopDownState()
{
    for(auto it:collisions_)
    {
        delete it;
    }
    collisions_.clear();
    delete puzzle1;
    Manager::~Manager();

}

void TopDownState::update() {
    Vector2D savedPos = Saving::instance()->getPos();
    if (savedPos != Vector2D(0, 0))
    {
        movcomp_player_->setNewPos(savedPos);
        Saving::instance()->deletePos();
    }
    Playernpc_->setcol();

    Quests::instance()->actQuests();
    Manager::refresh();
    Manager::update();

    camRect_.x = camRect_.x + ((trans_player_->getPos().getX() + camOffset_ - camRect_.x) - WIN_WIDTH / 2) * 0.05;
    camRect_.y = camRect_.y + ((trans_player_->getPos().getY() + camOffset_ - camRect_.y) - WIN_HEIGHT / 2) * 0.05;
    // Clamp
    if (camRect_.x < 0) {
        camRect_.x = 0;
    }
    if (camRect_.y < 0) {
        camRect_.y = 0;
    }
}
void TopDownState::SaveGame() {

    if (!saved) {
        saved = true;
        ofstream save;
        save.open("File1.txt");
        if (save.is_open()) {
            //escribir cosas deñ player
            save << "PLAYER" << endl;
            save << player_->getComponent<EconomyComponent>(ECONOMYCOMPONENT_H)->getMoney() << endl;
            save << trans_player_->getPos().getX() << " " << trans_player_->getPos().getY() << endl;
            save << Elements::instance()->getEarth() << endl;
            save << PropertiesManager::instance()->getStrength(3) << " " << PropertiesManager::instance()->getLives(3) << endl;
            save << Elements::instance()->getFire() << endl;
            save << PropertiesManager::instance()->getStrength(1) << " " << PropertiesManager::instance()->getLives(1) << endl;
            save << Elements::instance()->getWater() << endl;
            save << PropertiesManager::instance()->getStrength(2) << " " << PropertiesManager::instance()->getLives(2) << endl << endl;


            //ENEMIGUESSS
            for (auto c : ents_) {
                if (c->hasComponent(ENEMY_MOVEMENT_TD_H)) {
                    save << "enemy" << endl;
                    Transform* f = c->getComponent<Transform>(TRANSFORM_H);
                    if (c->getComponent<FramedImage>(FRAMEDIMAGE_H)->getType() == "") {
                        save << "skeleton" << endl;
                    }
                    else {
                        save << c->getComponent<FramedImage>(FRAMEDIMAGE_H)->getType() << endl;
                    }

                    save << f->getPos().getX() << " " << f->getPos().getY() << " " << f->getDir().getX() << " " << f->getDir().getY() << endl;





                }
                else if (c->hasComponent(REDIRECTENEMY_H)) {
                    save << "redirect" << endl;
                    RedirectEnemy* f = c->getComponent<RedirectEnemy>(REDIRECTENEMY_H);
                    save << f->getVector().getX() << " " << f->getVector().getY() << endl;
                    save << f->getBox().x << " " << f->getBox().y << " " << f->getBox().w << " " << f->getBox().h << endl;
                }

            }

            save << -1 << endl;
            save.close();

        }
    }
}

void TopDownState::render() {

    SDL_Rect dst = { 0,0,(fondowidth_ * 2.5) * (WIN_WIDTH / 900),(fondoheight_ * 2.5) * (WIN_HEIGHT / 600) };
    // posición según el transform de la Camara
    dst.x -= Manager::camRect_.x;
    dst.y -= Manager::camRect_.y;
    SDL_Rect src = { 0, 0, fondowidth_, fondoheight_ };

    SDL_RenderCopy(Gm_->getRenderer(), background_0, &src, &dst);
    for (auto p : interactions_) {
        p->render();
    }
    for (auto p : collisions_) {
        p->render();
    }
    //SDL_RenderCopy(Gm_->getRenderer(), background_1, &src, &dst);
    //hudTD->render();
    
    // MINIMAPA
    Vector2D scale = { (WIN_WIDTH / 900.0f), (WIN_HEIGHT / 600.0f) };
    SDL_Rect mapFrame = { (WIN_WIDTH - 190 * scale.getX()), 10 * scale.getY(), mapFrameX_ * scale.getX(), mapFrameY_ * scale.getY() };
    SDL_Rect srcMinMap = { 0, 0, fondowidth_ / zoom_, fondoheight_ / zoom_ };
    srcMinMap.x += Manager::camRect_.x / 4 - WIN_WIDTH / 2 - mapOffsetX_;
    srcMinMap.y += Manager::camRect_.y / 4 - WIN_HEIGHT / 4 + mapOffsetY_;
    SDL_RenderCopy(Gm_->getRenderer(), background_0, &srcMinMap, &mapFrame);
    m_->render(mapFrame);

    SDL_Rect icon = { (WIN_WIDTH - 190 / 2 * scale.getX()), 60 * scale.getY(), iconWidth_, iconHeight_ };
    SDL_Rect srcIc = { 0, 0, PLAYERAVATAR_DIMENSION, PLAYERAVATAR_DIMENSION };
    SDL_RenderCopy(Gm_->getRenderer(), background_0, &srcIc, &icon);
    sk_->getAvatar()->render(icon);

    Manager::render();

    SDL_RenderCopy(Gm_->getRenderer(), prueba, &src, &dst);
    Hud_->render();
    if (questsMenu)Quests::instance()->renderQuestList();

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
    background_0 = SDL_CreateTexture(Gm_->getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, fondowidth_, fondoheight_);
    SDL_SetTextureBlendMode(background_0, SDL_BLENDMODE_BLEND);
    prueba = SDL_CreateTexture(Gm_->getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, fondowidth_, fondoheight_);
    SDL_SetTextureBlendMode(prueba, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(Gm_->getRenderer(), background_0);
    //CARGAR AQUI LAS DIFERENTES TEXTURAS

    //Cargamos y almacenamos los tilesets utilizados por el tilemap
    vector<tmx::Tileset> mapTilesets = mapInfo.tile_MAP->getTilesets();

    for (const tmx::Tileset tile : mapTilesets) {
        string name = tile.getName();
        Texture* texture = sdlutils().tilesets().find(name)->second; 
        mapInfo.tilesets.insert(pair<uint, Texture*>(tile.getFirstGID(), texture));  //inserta en el mapa de Map_Info: llamado tilesets el ID del tileset y su textura
    }

    /*Mix_VolumeMusic(0);
    Mix_Volume(MIX_CHANNELS, 0);*/

    // recorremos cada una de las capas (de momento solo las de tiles) del mapa    
    auto& mapLayers = mapInfo.tile_MAP->getLayers();
    for (auto& layer : mapLayers) {
        if (layer->getType() == tmx::Layer::Type::Tile) {
            // cargamos la capa
            tmx::TileLayer* tile_layer = dynamic_cast<tmx::TileLayer*>(layer.get());
            string name = tile_layer->getName();
            auto& layer_tiles = tile_layer->getTiles();
            if (name != "Nada") {

                //vemos si es una capa que debe renderizar por delante o por detras del jugador
                if (name == "pruebapasardetras") {
                    SDL_SetRenderTarget(Gm_->getRenderer(), prueba); // poner en el if todas las capas que renderizan por delante de las entidades
                }
                else SDL_SetRenderTarget(Gm_->getRenderer(), background_0);  // todo el resto de capas

                // recorremos todos los tiles para obtener su informacion
                for (auto y = 0; y < mapInfo.rows; ++y) {
                    for (auto x = 0; x < mapInfo.cols; ++x) {
                        //if (y < mapInfo.rows/10) {
                        //    if (x < mapInfo.cols / 5) { //primer 
                        //        SDL_SetRenderTarget(Gm_->getRenderer(), background_0);

                        //    }
                        //    else {//segundo
                        //        SDL_SetRenderTarget(Gm_->getRenderer(), background_1);

                        //    }
                        //}
                        //else {//tercero
                        //    if (x < mapInfo.cols / 2) {
                        //        SDL_SetRenderTarget(Gm_->getRenderer(), background_2);

                        //    }
                        //    else {//cuarto
                        //        SDL_SetRenderTarget(Gm_->getRenderer(), background_3);

                        //    }
                        //}
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
                        dest.y = y_pos;
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

                if (name == "Collisions") {
                    Entity* colision = new Entity();
                    colision->addComponent<Transform>(TRANSFORM_H, Vector2D(rect.left*2.5, rect.top*2.5), (rect.width * 2.5)* (WIN_WIDTH / 900), (rect.height * 2.5)* (WIN_HEIGHT / 600));
                    //(fondowidth_ * 2.5)* (WIN_WIDTH / 900),(fondoheight_ * 2.5)* (WIN_HEIGHT / 600)
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
                    trans_player_ = player_->addComponent<Transform>(TRANSFORM_H, Vector2D((obj.getPosition().x * 2.5), obj.getPosition().y * 2.5), PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME);
                    trans_player_->setVel(PLAYERTD_SPEED);                                      /*(fondowidth_ * 2.5)* (WIN_WIDTH / 900), (fondoheight_ * 2.5)* (WIN_HEIGHT / 600)*/
                    sk_ = player_->addComponent<SkinComponent>(SKINCOMPONENT_H, "air", airAvatar_);
                    sk_->changeState(SkinComponent::Idle);

                    texture_player_ = &SDLUtils::instance()->images().at("PTD_air_idle");
                    Playernpc_ = player_->addComponent<PlayerNPC>(PLAYERNPC_H);
                    player_->addComponent<FramedImage>(FRAMEDIMAGE_H, texture_player_, PLAYERTD_WIDTH_FRAME, PLAYERTD_HEIGHT_FRAME, 7, "air");
                    sk_->initComponent();
                    dialog_ = player_->addComponent<DialogueComponent>(DIALOGCOMPONENT_H);
                    movcomp_player_ = player_->addComponent<MovementComponent>(MOVEMENTCOMPONENT_H);
                    in_ = player_->addComponent<InputComponent>(INPUTCOMPONENT_H, roulete);
                    player_->addComponent<ColliderTile>(COLLIDERTILE_H, collisions_);
                    damage_ = Hud_->addComponent<Damage>(DAMAGE_H);
                    life_ = Hud_->addComponent<LifeTD>(LIFETDCOMPONENT_H);
                    economyComp_ = Hud_->addComponent<EconomyComponent>(ECONOMYCOMPONENT_H);
                    shopComp_ = player_->addComponent<ShopComponent>(SHOPCOMPONENT_H, economyComp_, damage_, life_);

                }
                else if (name == "NPC") {
                    contnpc++; 
                    Npc_ = new Entity();
                    Npc_->setContext(this);
                    Npc_->addComponent<Transform>(TRANSFORM_H,Vector2D((obj.getPosition().x * 2.5), obj.getPosition().y * 2.5), NPC_WIDTH, NPC_HEIGHT);
                    if (obj.getName() != "Contexto") { Npc_->addComponent<FramedImage>(FRAMEDIMAGE_H, npcTexture(), NPC_WIDTH, NPC_HEIGHT, 7);}
                    Npc_->addComponent<NPCcollisioncomponent>(NPCCOLLISIONCOMPONENTT, player_,  contnpc );
                    addEntity(Npc_);
                    if (obj.getName() == "Contexto") {
                        Contexto = Npc_;
                    }
                }
                else if (name == "Herreros") {
                    contBlksm++;
                    Blacksmith_ = new Entity();
                    Blacksmith_->setContext(this);
                    Blacksmith_->addComponent<Transform>(TRANSFORM_H, Vector2D((obj.getPosition().x * 2.5), obj.getPosition().y * 2.5), BLACKSMITH_WIDTH, BLACKSMITH_HEIGHT);
                    Blacksmith_->addComponent<FramedImage>(IMAGE_H, blacksmithTexture(), BLACKSMITH_WIDTH, BLACKSMITH_HEIGHT, BLACKSMITH_FRAMES);
                    Blacksmith_->addComponent<NPCcollisioncomponent>(NPCCOLLISIONCOMPONENTT, player_, contBlksm);
                    Blacksmith_->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(0, 0), BLACKSMITH_HEIGHT, BLACKSMITH_WIDTH / BLACKSMITH_FRAMES);
                    addEntity(Blacksmith_);

                }
                else if (name == "pruebas")
                {
                    pruebaCollider = new Entity();
                    pruebaCollider->setContext(this);
                    pruebaCollider->addComponent<Transform>(TRANSFORM_H, Vector2D((obj.getPosition().x * 2.5), obj.getPosition().y * 2.5), obj.getAABB().width, obj.getAABB().height);
                    //pruebaCollider->addComponent <SectorCollisionComponent>(SECTORCOLLISIONCOMPONENT_H, player_, idSector);
                    pruebaCollider->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(0, 0), obj.getAABB().height, obj.getAABB().width);
                    addEntity(pruebaCollider);
                    idSector++;
                }
                else if (name == "BossLuz")
                {
                    boss_ = new Entity();
                    boss_->setContext(this);
                    boss_->addComponent<Transform>(TRANSFORM_H, Vector2D((obj.getPosition().x * 2.5), obj.getPosition().y * 2.5), 600, 400);
                    boss_->addComponent<FramedImage>(IMAGE_H, bossLuzTexture(), LIGHTBOSS_TP_WIDTH, LIGHTBOSS_TP_HEIGHT, LIGHTBOSS_TP_FRAMES);
                    boss_->addComponent<BossCollision>(BOSSCOLLISION_H, player_, "light");
                    boss_->addComponent<ColliderComponent>(COLLIDERCOMPONENT_H, Vector2D(0, 0), 288, 188);
                    addEntity(boss_);
                }
                if (!loadGame) { //carga
                     if (name == "Enemy") {
                        if (obj.getName() == "" && !loadGame) {
                            enemy_ = new Entity();
                            enemy_->setContext(this);
                            Texture* enemyT_ = EnemyTexture();
                            enemy_->addComponent<Transform>(TRANSFORM_H, Vector2D((obj.getPosition().x * 2.5), obj.getPosition().y * 2.5), enemy_width, enemy_height);
                            FramedImage* img = enemy_->addComponent<FramedImage>(FRAMEDIMAGE_H, enemyT_, enemy_width, enemy_height, 7, type_);
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
                            redBox_.x = obj.getPosition().x * 2.5;
                            redBox_.y = obj.getPosition().y * 2.5;
                            redBox_.w = 10;
                            redBox_.h = 10;
                            redirect_->addComponent<RedirectEnemy>(REDIRECTENEMY_H, Vector2D(-1, 0), redBox_, enemies_);
                            addEntity(redirect_);
                        }
                        else if (obj.getName() == "right") {
                            redirect_ = new Entity();
                            redBox_.x = obj.getPosition().x * 2.5;
                            redBox_.y = obj.getPosition().y * 2.5;
                            redBox_.w = 10;
                            redBox_.h = 10;
                            redirect_->addComponent<RedirectEnemy>(REDIRECTENEMY_H, Vector2D(1, 0), redBox_, enemies_);
                            addEntity(redirect_);
                        }
                        else if (obj.getName() == "up") {
                            redirect_ = new Entity();
                            redBox_.x = obj.getPosition().x * 2.5;
                            redBox_.y = obj.getPosition().y * 2.5;
                            redBox_.w = 10;
                            redBox_.h = 10;
                            redirect_->addComponent<RedirectEnemy>(REDIRECTENEMY_H, Vector2D(0, -1), redBox_, enemies_);
                            addEntity(redirect_);
                        }
                        else if (obj.getName() == "down") {
                            redirect_ = new Entity();
                            redBox_.x = obj.getPosition().x * 2.5;
                            redBox_.y = obj.getPosition().y * 2.5;
                            redBox_.w = 10;
                            redBox_.h = 10;
                            redirect_->addComponent<RedirectEnemy>(REDIRECTENEMY_H, Vector2D(0, 1), redBox_, enemies_);
                            addEntity(redirect_);
                        }
                    }
                    else if (obj.getName() == "water") {
                        //PARA CREAR EL RESTO DE BOSSES AÑADIR AL TILEMAP (EN LA CAPA DE ENEMY) UN ENEMIGO NUEVO Y MODIFICAR SU NOMBRE
                        enemy_ = new Entity();
                        enemy_->setContext(this);
                        enemy_->addComponent<Transform>(TRANSFORM_H, Vector2D(obj.getPosition().x, obj.getPosition().y), WATERBOSS_WIDTH, WATERBOSS_HEIGHT, 2);
                        enemy_->addComponent<FramedImage>(FRAMEDIMAGE_H, &sdlutils().images().at("waterBoss_idle"), WATERBOSS_WIDTH, WATERBOSS_HEIGHT, 6);
                        float a = 1.0f;
                        float lookingRange = 50.0f;
                        float lookingWidth = -40;
                        enemy_->addComponent<Enemy_movementTD_component>(ENEMY_MOVEMENT_TD_H, "boss");
                        enemy_->addComponent<CheckCollision>(CHECKCOLLISION_H, player_, lookingRange, lookingWidth, a, -300, "water");
                        addEntity(enemy_);
                        enemies_.push_back(enemy_);
                    }
                    else if (obj.getName() == "earth") {
                        //PARA CREAR EL RESTO DE BOSSES AÑADIR AL TILEMAP (EN LA CAPA DE ENEMY) UN ENEMIGO NUEVO Y MODIFICAR SU NOMBRE
                        enemy_ = new Entity();
                        enemy_->setContext(this);
                        enemy_->addComponent<Transform>(TRANSFORM_H, Vector2D(obj.getPosition().x, obj.getPosition().y), EARTHBOSS_HEIGHT, EARTHBOSS_HEIGHT, 2);
                        enemy_->addComponent<FramedImage>(FRAMEDIMAGE_H, &sdlutils().images().at("GolemFase1_idle"), EARTHBOSS_WIDTH, EARTHBOSS_HEIGHT, 6);
                        float a = 1.0f;
                        float lookingRange = 50.0f;
                        float lookingWidth = -40;
                        enemy_->addComponent<Enemy_movementTD_component>(ENEMY_MOVEMENT_TD_H, "boss");
                        enemy_->addComponent<CheckCollision>(CHECKCOLLISION_H, player_, lookingRange, lookingWidth, a, -300, "earth");
                        addEntity(enemy_);
                        enemies_.push_back(enemy_);
                    }
                }
                else if (name == "Portal") {
                    Entity* portal_ = new Entity();
                    portal_->setContext(this);
                    portal_->addComponent<Transform>(TRANSFORM_H, Vector2D((obj.getPosition().x * 2.5), obj.getPosition().y * 2.5), PORTAL_WIDTH, PORTAL_HEIGHT);
                    portal_->addComponent<FramedImage>(FRAMEDIMAGE_H, &SDLUtils::instance()->images().at("portal"), PORTAL_WIDTH, PORTAL_HEIGHT, 1);
                    portal_->addComponent<PortalComponent>(PORTALCOMPONENT_H, trans_player_);
                    addEntity(portal_);
                }
            }
        }

    }
    addEntity(player_);
    SDL_RenderPresent(Gm_->getRenderer());
    SDL_SetRenderTarget(Gm_->getRenderer(), nullptr);

}



void TopDownState::LoadGame() {
    if (!loaded) {
        loaded = true;
        ifstream f;
        f.open("File1.txt");
        if (f.is_open()) {
            string player;
            f >> player;

            if (player == "PLAYER") {

                float number;
                f >> number;
                EconomyComponent* ec = Hud_->getComponent<EconomyComponent>(ECONOMYCOMPONENT_H);
                ec->setMoney(int(number));
                float number2, number3;
                f >> number2;
                f >> number3;
                Vector2D v{ number2,number3 };
                trans_player_->setPos(v);
                bool d;
                f >> d;
                Elements::instance()->setEarth(d);
                f >> number2 >> number3;
                PropertiesManager::instance()->setStrength(3, number2);
                PropertiesManager::instance()->setLives(3, number3);
                f >> d;
                f >> number2 >> number3;
                Elements::instance()->setFire(d);
                PropertiesManager::instance()->setStrength(1, number2);
                PropertiesManager::instance()->setLives(1, number3);
                f >> d;
                f >> number2 >> number3;
                Elements::instance()->setWater(d);
                PropertiesManager::instance()->setStrength(2, number2);
                PropertiesManager::instance()->setLives(2, number3);

                string name;
                f >> name;
                while (name != "-1") {
                    if (name == "enemy") {
                        Vector2D pos;
                        string name;
                        f >> name;
                        float x, y, dirx, diry;
                        f >> x >> y >> dirx >> diry;

                        pos = { x,y };
                        enemy_ = new Entity();
                        enemy_->setContext(this);
                        Texture* enemyT_ = EnemyTexture();
                        Transform* m = enemy_->addComponent<Transform>(TRANSFORM_H, pos, enemy_width, enemy_height);
                        m->setDir(Vector2D{ dirx,diry });
                        FramedImage* img = enemy_->addComponent<FramedImage>(FRAMEDIMAGE_H, enemyT_, enemy_width, enemy_height, 7, name);
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
                    else if (name == "redirect") {
                        float x, y, x2, y2, w, h;
                        f >> x >> y >> x2 >> y2 >> w >> h;
                        redirect_ = new Entity();
                        redBox_.x = x2;
                        redBox_.y = y2;
                        redBox_.w = w;
                        redBox_.h = h;
                        redirect_->addComponent<RedirectEnemy>(REDIRECTENEMY_H, Vector2D(x, y), redBox_, enemies_);
                        addEntity(redirect_);

                    }
                    f >> name;

                }


            }


        }
    }

  

}

void TopDownState::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
        in_->handleEvents(event);
        if (event.type == SDL_QUIT)
        {
            GameManager::instance()->getGame()->setExit(true);
        }
        if (dialog_->getopenedShop()) {
            for (auto e : buttons1) {
                e->handleEvent(event);
            }
            for (auto e : buttons2) {
                e->handleEvent(event);
            }
          
            exitShopButton_->handleEvent(event);
        }
}

void TopDownState::createShopButtons() {
    upturnButtonX = trans_player_->getPos().getX();
    upturnButtonY = trans_player_->getPos().getY();
    if (WIN_WIDTH / 900 == 1920 / 900) upturnButtonPos_ = Vector2D(upturnButtonX - 195, upturnButtonY - 20);
    else upturnButtonPos_ = Vector2D(upturnButtonX - upturnButtonOffsetX, upturnButtonY + upturnButtonOffsetY);

    if (shopCreated_) {
        int i = 0;
        for (auto e : buttons1) {

            Vector2D pos;
            if (WIN_WIDTH / 900 == 1920 / 900) {
                pos = Vector2D((upturnButtonPos_.getX()),
                    upturnButtonPos_.getY() + i * (50 * WIN_HEIGHT / 600));
            }
            else
            {
                pos = Vector2D(upturnButtonPos_.getX(), upturnButtonPos_.getY() + i * 50);
            }
            i++;

            e->getComponent<Transform>(TRANSFORM_H)->setPos(pos);
            e->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("UpturnButton"));
        }

        int j = 0;
        for (auto e : buttons2) {

            Vector2D pos;
            if (WIN_WIDTH / 900 == 1920 / 900) {
                pos = Vector2D((upturnButtonPos_.getX() + 330),
                    upturnButtonPos_.getY() + j * (50 * WIN_HEIGHT / 600));
            }
            else
            {
                pos = Vector2D((upturnButtonPos_.getX() + upturnButtonOffsetX * 3), upturnButtonPos_.getY() + j * 50);
            }
            j++;

            e->getComponent<Transform>(TRANSFORM_H)->setPos(pos);
            e->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("UpturnButton"));
        }
        exitShopButton_ = new Entity();
        exitShopButton_->setContext(this);
        Vector2D pos;
        if (WIN_WIDTH / 900 == 1920 / 900) {
            pos = Vector2D(upturnButtonPos_.getX() - 60, upturnButtonPos_.getY() + 510);
        }
        else pos = Vector2D(upturnButtonX - SHOP_WIDTH / 9, upturnButtonPos_.getY() + 275);

        if (WIN_WIDTH / 900 == 1920 / 900) {
            exitShopButtonTr_ = exitShopButton_->addComponent<Transform>(TRANSFORM_H, pos, (EXITSHOP_WIDTH / 2) * WIN_WIDTH / 900, (EXITSHOP_HEIGHT / 2) * WIN_HEIGHT / 600, 0.5);
        }
        else exitShopButtonTr_ = exitShopButton_->addComponent<Transform>(TRANSFORM_H, pos, EXITSHOP_WIDTH / 2, EXITSHOP_HEIGHT / 2);

        exitShopButton_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("ExitShop"));
        exitShopButtonComp_ = exitShopButton_->addComponent<Button>(BUTTON_H, "EXITSHOP");
        addEntity(exitShopButton_);
    }
    else { // creo botones por primera vez
        for (int i = 0; i < 4; i++) {
            upturnButton_ = new Entity();
            upturnButton_->setContext(this);
            Vector2D pos = Vector2D(upturnButtonPos_.getX(), upturnButtonPos_.getY() + i * (50 * WIN_HEIGHT / 600));
            if (WIN_WIDTH / 900 == 1920 / 900) {
                upturnButtonTr_ = upturnButton_->addComponent<Transform>(TRANSFORM_H, pos, (UPTURNBUTTON_WIDTH * WIN_WIDTH / 900) / 2,
                    (UPTURNBUTTON_HEIGHT * WIN_HEIGHT / 600) / 2, 0.5);
            }
            else upturnButtonTr_ = upturnButton_->addComponent<Transform>(TRANSFORM_H, pos, UPTURNBUTTON_WIDTH / 2, UPTURNBUTTON_HEIGHT / 2);

            upturnButtonComp_ = upturnButton_->addComponent<Button>(BUTTON_H, "UPTURN");
            upturnButton_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("UpturnButton"));
            buttonsComp.push_back(upturnButtonComp_);
            buttons1.push_back(upturnButton_);
        }
        for (int i = 0; i < 4; i++) {
            upturnButton_ = new Entity();
            upturnButton_->setContext(this);
            Vector2D pos;
            if (WIN_WIDTH / 900 == 1920 / 900) {
                pos = Vector2D((upturnButtonPos_.getX() + 330),
                    upturnButtonPos_.getY() + i * (50 * WIN_HEIGHT / 600));

                upturnButtonTr_ = upturnButton_->addComponent<Transform>(TRANSFORM_H, pos, (UPTURNBUTTON_WIDTH / 2) * WIN_WIDTH / 900,
                    (UPTURNBUTTON_HEIGHT / 2) * WIN_HEIGHT / 600, 0.5);
            }
            else
            {
                pos = Vector2D((upturnButtonPos_.getX() + upturnButtonOffsetX * 3), upturnButtonPos_.getY() + i * 50);
                upturnButtonTr_ = upturnButton_->addComponent<Transform>(TRANSFORM_H, pos, UPTURNBUTTON_WIDTH / 2, UPTURNBUTTON_HEIGHT / 2);
            }


            upturnButtonComp_ = upturnButton_->addComponent<Button>(BUTTON_H, "UPTURN");
            upturnButton_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("UpturnButton"));
            buttonsComp.push_back(upturnButtonComp_);
            buttons2.push_back(upturnButton_);
        }
        for (auto e : buttons1) {
            addEntity(e);
        }
        for (auto e : buttons2) {
            addEntity(e);
        }
        exitShopButton_ = new Entity();
        exitShopButton_->setContext(this);
        Vector2D pos;
        if (WIN_WIDTH / 900 == 1920 / 900) {
            pos = Vector2D(upturnButtonPos_.getX() - 60, upturnButtonPos_.getY() + 510);
        }
        else pos = Vector2D(upturnButtonX - SHOP_WIDTH / 9, upturnButtonPos_.getY() + 275);

        if (WIN_WIDTH / 900 == 1920 / 900) {
            exitShopButtonTr_ = exitShopButton_->addComponent<Transform>(TRANSFORM_H, pos, (EXITSHOP_WIDTH / 2) * WIN_WIDTH / 900, (EXITSHOP_HEIGHT / 2) * WIN_HEIGHT / 600, 0.5);
        }
        else exitShopButtonTr_ = exitShopButton_->addComponent<Transform>(TRANSFORM_H, pos, EXITSHOP_WIDTH / 2, EXITSHOP_HEIGHT / 2);

        exitShopButton_->addComponent<Image>(IMAGE_H, &SDLUtils::instance()->images().at("ExitShop"));
        exitShopButtonComp_ = exitShopButton_->addComponent<Button>(BUTTON_H, "EXITSHOP");
        addEntity(exitShopButton_);
    }

}

void TopDownState::cleanShopButtons() {
    for (auto e : buttons1) {
        e->removeComponent(IMAGE_H);
    }
    for (auto e : buttons2) {
        e->removeComponent(IMAGE_H);
    }
    exitShopButton_->setAlive(false);
    shopCreated_ = true;
}

void TopDownState::newQuest(string nombre, string text, string reward, int coins, int fases) {
    Entity* q = new Entity();
    q->addComponent<QuestInfoComponent>(QUESTINFOCOMPONENT_H, nombre, text, reward, coins, fases);
    addEntity(q);
    Quests::instance()->pushElement(q);
}

string TopDownState::getStateID() {
    return "TopDownState";
}
void TopDownState::desbloqueoZona() {
    cout << "se llama";
    collisions_.pop_back();
}
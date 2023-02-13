#include "TileMap.h"
void GameMap::render() {
	for (int i = 0; i < map_layers_.size(); ++i) {
		map_layers_[i]->render();
	}
}
void GameMap::update() {
	for (int i = 0; i < map_layers_.size(); ++i) {
		map_layers_[i]->update();
	}
}

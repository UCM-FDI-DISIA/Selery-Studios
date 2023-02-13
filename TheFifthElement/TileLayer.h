#pragma once
#include "Layer.h"
#include <vector>
#include <string>
using namespace std;
struct TileSet {
	int firstID_, lastID_,
		nrow_, ncol_,
		tile_count_, tile_size_;
	string name_, source_;


};
using TileSetVector = vector<TileSet>;
using TileMap = vector<vector<int>>;

class TileLayer:public Layer
{
private:
	int tilesize_;
	int numrows_, numcols_;

	TileMap tilemap_;
	TileSetVector tilesetvector_;


public:
	TileLayer(int tilesize,int width,int height, TileMap tilemap_,TileSetVector tilesetvector_);

	virtual void render();
	virtual void update(float dt);
	inline TileMap GetTileMap() { return tilemap_; }
};


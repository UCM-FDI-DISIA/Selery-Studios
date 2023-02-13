#include "TileLayer.h"
TileLayer::TileLayer(int tilesize, int numrows, int numcols, TileMap tilemap_, TileSetVector tilesetvector_) {
	this->tilesize_ = tilesize;
	this->tilemap_ = tilemap_;
	this->tilesetvector_ = tilesetvector_;
	numrows_ = numrows;
	numcols_= numcols;

}
void TileLayer::update(float dt) {

}
void TileLayer::render() {

}

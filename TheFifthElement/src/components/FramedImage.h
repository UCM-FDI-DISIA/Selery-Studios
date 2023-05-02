#pragma once
#ifndef FRAMEDIMAGE_H
#define FRAMEDIMAGE_H_
#include "../sdlutils/Texture.h"
#include "Transform.h" 
#include "../utils/Entity.h"
#include "../sdlutils/SDLUtils.h"

class FramedImage : public Component {
private:
	int frames_, col = 0, widthFrame_, heightFrame_, cont = 0, tope = 100, fila_;
	int framesPerRow_, nFilas_; // Se utiliza para imagenes con la misma animacion repartida en varias filas
	Transform* tr_; // Consulta las caracteristicas fisicas
	Texture* tex_;	// Imagen a rederizar
	SDL_RendererFlip s = SDL_FLIP_NONE;
	SDL_Rect dest, src;
	bool isAnimUnstoppable_ = false;
	float frameRate = FRAME_RATE;
	string type_, texKey_ = "";
public:
	//Constructora
	FramedImage(Texture* tex, int width, int height, int frames, string type = ""); // Imagen con una animacion en una fila
	FramedImage(Texture* tex, int width, int height, int frames, int fila, string type = ""); // Imagen con varias animaciones

	// Destructora
	virtual ~FramedImage();

	void initComponent();

	void update();

	// Dibuja en escena
	void render();

	inline int getCol() { return col; }
	inline int getLastFrame() { return frames_; }

	inline int getRow() { return fila_; }

	void setAnim(string textureKey, int frames, bool isAnimUnstoppable, int fila = 0); // Metodo generico para cambiar de animacion
	void setAnim(string textureKey, int col, int frames, bool isAnimUnstoppable, int fila = 0); // Metodo generico para cambiar de animacion desde una columna determinada
	void setAnim(string textureKey, int frames, int framesPerRow, int nFilas, bool isAnimUnstoppable, int fila = 0); // Metodo generico para cambiar de animacion repartida en varias filas

	inline bool isAnimPlaying() { return col < frames_ - 1; }

	inline void setTope(int i) { tope = i; }
	inline int getTope() const { return tope; }

	inline bool getIsAnimUnstoppable() { return isAnimUnstoppable_; }

	inline void setType(string newValue) { type_ = newValue; }
	inline string getType() { return type_; }


	inline string getTexKey() { return texKey_; }
	inline void setTexKey(string newValue) { texKey_ = newValue; }

	inline void setIsAnimUnstoppable(bool newValue) { isAnimUnstoppable_ = newValue; }

	inline void setWidthFrame(int newWidth) { widthFrame_ = newWidth; }
	inline void setHeightFrame(int newHeight) { heightFrame_ = newHeight; }

	void setFlip(SDL_RendererFlip Flip = SDL_FLIP_NONE) { s = Flip; }

	SDL_RendererFlip  getFlip() { return s; }
};
#endif


#pragma once
#ifndef ROULETTECOMPONENT_H
#define ROULETTECOMPONENT_H_
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include <string>
#include <iostream>
using namespace std;
class Roulette : public Component {
private:
	//PORICION DEL BORDE BLANCO Y TEXTURA
	Vector2D ruleta = { 20,10 };
	Texture* rueda = &SDLUtils::instance()->images().at("Ruleta");
	int rlt_width = 500, rlt_height = 370;
	int width = 65, height = 65;

	//POSICIONES Y TEXTURAS DE LOS PERSONAJES
	Vector2D p1 = { 50,40 };
	int width1 = 30, height1 = 30;
	//fuego
	Vector2D p2 = { 25,45 };
	int width2 = 20, height2 = 20;
	//calvo
	Vector2D p3 = { 30,20 };
	int width3 = 20, height3 = 20;
	// aire
	Vector2D p4 = { 50,10 };
	int width4 = 20, height4 = 20;

	int principal= 1;

public:
	virtual void update() {};
	virtual void render() {

		SDLUtils::instance()->images().at("Cartel").render({ 0,0,400,200 }, 0);
		choosandrender();
		SDL_Rect dest = { ruleta.getX(),ruleta.getY(),width,height };
		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.h = rlt_height;
		src.w = rlt_width;
		rueda->render( dest, 90);
		
	};
	virtual ~Roulette() {};
	void choosandrender() {
		SDL_Rect dest1 = { p1.getX(),p1.getY(),width1,height1 };
		SDL_Rect src1;
		src1.x = 0;
		src1.y = 0;
		src1.h = rlt_height;
		src1.w = rlt_width;
		SDLUtils::instance()->images().at("AirAvatar").render(src1, dest1);
		
		SDL_Rect dest2 = { p2.getX(),p2.getY(),width2,height2 };
		SDL_Rect src2;
		src2.x = 0;
		src2.y = 0;
		src2.h = rlt_height;
		src2.w = rlt_width;
		SDLUtils::instance()->images().at("FireAvatar").render(src2, dest2); 
		
		SDL_Rect dest3 = { p3.getX(),p3.getY(),width3,height3 };
		SDL_Rect src3;
		src3.x = 0;
		src3.y = 0;
		src3.h = rlt_height;
		src3.w = rlt_width;
		SDLUtils::instance()->images().at("WaterAvatar").render(src3, dest3);
		
		SDL_Rect dest4 = { p4.getX(),p4.getY(),width4,height4 };
		SDL_Rect src4;
		src4.x = 0;
		src4.y = 0;
		src4.h = rlt_height;
		src4.w = rlt_width;
		SDLUtils::instance()->images().at("EarthAvatar").render(src4, dest4);
	}
	void changeplayer(int a) {
		if (a == 1) {
			 p1 = { 50,40 };
			 width1 = 30;
			 height1 = 30;
			//fuego
			p2 = { 25,45 };
			width2 = 20;
			height2 = 20;
			//calvo
			 p3 = { 30,20 };
			 width3 = 20;
			 height3 = 20;
			// aire
			 p4 = { 50,10 };
			 width4 = 20; height4 = 20;
		}
		else if (a==2) {
			p2 = { 50,40 };
			width2 = 30;
			height2 = 30;
			//fuego
			p1 = { 25,45 };
			width1 = 20;
			height1 = 20;
			//calvo
			p3 = { 30,20 };
			width3 = 20;
			height3 = 20;
			// aire
			p4 = { 50,10 };
			width4 = 20; height4 = 20;
		}
		else if (a == 3) {
			p3 = { 50,40 };
			width3 = 30;
			height3 = 30;
			//fuego
			p1 = { 25,45 };
			width1 = 20;
			height1 = 20;
			//calvo
			p2 = { 30,20 };
			width2 = 20;
			height2 = 20;
			// aire
			p4 = { 50,10 };
			width4 = 20; height4 = 20;
		}
		else if (a == 4) {
			p4 = { 50,40 };
			width4 = 30;
			height4 = 30;
			//fuego
			p1 = { 25,45 };
			width1 = 20;
			height1 = 20;
			//calvo
			p2 = { 30,20 };
			width2 = 20;
			height2= 20;
			// aire
			p3 = { 50,10 };
			width3 = 20; height4 = 20;
		}
	}
#pragma endregion
};
#endif

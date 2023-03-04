#include "HUD.h"

void HUD::indexSkin(string skin)//estoy dudando si es necesario aunque lo puedo hacer funcionar si luego hago otro array y así traslado indexes
{
	int x;
	for (int i = 0; i < skins_->length(); i++)
	{
		if (skins_[i] == skin)
		{
			x = i;
		}
	}
	rotateWheel(x);
}

void HUD::rotateWheel(int index)
{
	//puedo tener un index de texturas y al pasar el int voy poniendo posiciones fijas al contenido de cada index
	//necesito encontrar la manera de unir los iconos a un vector2d que les dé su posición para que rotate sea genérico
	//x corresponde al primer elemento de los vectores, al front, y voy a necesitar capar el index desde 0 al 3 para que sea ciclico
	//a la vez que se asigna el vector se crea directamente la imagen, la idea será con rects donde la pos es el vector y la altura y ancho una cte de icono
}
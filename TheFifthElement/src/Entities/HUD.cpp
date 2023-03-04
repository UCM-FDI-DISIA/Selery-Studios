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
}
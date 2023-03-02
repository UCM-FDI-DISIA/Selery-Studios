#include "ColliderTile.h"

void ColliderTile::update() {

	//tia una cosa, en el bucle de update de entity se llama a que haga el update de los componentes, deberia hacer un componente 
	//aññadirlo a ColliderTile y ponerle este update, porque si se lo pongo a entity no se va a hacer,no se si me entiendes
	//yo creo que mejor lo añado como component y asi no modifico entity
	if (isActive_) {
		if (collide(game->getPlayer()->getCollider())) {
			isColliding_ = true;
			onPlayerCollision();
		}
		else if (isColliding_) { // La colisión estaba activa pero ha parado

			isColliding_ = false;
			onPlayerCollisionExit();
		}
	}
}

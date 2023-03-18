#pragma once
#ifndef ECS_H_
#define ECS_H_

using cmpId_type = int;
enum cmpId : cmpId_type {
	// ... (compoment ids)
	TRANSFORM_H = 0,
	RENDERCOMPONENT_H = 1,
	INPUTCOMPONENT_H = 2,
	SKINCOMPONENT_H = 3,
	CHECKCOLLISION_H = 4,
	LIFECOMPONENT_H = 5,
	SHADOWCOMPONENT_H=6,
	IMAGE_H = 7,
	INPUTCOMPONENTBEU_H = 8,
	JUMP_H = 9,
	MOVEMENTCOMPONENT_H = 10,
	ENEMYBEUDIRECTIONCOMPONENT_H = 11,
	DIALOGCOMPONENT_H = 12,
	OBJECTSCOMPONENT_H = 13,
	ENEMY_MOVEMENT_TD_H = 14,
	CAMERACOMPONENT_H = 15,
	ATTACKBOXCOMPONENT_H = 16,
	COLLIDERCOMPONENT_H = 17,
	COLDETECTORCOMPONENT_H = 18,
	LIMITBEU_H = 19,
	ANIMATIONENEMYBEUCOMPONENT_H = 20,
	BUTTON_H = 21,
	COLLIDERTILE_H = 22,
	PORTALCOMPONENT_H =23,
	SHOPCOMPONENT_H = 24,
	MOVEMENTEARTHBOSSCOMPONENT_H = 25,
	LIFEEARTHBOSSCOMPONENT_H = 26,
	ANIMATIONEARTHBOSSCOMPONENT_H = 27,
	REDIRECTENEMY_H = 28,
	POINTOFFIGHTCOMPONENT_H = 29,
	BRIGHTSLIDER_H = 30,
	SLIDERCOMPONENT_H = 31,
	SKINBEUCOMPONENT_H = 32,


	// do not remove this
	_LAST_CMP_ID
};
constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

#endif // !ECS_H_
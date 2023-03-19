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
	IMAGE_H = 6,
	INPUTCOMPONENTBEU_H = 7,
	JUMP_H = 8,
	MOVEMENTCOMPONENT_H = 9,
	ENEMYBEUDIRECTIONCOMPONENT_H = 10,
	DIALOGCOMPONENT_H = 11,
	OBJECTSCOMPONENT_H = 12,
	ENEMY_MOVEMENT_TD_H = 13,
	CAMERACOMPONENT_H = 14,
	ATTACKBOXCOMPONENT_H = 15,
	COLLIDERCOMPONENT_H = 16,
	COLDETECTORCOMPONENT_H = 17,
	LIMITBEU_H = 18,
	ANIMATIONENEMYBEUCOMPONENT_H = 19,
	BUTTON_H = 20,
	COLLIDERTILE_H = 21,
	PORTALCOMPONENT_H =22,
	SHOPCOMPONENT_H = 23,
	MOVEMENTEARTHBOSSCOMPONENT_H = 24,
	LIFEEARTHBOSSCOMPONENT_H = 25,
	ANIMATIONEARTHBOSSCOMPONENT_H = 26,
	REDIRECTENEMY_H = 27,
	NPCCOLLISIONCOMPONENTT=28,
	PLAYERNPC_H =29,
	// do not remove this
	_LAST_CMP_ID
};
constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

#endif // !ECS_H_
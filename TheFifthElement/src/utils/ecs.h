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
	SHADOWCOMPONENT_H = 6,
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
	PORTALCOMPONENT_H = 23,
	SHOPCOMPONENT_H = 24,
	MOVEMENTEARTHBOSSCOMPONENT_H = 25,
	LIFEEARTHBOSSCOMPONENT_H = 26,
	ANIMATIONEARTHBOSSCOMPONENT_H = 27,
	REDIRECTENEMY_H = 28,
	POINTOFFIGHTCOMPONENT_H = 29,
	BRIGHTSLIDER_H = 30,
	SLIDERCOMPONENT_H = 31,
	SKINBEUCOMPONENT_H = 32,
	ATTACKEARTHBOSSCOMPONENT_H = 33,
	NPCCOLLISIONCOMPONENTT = 34,
	PLAYERNPC_H = 35,
	ECONOMYCOMPONENT_H = 36,
	VOLUMESLIDER_H = 37,
	LIFETDCOMPONENT_H = 38,
	DAMAGE_H = 39,
	ROULETTECOMPONENT_H = 40,
	SPAWN_H = 41,
	SECTORCOLLISIONCOMPONENT_H = 42,
	BOSSCOLLISION_H = 43,
	SAVING_H=44,
	LIFELIGHTBOSSCOMPONENT_H=45,
	MOVEMENTLIGHTBOSSCOMPONENT_H=46,
	ATTACKLIGHTBOSSCOMPONENT_H=47,
	ANIMATIONLIGHTBOSSCOMPONENT_H=48,
	WATERBOSSIA_H = 49,
	WATERBOSSLIFE_H = 50,
	DISABLEONEXIT_H = 51,
	FRAMEDIMAGE_H = 52,
	STONECOMPONENT_H = 53,
	PROTECTIONEARTHBOSSCOMPONENT_H = 54,
	ICESHADOWCOMPONENT_H = 55,
	ICEIACOMPONENT_H = 56,
	LIGHTBOSSELEMENT_H=57,
	THROWABLEOBJECT_H = 58,
	FIREBOSSCOMPONENT_H=59,
	LIFEBASICCOMPONENT_H=60,
	POWERUPCTRL_H = 61,
	QUESTINFOCOMPONENT_H = 62,
	TRIGGER_H = 63,
	REWARDTEXTCOMPONENT_H = 64,
	DECKMANAGERCOMPONENT_H = 65,
	IADECKCOMPONENT_H=66,
	CARDPLAYERLIFECOMPONENT_H=67,
	// do not remove this
	_LAST_CMP_ID
};
constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

#endif // !ECS_H_
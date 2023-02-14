#pragma once
#ifndef ECS_H_
#define ECS_H_

using cmpId_type = int;
enum cmpId : cmpId_type {
	// ... (compoment ids)
	TRANSFORM_H = 0,
	RENDERCOMPONENT_H = 1,
	INPUTCOMPONENT_H = 2,
	MOVEMENTCOMPONENT_H = 3,
	CHECKCOLLISION_H = 4,
	LIFEBARCOMPONENT_H = 5,
	CAMERACOMPONENT_H = 6,
	// do not remove this
	_LAST_CMP_ID
};
constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

#endif // !ECS_H_
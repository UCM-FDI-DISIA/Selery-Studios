#pragma once
#ifndef ECS_H_
#define ECS_H_

using cmpId_type = int;
enum cmpId : cmpId_type {
	_TRANSFORM_H_ =0,
	// ... (compoment ids)
	RENDERCOMPONENT_H_ =1,
	_MOVEMENTCOMPONENT_ =2,
	// do not remove this
	_LAST_CMP_ID
};
constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

#endif // !ECS_H_
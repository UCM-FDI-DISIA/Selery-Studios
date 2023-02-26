#pragma once
#ifndef ECS_H_
#define ECS_H_

using cmpId_type = int;
<<<<<<< Updated upstream
namespace ecs {
	enum cmpId : cmpId_type {
		_TRANSFORM = 0,
		// ... (compoment ids)

		// do not remove this
		_LAST_CMP_ID
	};
	constexpr cmpId_type maxComponentId = _LAST_CMP_ID;
}

=======
enum cmpId : cmpId_type {
	_TRANSFORM_H_ = 0,
	// ... (compoment ids)
	RENDERCOMPONENT_H = 1,
	INPUTCOMPONENT_H = 2,
	MOVEMENTCOMPONENT_H = 3,
	CHECKCOLLISION_H = 4,
	// do not remove this
	_LAST_CMP_ID
};
constexpr cmpId_type maxComponentId = _LAST_CMP_ID;
>>>>>>> Stashed changes

#endif // !ECS_H_
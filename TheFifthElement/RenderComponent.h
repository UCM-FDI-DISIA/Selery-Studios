#pragma once
#ifndef RENDERCOMP_
#define RENDERCOMP_
#include "Transform.h"
#include "sdlutils/Texture.h"

class RenderComponent : public Component {
	public:
		RenderComponent() {};
		RenderComponent(Texture* t, Entity* e) :Component() {
			ent_ = e;
			tx_ = t;
			//tr_ = ent_->getComponent<Transform>(int(TRANSFORM_H_));
		};
		virtual ~RenderComponent() {};
		void getTransform() {
			
		}
	private:
		Transform* tr_;
		Texture* tx_;
	protected:	
};
#endif
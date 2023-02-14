#pragma once
#include "utils/Entity.h"
#include "Transform.h"
#include "utils/ecs.h"
#include "GameManager.h"
#include "PlayerTD.h"
#include "CameraComponent.h"


class Camera : public Entity
{
private:

	/*Camera() { m_ViewBox = { 0, 0, WIN_WIDTH, WIN_HEIGHT }; }
	Vector2D m_Position;
	Vector2D m_PlayerPos;

	SDL_Rect m_ViewBox;
	static Camera* s_Instance;*/


	Vector2D camPosition_;
	Vector2D camVelocity_;
	float camRotation_ = 0;
	Transform* tr;
	/*Transform* trPlayer_;*/
	GameManager* m;
	PlayerTD* player_;
	/*CameraComponent* cc;*/

public:

	/*inline SDL_Rect GetViewBox() { return m_ViewBox; }
	inline Vector2D GetPosition() { return m_Position; }
	inline void SetTarget(Vector2D* player) { m_PlayerPos = player; }*/
	
	Camera(GameManager* gm_) : Entity() {
		cmpId_type z = int(TRANSFORM_H);
		tr = addComponent<Transform>(z, camPosition_, camVelocity_, WIN_WIDTH, WIN_HEIGHT, camRotation_);
	}

	~Camera()
	{

	}

	void update()
	{
		
	}


	Camera(GameManager* gm_, PlayerTD* player) : Entity()
	{
		m = gm_;
		player_ = player;
		cmpId_type z = int(TRANSFORM_H);
		tr = addComponent<Transform>(z, camPosition_, camVelocity_, WIN_WIDTH, WIN_HEIGHT, camRotation_);

		cmpId_type k = int(CAMERACOMPONENT_H);
		addComponent<CameraComponent>(k, m, player_);

		/*player_ = player;
		trPlayer_ = player_->getComponent<Transform>(z);*/
	}

};



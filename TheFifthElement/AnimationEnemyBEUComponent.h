#pragma once
#include "src/utils/Component.h"
#include "src/utils/Vector2D.h"
#include "src/sdlutils/SDLUtils.h"
#include "src/sdlutils/Texture.h"
#include <string>
using namespace std;

class AnimationEnemyBEUComponent :
    public Component
{
public:
	#pragma region EnumAnims
		enum AnimationStates
		{
			Moving, Attack, Hit, Death, Null
		};

		AnimationStates currentState_;
		AnimationStates nextState_;

	#pragma endregion
private:
	#pragma region ColliderData
		Vector2D offset_ = Vector2D(0, 0);
		float ColWidth_, ColHeight_;
	#pragma endregion

	#pragma region spritesData
		float EnemyWidth_, EnemyHeight_;
		int nframes_;
	#pragma endregion

	#pragma region infoEnemies
		string type_, enemy_;
	#pragma endregion

	#pragma region references
		Texture* t_;
	#pragma endregion

public:
	AnimationEnemyBEUComponent(string type, string enemy) {
		currentState_ = nextState_ = Null;

		type_ = type;
		enemy_ = enemy;
	}

	void update();
	void changeState(AnimationStates newState);
	void updateAnimation();
	void updateAn();

	void setMovTexture();
	void setAttackTexture();
	void setHitTexture();
	void setDeathTexture();
};


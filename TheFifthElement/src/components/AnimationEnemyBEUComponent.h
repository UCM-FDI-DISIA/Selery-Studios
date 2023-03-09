#pragma once
#include "../utils/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/ColliderComponent.h"
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
		Image* im_;
		Transform* tr_;
		Transform* playerTr_;
		ColliderComponent* col_;
	#pragma endregion

		bool set_ = false;

public:
	AnimationEnemyBEUComponent(string type, string enemy, Transform* plTr) {
		currentState_ = nextState_ = Null;

		type_ = type;
		enemy_ = enemy;
		playerTr_ = plTr;
	}

	void update();
	void changeState(AnimationStates newState);
	void updateAnimation();
	void updateAn();

	void setMovTexture();
	void setAttackTexture();
	void setHitTexture();
	void setDeathTexture();

	int getNFrames() { return nframes_; }
	Texture* getTexture() { return t_; }
	Vector2D getOffset() { return offset_; }
	int getColWidth() { return ColWidth_; }
	int getColHeight() { return ColHeight_; }
};


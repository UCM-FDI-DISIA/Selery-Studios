#pragma once
#include "../utils/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include <string>
using namespace std;

class AnimationEnemyBEUComponent : public Component {
public:
#pragma region EnumAnims
	enum AnimationStates{
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
#pragma endregion

	bool set_ = false;

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
	inline int Get_enemy_Width() { return EnemyWidth_; }
	inline int Get_enemy_Height() { return EnemyHeight_; }
	inline Texture* Get_enemy_Texture() { return t_; }
	inline string Get_enemy() { return enemy_; }
	inline string Get_type() { return type_; }
};



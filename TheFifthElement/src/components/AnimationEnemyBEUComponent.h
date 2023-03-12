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
	Entity* player_;

	Texture* t_;
	Image* im_;
	Transform* tr_;
	Transform* playerTr_;
	ColliderComponent* col_;
	ColliderComponent* playerCol_;
#pragma endregion

#pragma region parameters
	bool set_ = false;
	float posX, playerPosX;
#pragma endregion


public:
	AnimationEnemyBEUComponent(string type, string enemy, Entity* player) {
		currentState_ = nextState_ = Null;

		type_ = type;
		enemy_ = enemy;
		player_ = player;
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
	inline string getEnemy() { return enemy_; }
	inline string getType() { return type_; }
	inline float getWidth() { return EnemyWidth_; }
	inline float getHeight() { return EnemyHeight_; }
};


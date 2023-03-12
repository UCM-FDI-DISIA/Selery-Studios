//#pragma once
//#include "../utils/Entity.h"
//#include "../components/Image.h"
//#include "../components/Transform.h"
//#include "../sdlutils/Texture.h"
//#include "../utils/Vector2D.h"
//
//class LifeBar : public Entity
//{
//private:
//#pragma region parameters
//	float maxLife_, life_;
//	string type_;
//#pragma endregion
//
//#pragma region references
//	Transform* entTransform_;
//#pragma endregion
//
//#pragma region propierties
//	Vector2D pos_;
//#pragma endregion
//
//#pragma region LifeBar
//	float barWidth_, barHeight_;
//	Texture* barTexture_;
//	/*Transform* barTransform_;
//	Image* barImage_;*/
//#pragma endregion
//
//#pragma region LifeBarBack
//	float backWidth_, backHeight_;
//	Texture* backTexture_;
//	/*Transform* backTransform_;
//	Image* backImage_;*/
//#pragma endregion
//
//#pragma region LifeBarBorder
//	float borderWidth_, borderHeight_;
//	Texture* borderTexture_;
//	/*Transform* borderTransform_;
//	Image* borderImage_;*/
//#pragma endregion
//
//public:
//	LifeBar(float life, string type, Entity* ent);
//	void subLife(float life);
//	void updatePos();
//	void chooseTexture();
//	void setAll();
//	void renderAll();
//	float getMaxLife() { return maxLife_; }
//};
//

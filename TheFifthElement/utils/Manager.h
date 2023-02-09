//#pragma once
//#include <vector>
//#include "Entity.h"
//using namespace std;
//
//class Manager {
//private:
//	//vector<Entity*> ents_;
//	static Manager* instance_;
//	Manager() {
//		ents_.reserve(100);
//		/*for (auto& grpEnts : entsByGroup_) {
//			grpEnts.reserve(100);
//		}*///groups
//	}
//public:
//	static Manager* getInstance() {
//		if (instance_ == nullptr)
//			instance_ = new Manager();
//		return instance_;
//	}
//	virtual ~Manager();
//	//Entity* addEntity();
//	void refresh();
//	void update();
//	void render();
//
//	#pragma region Groups
//	/*void addToGroupList(grpId_type gId, Entity* e);
//	inline const auto& getEntities() { return ents_; }
//	inline const auto& getEntitiesByGroup(grpId_type gId) {
//		return entsByGroup_[gId];
//	}
//	private:
//		array<vector<Entity*>, maxGroupId> entsByGroup_;*/
//	#pragma endregion
//
//};

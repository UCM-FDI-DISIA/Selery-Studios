#pragma once
#include <vector>
#include "Entity.h"
#include "Singleton.h"
//#include "uptr.h"
using namespace std;


class Manager:public Singleton <Manager> {
protected:
	vector<Entity*> ents_;
public:

	Manager();
	virtual ~Manager();
	Entity* addEntity();
	void refresh();
	void update();
	void render();

	#pragma region Groups
	/*void addToGroupList(grpId_type gId, Entity* e);
	inline const auto& getEntities() { return ents_; }
	inline const auto& getEntitiesByGroup(grpId_type gId) {
		return entsByGroup_[gId];
	}
	private:
		array<vector<Entity*>, maxGroupId> entsByGroup_;*/
	#pragma endregion

};

//#include "Manager.h"
//
//
//Manager::~Manager() {
//	for (auto e : ents_) {
//		delete e;
//	}
//}
//
//Entity* Manager::addEntity() {
//	Entity* e = new Entity();
//	e->setAlive(true);
//	ents_.push_back(e);
//	return e;
//}
//
//void Manager::refresh() {
//	ents_.erase(
//		remove_if(ents_.begin(), ents_.end(), [](Entity* e) {
//			if (e->isAlive()) {
//				return false;
//			}
//			else {
//				delete e;
//				return true;
//			}
//			}), 
//		ents_.end());
//}
//
//void Manager::update() {
//	auto n = ents_.size();
//	for (auto i = 0u; i < n; i++)
//		ents_[i]->update();
//}
//
//void Manager::render() {
//	auto n = ents_.size();
//	for (auto i = 0u; i < n; i++)
//		ents_[i]->render();
//}
//
//	#pragma region Groups
//	/*void Manager::addToGroupList(grpId_type gId, Entity* e) {
//		entsByGroup_[gId].push_back(e);
//	}
//	void Manager::refresh() {
//		for (ecs::grpId_type gId = 0; gId < ecs::maxGroupId; gId++) {
//			auto& grpEnts = entsByGroup_[gId];
//			grpEnts.erase(
//				std::remove_if(grpEnts.begin(), grpEnts.end(),
//					[gId](Entity* e) {
//						return !e->isAlive() || !e->hasGroup(gId);
//					}),
//				grpEnts.end());
//		}
//	}*/
//	///falta a partir de la diapo 51
//	#pragma endregion
//

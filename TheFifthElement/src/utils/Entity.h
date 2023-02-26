#pragma once
#include "Component.h"
#include "ecs.h"
#include <array>
#include <vector>
#include <bitset>

using namespace std;

class Entity
{
private:
	bool alive_;
	Manager* mngr_;
	vector<Component*> currCmps_;
	array<Component*, maxComponentId> cmps_;
public:
	Entity() :mngr_(nullptr), cmps_(), currCmps_(), alive_() {

		currCmps_.reserve(maxComponentId);
	}
	virtual void initEntity() { }
	virtual ~Entity() {
		for (auto c : currCmps_) {
			delete c;
		}
	}
	// Asigna a la entidad su manager
	inline void setContext(Manager* mngr) { mngr_ = mngr; }
	// Devuelve si esta vivo
	inline bool isAlive() {
		return alive_;
	}

	inline void setAlive(bool alive) {
		alive_ = alive;
	}
	// Crea un componente
	template<typename T, typename ...Ts>
	inline T* addComponent(cmpId_type cId, Ts && ...args) {
		T* c = new T(forward<Ts>(args)...);
		// Borra el componente actual de la posici�n cId en caso 
		// de encontrar el componeent
		removeComponent(cId);
		// Anade al array y a la lista de componentes
		currCmps_.push_back(c);
		cmps_[cId] = c;
		// Inicializa el componente
		c->setContext(this, mngr_);
		c->initComponent();
		return c;
	}

	inline void removeComponent(cmpId_type cId) {
		if (cmps_[cId] != nullptr) {
			auto iter = std::find(currCmps_.begin(),
				currCmps_.end(),
				cmps_[cId]);
			currCmps_.erase(iter);
			delete cmps_[cId];
			cmps_[cId] = nullptr;
		}
	}

	template<typename T>
	inline T* getComponent(cmpId_type cId) {
		return static_cast<T*>(cmps_[cId]);
	}

	inline bool hasComponent(cmpId_type cId) {
		return cmps_[cId] != nullptr;
	}

	inline void update() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++)
			currCmps_[i]->update();
	}

	inline void render() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++)
			currCmps_[i]->render();
	}

	virtual void collision() {};
};


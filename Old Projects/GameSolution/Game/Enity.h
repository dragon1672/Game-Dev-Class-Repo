#ifndef ENTITY_H
#define ENTITY_H
#include <cassert>
#include "Component.h"


namespace Entities {
	class Component;
	class Entity {
		static const unsigned int NUM_MAX_COMPONENTS = 50;
		Component* components[NUM_MAX_COMPONENTS];
		int numComponents;
	public:
		bool initialize() {
			numComponents = 0;
			return true;
		}
		bool shutdown() {
			return true;
		}
		void addComponent(Component* component) {
			assert(numComponents!=NUM_MAX_COMPONENTS);
			components[numComponents++] = component;
			component->parent = this;
		}
	}
};
#endif
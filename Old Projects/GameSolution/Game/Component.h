#ifndef COMPONENT_H
#define COMPONENT_H
namespace Entities {
	class Entity;
	class Component {
		friend class Entity;
		Entity* parent;
	public:
		virtual void update() {}
	}
}

#endif
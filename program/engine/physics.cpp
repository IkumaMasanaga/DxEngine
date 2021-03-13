#include "physics.h"
#include "object/mover/physics_object.h"


namespace dxe {

	void Physics::update() {

		// d—Í‚ÌŒvZ
		std::list<std::shared_ptr<PhysicsObject>>::iterator it = physics_objects_.begin();
		while (it != physics_objects_.end()) {
			if (!(*it)->isAlive()) {
				it = physics_objects_.erase(it);
				continue;
			}
			(*it)->addForceTime(gravity_ * (*it)->gravity_scale_);
			(*it)->addForceTime(-((*it)->getVelocity() * (*it)->drag_));
			(*it)->transform_.position_ += (*it)->toLocalPosition((*it)->getVelocity());
			++it;
		}

	}

}

#include "physics.h"
#include "object/mover/physics_object.h"


namespace dxe {

	void Physics::update() {

		// d—Í‚Æ‹ó‹C’ïR‚ÌŒvZ
		std::list<std::shared_ptr<PhysicsObject>>::iterator it = physics_objects_.begin();
		while (it != physics_objects_.end()) {
			if (!(*it)->isAlive()) {
				it = physics_objects_.erase(it);
				continue;
			}
			(*it)->velocity_ += (gravity_ * (*it)->gravity_scale_ * t2k::Time::getDeltaTime());
			(*it)->transform_.position_ += (*it)->toLocalPosition((*it)->velocity_);
			(*it)->velocity_ *= (t2k::Vector3::ONE - (*it)->drag_);
			++it;
		}

	}

}

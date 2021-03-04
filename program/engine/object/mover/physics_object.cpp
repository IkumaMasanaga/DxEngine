#include "../../physics.h"
#include "../../collision_manager.h"
#include "physics_object.h"


namespace dxe {

	void PhysicsObject::shared_from_this_constructor() {
		Physics::getInstance().physics_objects_.emplace_back(std::dynamic_pointer_cast<PhysicsObject>(shared_from_this()));
		CollisionObject::shared_from_this_constructor();
	}

	void PhysicsObject::onCollision(CollisionObject::SharedPtr other, std::shared_ptr<CollisionRect> rect, const CorrectDirection direction) {

		// �␳�����Ƃ��̂ݖ��C�̌v�Z���s
		if (direction != CorrectDirection::NONE) {
			t2k::Vector3 gravity = Physics::getInstance().gravity_;
			gravity.normalize();
			gravity.x = std::abs(gravity.x);
			gravity.y = std::abs(gravity.y);
			velocity_ *= (t2k::Vector3::ONE - ((t2k::Vector3::ONE - gravity) * friction_) * gravity_scale_);

			if (direction == CorrectDirection::UP || direction == CorrectDirection::DOWN) {
				velocity_.y = 0;
			}
			else if (direction == CorrectDirection::LEFT || direction == CorrectDirection::RIGHT) {
				velocity_.x = 0;
			}
		}

		// �h���N���X�̏Փ˔��菈��
		onCollisionOfPhysicsObject(other, rect, direction);
	}

}

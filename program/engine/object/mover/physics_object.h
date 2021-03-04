#pragma once
#include "collision_object.h"


namespace dxe {

	// �������Z�̉e�����󂯂�N���X
	// �d�́A���C�A��C��R
	class PhysicsObject : public CollisionObject {
	public:
		using SharedPtr = std::shared_ptr<PhysicsObject>;
		using WeakPtr = std::weak_ptr<PhysicsObject>;
	private:
		// velocity_�𒼐ڈ�����
		friend class Physics;
		// shared_from_this_constructor���ĂԂ���
		friend class t2k::SharedFactory<Object>;

		//====================================================================================================
		// �����o�ϐ�

		// ����
		t2k::Vector3 velocity_ = t2k::Vector3::ZERO;

		//====================================================================================================
		// �����o�֐�

		// �Փˎ��̏���
		void onCollision(CollisionObject::SharedPtr other, std::shared_ptr<CollisionRect> rect, const CorrectDirection direction) final override;

		//====================================================================================================
	protected:
		//====================================================================================================
		// �����o�֐�

		// shared_from_this���g����R���X�g���N�^
		virtual void shared_from_this_constructor() override;

		// �Փˎ��̔h���N���X�̏���
		// ���̃N���X�̔h���N���X�ŗL�̏Փˎ��̐U�镑�����������Ƃ��͂��̊֐�����������
		virtual void onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<CollisionRect> rect, const CorrectDirection direction) {}

		//====================================================================================================
	public:
		PhysicsObject() {}
		virtual ~PhysicsObject() {}

		//====================================================================================================
		// �����o�ϐ�

		// �d�͂̉e������
		float gravity_scale_ = 1.0f;

		// ���C����
		t2k::Vector3 friction_ = t2k::Vector3(0.8f, 0.8f, 0.0f);

		// ��C��R����
		t2k::Vector3 drag_ = t2k::Vector3(0.02f, 0.0f, 0.0f);

		//====================================================================================================
		// �����o�֐�

		// �����𑫂�
		inline void addForce(const t2k::Vector3 force) { velocity_ += (force * t2k::Time::getDeltaTime()); }

		//====================================================================================================
	};

}

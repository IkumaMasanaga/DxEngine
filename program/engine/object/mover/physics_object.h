#pragma once
#include "collision_object.h"


namespace dxe {

	// 物理演算の影響を受けるクラス
	// 重力、摩擦、空気抵抗
	class PhysicsObject : public CollisionObject {
	public:
		using SharedPtr = std::shared_ptr<PhysicsObject>;
		using WeakPtr = std::weak_ptr<PhysicsObject>;
	private:
		// velocity_を直接扱う為
		friend class Physics;
		// shared_from_this_constructorを呼ぶため
		friend class t2k::SharedFactory<Object>;

		//====================================================================================================
		// メンバ変数

		// 速さ
		t2k::Vector3 velocity_ = t2k::Vector3::ZERO;

		//====================================================================================================
		// メンバ関数

		// 衝突時の処理
		void onCollision(CollisionObject::SharedPtr other, std::shared_ptr<CollisionRect> rect, const CorrectDirection direction) final override;

		//====================================================================================================
	protected:
		//====================================================================================================
		// メンバ関数

		// shared_from_thisが使えるコンストラクタ
		virtual void shared_from_this_constructor() override;

		// 衝突時の派生クラスの処理
		// このクラスの派生クラス固有の衝突時の振る舞いをしたいときはこの関数を実装する
		virtual void onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<CollisionRect> rect, const CorrectDirection direction) {}

		//====================================================================================================
	public:
		PhysicsObject() {}
		virtual ~PhysicsObject() {}

		//====================================================================================================
		// メンバ変数

		// 重力の影響割合
		float gravity_scale_ = 1.0f;

		// 摩擦割合
		t2k::Vector3 friction_ = t2k::Vector3(0.8f, 0.8f, 0.0f);

		// 空気抵抗割合
		t2k::Vector3 drag_ = t2k::Vector3(0.02f, 0.0f, 0.0f);

		//====================================================================================================
		// メンバ関数

		// 速さを足す
		inline void addForce(const t2k::Vector3 force) { velocity_ += (force * t2k::Time::getDeltaTime()); }

		//====================================================================================================
	};

}

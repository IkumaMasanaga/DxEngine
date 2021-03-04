#pragma once
#include "vector.h"


namespace t2k {

	class Transform {
	public:
		Vector3 position_ = Vector3::ZERO;
		float rotation_ = 0.0f;
		float scale_ = 1.0f;
	};

}

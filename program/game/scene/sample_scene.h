#pragma once
#include "../../engine/dxe.h"


class SampleScene final : public dxe::Scene {
public:
	using SharedPtr = std::shared_ptr<SampleScene>;
	using WeakPtr = std::weak_ptr<SampleScene>;
private:
	dxe::Screen::SharedPtr main_screen_ = nullptr;
	dxe::PhysicsObject::SharedPtr player_ = nullptr;
	dxe::RectRenderer::SharedPtr rect_renderer_ = nullptr;

	void initialize() final override;

	void lateUpdate() final override;

public:
	SampleScene() {}
	~SampleScene() {}
};

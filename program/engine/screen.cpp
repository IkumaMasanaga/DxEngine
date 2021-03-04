#include "DxLib.h"
#include "screen.h"
#include "dx_engine.h"
#include "collision_manager.h"
#include "scene.h"
#include "object/object.h"
#include "object/mover/render_object/render_object.h"


namespace dxe {

	void Screen::renderToTexture() {

		std::list<std::shared_ptr<RenderObject>> renders = getScene()->renders_;

		renders.sort([](const std::shared_ptr<RenderObject> left, const std::shared_ptr<RenderObject> right) {
			return left->render_priority_ < right->render_priority_;
		});

		SetDrawScreen(texture_->getImage());
		ClearDrawScreen();

		for (auto obj : renders) {
			if (!obj->isActive()) continue;
			obj->render(shared_from_this());
		}

		CollisionManager& collision_manager = CollisionManager::getInstance();
		if (collision_manager.is_render_debug_area_) {
			collision_manager.renderDebugArea(shared_from_this());
		}
		
		SetDrawScreen(DX_SCREEN_BACK);

	}

	void Screen::render() const {
		DxEngine& engine = DxEngine::getInstance();
		int w = engine.getWindowWidth() >> 1;
		int h = engine.getWindowHeight() >> 1;
		int rx = (int)(w + position_.x);
		int ry = (int)(h + position_.y);

		// 描画モードのリセット
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawRotaGraph(rx, ry, 1.0f, 0.0f, texture_->getImage(), true);
	}

	Screen::SharedPtr Screen::create(std::shared_ptr<Camera2D> camera, const int width, const int height) {
		Screen::SharedPtr ptr = SharedFactory::create<Screen>();
		ptr->camera_ = camera;
		ptr->texture_ = t2k::Texture::createRenderTexture(width, height);
		return ptr;
	}

}

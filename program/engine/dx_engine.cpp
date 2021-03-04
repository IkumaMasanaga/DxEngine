#include "dx_engine.h"
#include "scene.h"


namespace dxe {

	void DxEngine::initialize(const int window_width, const int window_hieght, std::shared_ptr<Scene> first) {
		window_width_ = window_width;
		window_height_ = window_hieght;
		now_scene_ = next_scene_ = first;
		now_scene_->initialize();
	}

	void DxEngine::update() {
		if (now_scene_ != next_scene_) {
			now_scene_->finalize();
			now_scene_ = next_scene_;
			now_scene_->initialize();
		}
		now_scene_->update();
		now_scene_->render();
	}

	void DxEngine::finalize() {

	}

}

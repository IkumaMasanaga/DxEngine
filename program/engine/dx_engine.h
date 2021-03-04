#pragma once
#include "../library/t2klib.h"
#include "../system/dx_main.h"


namespace dxe {

	class Scene;

	class DxEngine final : public t2k::Singleton<DxEngine> {
	private:
		// 基底クラスで生成するため
		friend class t2k::Singleton<DxEngine>;
		// initialize, update, finalizeを呼ぶため
		friend class sys::DxMain;

		DxEngine() {}

		//====================================================================================================
		// メンバ変数

		bool is_playing_game_ = true;
		int window_width_ = 0;
		int window_height_ = 0;
		std::shared_ptr<Scene> now_scene_ = nullptr;
		std::shared_ptr<Scene> next_scene_ = nullptr;

		//====================================================================================================
		// メンバ関数

		void initialize(const int window_width, const int window_hieght, std::shared_ptr<Scene> first);
		void update();
		void finalize();

	public:
		~DxEngine() {}

		//====================================================================================================
		// メンバ関数

		inline int getWindowWidth() const { return window_width_; }
		inline int getWindowHeight() const { return window_height_; }
		inline std::shared_ptr<Scene> getNowScene() const { return now_scene_; }
		inline void changeScene(std::shared_ptr<Scene> next) { next_scene_ = next; }
		inline void exitGame() { is_playing_game_ = false; }
	};

}

#pragma once
#include "../library/t2klib.h"


namespace dxe {

	class SE;

	// SE一括管理クラス
	// SEの登録
	// SEの再生
	// SEの停止
	// SEのボリューム調整
	class SEManager final : public t2k::Singleton<SEManager> {
	private:
		// 基底クラスで生成するため
		friend class t2k::Singleton<SEManager>;
		// releaceAllを呼ぶため
		friend class UniPlusEngine;

		SEManager() {}

		//====================================================================================================
		// メンバ変数

		// SE一括管理用連想配列
		std::unordered_map<std::string, std::shared_ptr<SE>> se_map_;

		// SE全体のボリューム
		float master_volume_ = 1.0f;

		//====================================================================================================
		// メンバ関数

		// 自身が管理しているSEを解放する
		void releaceAll();

		//====================================================================================================
	public:
		~SEManager() {}

		//====================================================================================================
		// メンバ関数

		// SE全体のボリュームを取得
		inline float getMasterVolume() const { return master_volume_; }
		
		// SE全体のボリュームを設定
		void setMasterVolume(const float master_volume);

		// SEの登録
		std::shared_ptr<SE> registSE(const std::string& name, const std::string& file_path);

		// SEの取得
		std::shared_ptr<SE> getSE(const std::string& name);
		
		// SEの再生
		std::shared_ptr<SE> play(const std::string& name);

		// 再生中のSEの停止
		void stop();

		// SEの停止
		void stop(const std::string& name);

		// SEが再生中か
		bool isPlaying(const std::string& name);

		//====================================================================================================
	};

}

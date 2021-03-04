#pragma once
#include "../library/t2klib.h"


namespace dxe {

	class BGM;

	// BGM一括管理クラス
	// BGMの登録
	// BGMの再生
	// BGMの停止
	// BGMのボリューム調整
	class BGMManager final : public t2k::Singleton<BGMManager> {
	private:
		// 基底クラスで生成するため
		friend class t2k::Singleton<BGMManager>;
		// releaceAllを呼ぶため
		friend class UniPlusEngine;

		BGMManager() {}

		//====================================================================================================
		// メンバ変数

		// BGM一括管理用連想配列
		std::unordered_map<std::string, std::shared_ptr<BGM>> bgm_map_;

		// BGM全体のボリューム
		float master_volume_ = 1.0f;

		//====================================================================================================
		// メンバ関数

		// 自身が管理しているBGMを解放する
		void releaceAll();

		//====================================================================================================
	public:
		~BGMManager() {}

		//====================================================================================================
		// メンバ関数

		// BGM全体のボリュームを取得
		inline float getMasterVolume() const { return master_volume_; }

		// BGM全体のボリュームを取得
		void setMasterVolume(const float master_volume);

		// BGMの登録
		std::shared_ptr<BGM> registBGM(const std::string& name, const std::string& file_path);

		// BGMの取得
		std::shared_ptr<BGM> getBGM(const std::string& name);

		// BGMの再生
		// 第二引数に true を設定すると今再生中のBGMを止めずに重ねて再生する
		std::shared_ptr<BGM> play(const std::string& name, const bool is_duplicate = false);

		// 再生中のBGMの停止
		void stop();
		
		// BGMの停止
		void stop(const std::string& name);

		// BGMが再生中か
		bool isPlaying(const std::string& name);

		//====================================================================================================
	};

}

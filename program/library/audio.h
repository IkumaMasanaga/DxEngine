#pragma once
#include <string>
#include "shared_factory.h"
#include "shared_flyweight_map.h"


namespace t2k {

	class Audio final : public SharedFactory<Audio>, public SharedFlyweightMapInterface<std::string, Audio> {
	public:
		using SharedPtr = std::shared_ptr<Audio>;
		using WeakPtr = std::weak_ptr<Audio>;
	private:
		// fromFlyWeightLoader, finalizeを呼ぶため
		friend class SharedFlyweightMapInterface<std::string, Audio>;

		//====================================================================================================
		// メンバ変数
		int sound_ = 0;
		float total_time_ = 0.0f;
		std::string file_path_;

		//====================================================================================================
		// メンバ関数
		void finalize() final override;

		//====================================================================================================
		// static関数
		static Audio::SharedPtr fromFlyWeightLoader(const std::string& file_name, const std::string& file_path);

	public:
		Audio() {}
		~Audio() {}

		//====================================================================================================
		// メンバ関数
		inline int getSound() const { return sound_; }
		inline float getTotalTime() const { return total_time_; }

		//====================================================================================================
		// static関数
		static Audio::SharedPtr createFromFile(const std::string& file_path);
	};

}

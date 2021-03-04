#include "DxLib.h"
#include "../bgm_manager.h"
#include "bgm.h"


namespace dxe {

	void BGM::setVolume(const float volume) {
		volume_ = volume;
		ChangeVolumeSoundMem((int)(BGMManager::getInstance().getMasterVolume() * (volume_ * 255)), audio_->getSound());
	}

	BGM::SharedPtr BGM::create(const std::string& file_path) {
		BGM::SharedPtr ptr = Object::create<BGM>();
		ptr->audio_ = t2k::Audio::createFromFile(file_path);
		return ptr;
	}

}

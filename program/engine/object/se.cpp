#include "DxLib.h"
#include "../se_manager.h"
#include "se.h"


namespace dxe {

	void SE::setVolume(const float volume) {
		volume_ = volume;
		ChangeVolumeSoundMem((int)(SEManager::getInstance().getMasterVolume() * (volume_ * 255)), audio_->getSound());
	}

	SE::SharedPtr SE::create(const std::string& file_path) {
		SE::SharedPtr ptr = Object::create<SE>();
		ptr->audio_ = t2k::Audio::createFromFile(file_path);
		return ptr;
	}

}

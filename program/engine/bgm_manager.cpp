#include "DxLib.h"
#include "bgm_manager.h"
#include "object/bgm.h"


namespace dxe {

	void BGMManager::setMasterVolume(const float master_volume) {
		master_volume_ = master_volume;
		for (const auto& bgm : bgm_map_) {
			ChangeVolumeSoundMem((int)(master_volume_ * (bgm.second->getVolume() * 255)), bgm.second->getAudio()->getSound());
		}
	}

	std::shared_ptr<BGM> BGMManager::registBGM(const std::string& name, const std::string& file_path) {
		if (bgm_map_.find(name) != bgm_map_.end()) {
			warningMassage(("BGM–¼‚ªd•¡‚µ‚Ä‚¢‚Ü‚· : " + name).c_str());
			return nullptr;
		}
		std::shared_ptr<BGM> ptr = BGM::create(file_path);
		bgm_map_.try_emplace(name, ptr);
		return ptr;
	}

	std::shared_ptr<BGM> BGMManager::getBGM(const std::string& name) const {
		std::unordered_map<std::string, std::shared_ptr<BGM>>::const_iterator it = bgm_map_.find(name);
		if (it == bgm_map_.end()) {
			warningMassage(("BGM‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½ : " + name).c_str());
			return nullptr;
		}
		return it->second;
	}

	std::shared_ptr<BGM> BGMManager::play(const std::string& name, const bool is_duplicate) const {
		if (!is_duplicate) stop();
		std::unordered_map<std::string, std::shared_ptr<BGM>>::const_iterator it = bgm_map_.find(name);
		if (it == bgm_map_.end()) {
			warningMassage(("BGM‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½ : " + name).c_str());
			return nullptr;
		}
		ChangeVolumeSoundMem((int)(master_volume_ * (it->second->getVolume() * 255)), it->second->getAudio()->getSound());
		if (it->second->is_loop_) {
			PlaySoundMem(it->second->getAudio()->getSound(), DX_PLAYTYPE_LOOP);
		}
		else {
			PlaySoundMem(it->second->getAudio()->getSound(), DX_PLAYTYPE_BACK);
		}
		return it->second;
	}

	void BGMManager::stop() const {
		for (const auto& bgm : bgm_map_) {
			StopSoundMem(bgm.second->getAudio()->getSound());
		}
	}

	void BGMManager::stop(const std::string& name) const {
		std::unordered_map<std::string, std::shared_ptr<BGM>>::const_iterator it = bgm_map_.find(name);
		if (it == bgm_map_.end()) {
			warningMassage(("BGM‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½ : " + name).c_str());
			return;
		}
		StopSoundMem(it->second->getAudio()->getSound());
	}

	bool BGMManager::isPlaying(const std::string& name) const {
		std::unordered_map<std::string, std::shared_ptr<BGM>>::const_iterator it = bgm_map_.find(name);
		if (it == bgm_map_.end()) {
			warningMassage(("BGM‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½ : " + name).c_str());
			return false;
		}
		return CheckSoundMem(it->second->getAudio()->getSound());
	}

	void BGMManager::releaceAll() {
		std::unordered_map<std::string, std::shared_ptr<BGM>>::iterator it = bgm_map_.begin();
		while (it != bgm_map_.end()) {
			it = bgm_map_.erase(it);
		}
	}

}

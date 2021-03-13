#include "DxLib.h"
#include "se_manager.h"
#include "object/se.h"


namespace dxe {

	void SEManager::setMasterVolume(const float master_volume) {
		master_volume_ = master_volume;
		for (const auto& se : se_map_) {
			ChangeVolumeSoundMem((int)(master_volume_ * (se.second->getVolume() * 255)), se.second->getAudio()->getSound());
		}
	}

	std::shared_ptr<SE> SEManager::registSE(const std::string& name, const std::string& file_path) {
		if (se_map_.find(name) != se_map_.end()) {
			warningMassage(("SE–¼‚ªd•¡‚µ‚Ä‚¢‚Ü‚· : " + name).c_str());
			return nullptr;
		}
		std::shared_ptr<SE> ptr = SE::create(file_path);
		se_map_.try_emplace(name, ptr);
		return ptr;
	}

	std::shared_ptr<SE> SEManager::getSE(const std::string& name) const {
		std::unordered_map<std::string, std::shared_ptr<SE>>::const_iterator it = se_map_.find(name);
		if (it == se_map_.end()) {
			warningMassage(("SE‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½ : " + name).c_str());
			return nullptr;
		}
		return it->second;
	}

	std::shared_ptr<SE> SEManager::play(const std::string& name) const {
		std::unordered_map<std::string, std::shared_ptr<SE>>::const_iterator it = se_map_.find(name);
		if (it == se_map_.end()) {
			warningMassage(("SE‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½ : " + name).c_str());
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

	void SEManager::stop() const {
		for (const auto& se : se_map_) {
			StopSoundMem(se.second->getAudio()->getSound());
		}
	}

	void SEManager::stop(const std::string& name) const {
		std::unordered_map<std::string, std::shared_ptr<SE>>::const_iterator it = se_map_.find(name);
		if (it == se_map_.end()) {
			warningMassage(("SE‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½ : " + name).c_str());
			return;
		}
		StopSoundMem(it->second->getAudio()->getSound());
	}

	bool SEManager::isPlaying(const std::string& name) const {
		std::unordered_map<std::string, std::shared_ptr<SE>>::const_iterator it = se_map_.find(name);
		if (it == se_map_.end()) {
			warningMassage(("SE‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½ : " + name).c_str());
			return false;
		}
		return CheckSoundMem(it->second->getAudio()->getSound());
	}

	void SEManager::releaceAll() {
		std::unordered_map<std::string, std::shared_ptr<SE>>::iterator it = se_map_.begin();
		while (it != se_map_.end()) {
			it = se_map_.erase(it);
		}
	}

}

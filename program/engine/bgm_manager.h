#pragma once
#include "../library/t2klib.h"


namespace dxe {

	class BGM;

	// BGM�ꊇ�Ǘ��N���X
	// BGM�̓o�^
	// BGM�̍Đ�
	// BGM�̒�~
	// BGM�̃{�����[������
	class BGMManager final : public t2k::Singleton<BGMManager> {
	private:
		// ���N���X�Ő������邽��
		friend class t2k::Singleton<BGMManager>;
		// releaceAll���ĂԂ���
		friend class UniPlusEngine;

		BGMManager() {}

		//====================================================================================================
		// �����o�ϐ�

		// BGM�ꊇ�Ǘ��p�A�z�z��
		std::unordered_map<std::string, std::shared_ptr<BGM>> bgm_map_;

		// BGM�S�̂̃{�����[��
		float master_volume_ = 1.0f;

		//====================================================================================================
		// �����o�֐�

		// ���g���Ǘ����Ă���BGM���������
		void releaceAll();

		//====================================================================================================
	public:
		~BGMManager() {}

		//====================================================================================================
		// �����o�֐�

		// BGM�S�̂̃{�����[�����擾
		inline float getMasterVolume() const { return master_volume_; }

		// BGM�S�̂̃{�����[�����擾
		void setMasterVolume(const float master_volume);

		// BGM�̓o�^
		std::shared_ptr<BGM> registBGM(const std::string& name, const std::string& file_path);

		// BGM�̎擾
		std::shared_ptr<BGM> getBGM(const std::string& name);

		// BGM�̍Đ�
		// �������� true ��ݒ肷��ƍ��Đ�����BGM���~�߂��ɏd�˂čĐ�����
		std::shared_ptr<BGM> play(const std::string& name, const bool is_duplicate = false);

		// �Đ�����BGM�̒�~
		void stop();
		
		// BGM�̒�~
		void stop(const std::string& name);

		// BGM���Đ�����
		bool isPlaying(const std::string& name);

		//====================================================================================================
	};

}

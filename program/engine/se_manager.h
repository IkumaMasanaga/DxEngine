#pragma once
#include "../library/t2klib.h"


namespace dxe {

	class SE;

	// SE�ꊇ�Ǘ��N���X
	// SE�̓o�^
	// SE�̍Đ�
	// SE�̒�~
	// SE�̃{�����[������
	class SEManager final : public t2k::Singleton<SEManager> {
	private:
		// ���N���X�Ő������邽��
		friend class t2k::Singleton<SEManager>;
		// releaceAll���ĂԂ���
		friend class UniPlusEngine;

		SEManager() {}

		//====================================================================================================
		// �����o�ϐ�

		// SE�ꊇ�Ǘ��p�A�z�z��
		std::unordered_map<std::string, std::shared_ptr<SE>> se_map_;

		// SE�S�̂̃{�����[��
		float master_volume_ = 1.0f;

		//====================================================================================================
		// �����o�֐�

		// ���g���Ǘ����Ă���SE���������
		void releaceAll();

		//====================================================================================================
	public:
		~SEManager() {}

		//====================================================================================================
		// �����o�֐�

		// SE�S�̂̃{�����[�����擾
		inline float getMasterVolume() const { return master_volume_; }
		
		// SE�S�̂̃{�����[����ݒ�
		void setMasterVolume(const float master_volume);

		// SE�̓o�^
		std::shared_ptr<SE> registSE(const std::string& name, const std::string& file_path);

		// SE�̎擾
		std::shared_ptr<SE> getSE(const std::string& name);
		
		// SE�̍Đ�
		std::shared_ptr<SE> play(const std::string& name);

		// �Đ�����SE�̒�~
		void stop();

		// SE�̒�~
		void stop(const std::string& name);

		// SE���Đ�����
		bool isPlaying(const std::string& name);

		//====================================================================================================
	};

}

#include "DxLib.h"
#include "dx_main.h"
#include "../library/input.h"
#include "../library/time.h"
#include "../support/FrameRateController.h"
#include "../engine/dx_engine.h"
#include "../game/scene/sample_scene.h"


namespace sys {

	int DxMain::update() {

		// �E�B���h�E���[�h�ŋN��
		ChangeWindowMode(true);

		// �E�B���h�E�T�C�Y�ݒ�
		SetGraphMode(1024, 768, 32);

		// �E�B���h�E����A�N�e�B�u���ł��������~�߂Ȃ��悤�ɂ���
		SetAlwaysRunFlag(true);

		// �t���[�����[�g�ݒ�
		FpsSetting(60, 800);

		// DX���C�u��������������
		// �G���[���N�����璼���ɏI��
		if (DxLib_Init() == -1) return -1;

		// �`���𗠉�ʂɕύX
		SetDrawScreen(DX_SCREEN_BACK);

		// ���Ԑ���̏�����
		t2k::Time::initialize();

		// �L�[���͐���̏�����
		t2k::Input::initialize();

		// �G���W���̏�����
		dxe::DxEngine& engine = dxe::DxEngine::getInstance();
		engine.initialize(1024, 768, dxe::Scene::create<SampleScene>());

		// ���b�Z�[�W���[�v
		while (engine.is_playing_game_) {

			// ���Ԑ���X�V
			t2k::Time::update();

			// ���t���[���Ă�
			if (ProcessMessage() == -1) break;

			// �E�B���h�E����A�N�e�B�u�̏ꍇ�̓G���W���̍X�V���s��Ȃ�
			if (GetWindowActiveFlag() == false) continue;

			// ��ʂ��N���A
			ClearDrawScreen();

			// �L�[��Ԃ̍X�V
			t2k::Input::update();

			// �G���W���̍X�V
			engine.update();

			// �t���[�����[�g�R���g���[��
			FpsControll();

			// �o�b�N�o�b�t�@���t���b�v
			ScreenFlip();
			//SetWaitVSyncFlag(FALSE);
		}

		// �G���W���̏I������
		engine.finalize();
		dxe::DxEngine::destroy();

		// DX���C�u�����g�p�̏I������
		DxLib_End();

		// �\�t�g�̏I��
		return 0;

	}

}

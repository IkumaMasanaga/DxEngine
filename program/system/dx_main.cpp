#include "DxLib.h"
#include "dx_main.h"
#include "../library/input.h"
#include "../library/time.h"
#include "../support/FrameRateController.h"
#include "../engine/dx_engine.h"
#include "../game/scene/sample_scene.h"


namespace sys {

	int DxMain::update() {

		// ウィンドウモードで起動
		ChangeWindowMode(true);

		// ウィンドウサイズ設定
		SetGraphMode(1024, 768, 32);

		// ウィンドウが非アクティブ時でも処理を止めないようにする
		SetAlwaysRunFlag(true);

		// フレームレート設定
		FpsSetting(60, 800);

		// DXライブラリ初期化処理
		// エラーが起きたら直ちに終了
		if (DxLib_Init() == -1) return -1;

		// 描画先を裏画面に変更
		SetDrawScreen(DX_SCREEN_BACK);

		// 時間制御の初期化
		t2k::Time::initialize();

		// キー入力制御の初期化
		t2k::Input::initialize();

		// エンジンの初期化
		dxe::DxEngine& engine = dxe::DxEngine::getInstance();
		engine.initialize(1024, 768, dxe::Scene::create<SampleScene>());

		// メッセージループ
		while (engine.is_playing_game_) {

			// 時間制御更新
			t2k::Time::update();

			// 毎フレーム呼ぶ
			if (ProcessMessage() == -1) break;

			// ウィンドウが非アクティブの場合はエンジンの更新を行わない
			if (GetWindowActiveFlag() == false) continue;

			// 画面をクリア
			ClearDrawScreen();

			// キー状態の更新
			t2k::Input::update();

			// エンジンの更新
			engine.update();

			// フレームレートコントロール
			FpsControll();

			// バックバッファをフリップ
			ScreenFlip();
			//SetWaitVSyncFlag(FALSE);
		}

		// エンジンの終了処理
		engine.finalize();
		dxe::DxEngine::destroy();

		// DXライブラリ使用の終了処理
		DxLib_End();

		// ソフトの終了
		return 0;

	}

}

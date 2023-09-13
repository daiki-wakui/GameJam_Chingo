#include "DxLib.h"
#include "Keyboard.h"
#include "DebugManager.h"


#include "TitleScene.h"
#include "GameScene.h"
#include "ClearScene.h"

#include <memory>

enum MyEnum
{
	TITLE_SCENE,
	GAME_SCENE,
	CLEAR_SCENE
};

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "Chingo";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 900;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	int backImage = LoadGraph("GameAssets/Sprite/back.png");
	int groundImage = LoadGraph("GameAssets/Sprite/floor.png");
	
	
	// ゲームループで使う変数の宣言
	int titleBGM = LoadSoundMem("GameAssets/Sound/titleBGM.mp3");
	int gameBGM = LoadSoundMem("GameAssets/Sound/gameBGM.mp3");
	int resultBGM = LoadSoundMem("GameAssets/Sound/resultBGM.mp3");
	
	ChangeVolumeSoundMem(140, titleBGM);
	ChangeVolumeSoundMem(110, gameBGM);
	ChangeVolumeSoundMem(170, resultBGM);

	//keyboradクラスの生成
	Keyboard* keyboard_ = Keyboard::GetInstance();

	//シーンの生成と初期化
	std::unique_ptr<TitleScene> titleScene = std::make_unique<TitleScene>();
	std::unique_ptr<GameScene> gameScene = std::make_unique<GameScene>();
	std::unique_ptr<ClearScene> clearScene = std::make_unique<ClearScene>();
	DebugManager* debug = DebugManager::GetInstance();
	
	titleScene->Initialize();
	gameScene->Initialize();
	clearScene->Initialize();
	debug->Initialize();
	
	int scene = TITLE_SCENE;

	// ゲームループ
	while (true) {

		keyboard_->Update();

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		if (scene == TITLE_SCENE) {
			if (CheckSoundMem(titleBGM) == 0) {
				PlaySoundMem(titleBGM, DX_PLAYTYPE_LOOP, true);
			}
			
			titleScene->Update();

			if (titleScene->GetIsSceneChange()) {
				StopSoundMem(titleBGM);
				gameScene->Initialize();
				scene = GAME_SCENE;
			}
		}
		else if (scene == GAME_SCENE) {
			
			gameScene->Update();
			debug->Update();
	
			if (CheckSoundMem(gameBGM) == 0 && !gameScene->GetIstutorial()) {
				
				PlaySoundMem(gameBGM, DX_PLAYTYPE_LOOP, true);
			}
			else {
				if (CheckSoundMem(titleBGM) == 0) {
					PlaySoundMem(titleBGM, DX_PLAYTYPE_BACK, true);
				}
			}

			if (!gameScene->GetIstutorial()) {
				StopSoundMem(titleBGM);
			}

			if (!EnemyManager::GetInstance()->GetIsWhaleAlive()) {
				gameScene->SetIsSceneChange(true);
			}

			if (gameScene->GetIsSceneChange()) {
				StopSoundMem(gameBGM);
				clearScene->Initialize();
				scene = CLEAR_SCENE;
			}
		}
		else if (scene == CLEAR_SCENE) {
			if (CheckSoundMem(resultBGM) == 0) {
				PlaySoundMem(resultBGM, DX_PLAYTYPE_LOOP, true);
			}
			
			clearScene->Update();

			if (clearScene->GetIsChange()) {
				StopSoundMem(resultBGM);
				gameScene->Initialize();
				titleScene->Initialize();
				scene = TITLE_SCENE;
			}
		}

		// 描画処理
		if (scene == TITLE_SCENE) {
			DrawGraph(-40, -180, backImage, true);
			
			titleScene->Draw();
		}

		if (scene == GAME_SCENE) {
			
			gameScene->Draw();
			debug->Draw();
		}

		if (scene == CLEAR_SCENE) {
			clearScene->Draw();
		}

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}

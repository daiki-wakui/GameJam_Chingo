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

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "Chingo";

// �E�B���h�E����
const int WIN_WIDTH = 1280;

// �E�B���h�E�c��
const int WIN_HEIGHT = 900;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int backImage = LoadGraph("GameAssets/Sprite/back.png");
	int groundImage = LoadGraph("GameAssets/Sprite/floor.png");
	
	
	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	int titleBGM = LoadSoundMem("GameAssets/Sound/titleBGM.mp3");
	int gameBGM = LoadSoundMem("GameAssets/Sound/gameBGM.mp3");
	int resultBGM = LoadSoundMem("GameAssets/Sound/resultBGM.mp3");
	
	ChangeVolumeSoundMem(140, titleBGM);
	ChangeVolumeSoundMem(110, gameBGM);
	ChangeVolumeSoundMem(170, resultBGM);

	//keyborad�N���X�̐���
	Keyboard* keyboard_ = Keyboard::GetInstance();

	//�V�[���̐����Ə�����
	std::unique_ptr<TitleScene> titleScene = std::make_unique<TitleScene>();
	std::unique_ptr<GameScene> gameScene = std::make_unique<GameScene>();
	std::unique_ptr<ClearScene> clearScene = std::make_unique<ClearScene>();
	DebugManager* debug = DebugManager::GetInstance();
	
	titleScene->Initialize();
	gameScene->Initialize();
	clearScene->Initialize();
	debug->Initialize();
	
	int scene = TITLE_SCENE;

	// �Q�[�����[�v
	while (true) {

		keyboard_->Update();

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
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

		// �`�揈��
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

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}

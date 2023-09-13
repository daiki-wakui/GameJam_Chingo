#pragma once
#include "DxLib.h"
#include <memory>
#include "Shake.h"
#include "Keyboard.h"
#include "EnemyManager.h"
#include "Vector2.h"

class GameScene
{
private:

	int backBottomImage = LoadGraph("GameAssets/Sprite/background_bottom.png");
	int backMiddleImage = LoadGraph("GameAssets/Sprite/background_middle.png");
	int backTopImage = LoadGraph("GameAssets/Sprite/background_top.png");
	int blueImage = LoadGraph("GameAssets/Sprite/blue.png");
	int vignetImage = LoadGraph("GameAssets/Sprite/vignette.png");
	int moleImage = LoadGraph("GameAssets/Sprite/mole2.png");
	int endImage = LoadGraph("GameAssets/Sprite/UI/end.png");
	int RkeyImage = LoadGraph("GameAssets/Sprite/UI/RkeyReset.png");
	int mouseLeftImage = LoadGraph("GameAssets/Sprite/mouseUI2.png");

	int fukidasiImage = LoadGraph("GameAssets/Sprite/fukidasi.png");

	int tutorialImage[5];

	float fukidasiPosY = 650;

	int anagoImage[2];

	int endSE = LoadSoundMem("GameAssets/Sound/endSE.mp3");
	bool isSE = false;

	int UI_Select = LoadSoundMem("GameAssets/Sound/SFX_UI_Select.wav");

	EnemyManager* enemyM = EnemyManager::GetInstance();


	std::unique_ptr<Shake> shake = std::make_unique<Shake>();

	Keyboard* keyboard_ = Keyboard::GetInstance();

	//レベルアップ時の花びら演出の変数
	Vector2 effectPosLeft_[30];
	Vector2 effectPosRight_[30];
	Vector2 effectPower_[30];
	int effectNumber_ = 30;
	bool isEffectSet_ = false;
	int effectColorChange_ = 0;

	Vector2 startAnago[4];
	Vector2 endAnago[4];
	Vector2 AnagoPos[4];
	int frame_[5];
	bool isChangeStart = false;
	bool isChange = false;

	bool isReset = false;

	Vector2 endSize;

	int mouseX_, mouseY_;
	int isTutorialPhase;
	bool isTutorial;

	int Mouse;
	int oldMouse;
public:
	bool GetIstutorial() { return isTutorial; }

	bool GetIsSceneChange() { return isChange; }

	bool GetIsChangeStart() { return isChangeStart; }
	void SetIsSceneChange(bool change) { isChangeStart = change; }
	void SetIsReset(bool reset) { isReset = reset; }


	void LevelUpEffectSet();
	void LevelUpEffect();

	void Initialize();
	void Update();
	void Draw();

	bool MouseTriggerLeft();
};


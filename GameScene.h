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

public:
	void LevelUpEffectSet();
	void LevelUpEffect();

	void Initialize();
	void Update();
	void Draw();
};


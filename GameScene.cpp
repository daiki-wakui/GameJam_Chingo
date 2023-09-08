#include "GameScene.h"
#include "Player.h"
#include "ColliderManager.h"
#include "LevelManager.h"
#include "exBody/ExBodyManager.h"
#include <stdlib.h>
#include <time.h>

void GameScene::Initialize()
{
	Player::GetInstance()->Initialize();
	LevelManager::GetInstance()->Initialize();
	enemyM->Initialize();

	//初期値セット
	for (int i = 0; i < effectNumber_; i++)
	{
		effectPosLeft_[i].x = -60;
		effectPosLeft_[i].y = 0;
		effectPosRight_[i].x = -60;
		effectPosRight_[i].y = 0;
	}
}

void GameScene::Update()
{
	enemyM->Update();


	if (ExBodyManager::GetInstance()->GetIsSelect()) {
		Player::GetInstance()->Update();
		ExBodyManager::GetInstance()->Update();

		if (!isEffectSet_) {
			LevelUpEffectSet();
			isEffectSet_ = true;
		}

		LevelUpEffect();

		return;
	}
	isEffectSet_ = false;

	Player::GetInstance()->Update();
	ColliderManager::GetInstance()->Update();
	LevelManager::GetInstance()->Update();

	//playerが地面に来た時
	if (Player::GetInstance()->GetIsShakeing()) {
		srand(time(NULL));
		shake->max = 21;
		shake->min = 10;
		shake->isShakeing = 1;
		Player::GetInstance()->SetIsShakeing(false);
		//シェイク開始
	}

	//シェイクの処理
	shake->Effect();

	LevelUpEffect();
}

void GameScene::Draw()
{
	//地面
	DrawGraph(0, -180 + shake->randY, backImage, true);
	enemyM->Draw();
	Player::GetInstance()->Draw();
	LevelManager::GetInstance()->Draw();

	for (int i = 0; i < effectNumber_; i++) {
		//for文が偶数のとき赤
		if (effectColorChange_ % 2 == 0) {
			DrawBox((effectPosLeft_[i].x - 7), (effectPosLeft_[i].y - 7), (effectPosLeft_[i].x + 7), (effectPosLeft_[i].y + 7), GetColor(255, 50, 50), true);
			DrawBox((effectPosRight_[i].x - 7), (effectPosRight_[i].y - 7), (effectPosRight_[i].x + 7), (effectPosRight_[i].y + 7), GetColor(255, 50, 50), true);
		}
		//for文が3の倍数のとき緑
		else if (effectColorChange_ % 3 == 0) {
			DrawBox((effectPosLeft_[i].x - 7), (effectPosLeft_[i].y - 7), (effectPosLeft_[i].x + 7), (effectPosLeft_[i].y + 7), GetColor(50, 255, 50), true);
			DrawBox((effectPosRight_[i].x - 7), (effectPosRight_[i].y - 7), (effectPosRight_[i].x + 7), (effectPosRight_[i].y + 7), GetColor(50, 255, 50), true);
		}
		//それ以外青
		else {
			DrawBox((effectPosLeft_[i].x - 7), (effectPosLeft_[i].y - 5), (effectPosLeft_[i].x + 7), (effectPosLeft_[i].y + 7), GetColor(50, 50, 255), true);
			DrawBox((effectPosRight_[i].x - 7), (effectPosRight_[i].y - 5), (effectPosRight_[i].x + 7), (effectPosRight_[i].y + 7), GetColor(50, 50, 255), true);
		}
		effectColorChange_++;
	}

	DrawFormatString(0, 0, GetColor(255, 255, 255), "game");
}

void GameScene::LevelUpEffectSet()
{
	//初期値セット
	for (int i = 0; i < effectNumber_; i++)
	{
		effectPosLeft_[i].x = 0;
		effectPosLeft_[i].y = 900;
		effectPosRight_[i].x = 1280;
		effectPosRight_[i].y = 900;

		effectPower_[i].x = rand() % 7 + 1;
		effectPower_[i].y = rand() % 30 + 15;
	}
}

void GameScene::LevelUpEffect()
{
	//花びらの更新処理
	for (int i = 0; i < effectNumber_; i++) {
		effectPower_[i].y -= 0.75f;
		effectPosLeft_[i].x += effectPower_[i].x;
		effectPosLeft_[i].y -= effectPower_[i].y;
		effectPosRight_[i].x -= effectPower_[i].x;
		effectPosRight_[i].y -= effectPower_[i].y;
	}
}
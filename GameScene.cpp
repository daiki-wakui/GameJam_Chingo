#include "GameScene.h"
#include "Player.h"
#include "ColliderManager.h"
#include "LevelManager.h"
#include "exBody/ExBodyManager.h"
#include <stdlib.h>
#include <time.h>
#include "ScrollManager.h"
#include "Keyboard.h"
#include "BulletManager.h"
#include "Easing.h"
#include "EnemyManager.h"

void GameScene::Initialize()
{
	Player::GetInstance()->Initialize();
	LevelManager::GetInstance()->Initialize();
	enemyM->Initialize();
	BulletManager::GetInstance()->Initialize();

	//初期値セット
	for (int i = 0; i < effectNumber_; i++)
	{
		effectPosLeft_[i].x = -60;
		effectPosLeft_[i].y = 0;
		effectPosRight_[i].x = -60;
		effectPosRight_[i].y = 0;
	}
	shake->Reset();

	anagoImage[0] = LoadGraph("GameAssets/Sprite/anago1.png");
	anagoImage[1] = LoadGraph("GameAssets/Sprite/anago2.png");

	startAnago[0] = { -110,-250 };
	startAnago[1] = { -110 + 330,-250 };
	startAnago[2] = { -110 + 330 * 2,-250 };
	startAnago[3] = { -110 + 330 * 3,-250 };

	AnagoPos[0] = startAnago[0];
	AnagoPos[1] = startAnago[1];
	AnagoPos[2] = startAnago[2];
	AnagoPos[3] = startAnago[3];

	endAnago[0] = { -110,1400 };
	endAnago[1] = { -110 + 330,1200 };
	endAnago[2] = { -110 + 330 * 2,1000 };
	endAnago[3] = { -110 + 330 * 3,1500 };
	frame_[0] = 0;
	frame_[1] = 0;
	isChange = false;
	isChangeStart = false;
}

void GameScene::Update()
{
	frame_[0]++;

	if (EnemyManager::GetInstance()->GetIsWhaleAlive()) {
		AnagoPos[0] = AnagoPos[0].lerp(startAnago[0], endAnago[0], Easing::EaseInCubic(frame_[0], 60));
		AnagoPos[1] = AnagoPos[1].lerp(startAnago[1], endAnago[1], Easing::EaseInCubic(frame_[0], 60));
		AnagoPos[2] = AnagoPos[2].lerp(startAnago[2], endAnago[2], Easing::EaseInCubic(frame_[0], 60));
		AnagoPos[3] = AnagoPos[3].lerp(startAnago[3], endAnago[3], Easing::EaseInCubic(frame_[0], 60));
	}
	else if (isChangeStart) {
		frame_[1]++;
		AnagoPos[0] = AnagoPos[0].lerp(endAnago[0], startAnago[0], Easing::EaseOutCubic(frame_[1], 60));
		AnagoPos[1] = AnagoPos[1].lerp(endAnago[1], startAnago[1], Easing::EaseOutCubic(frame_[1], 60));
		AnagoPos[2] = AnagoPos[2].lerp(endAnago[2], startAnago[2], Easing::EaseOutCubic(frame_[1], 60));
		AnagoPos[3] = AnagoPos[3].lerp(endAnago[3], startAnago[3], Easing::EaseOutCubic(frame_[1], 60));

	}

	if (frame_[1] >= 60) {
		isChange = true;
	}
	

	if (Keyboard::GetInstance()->KeyTriggerPush(KEY_INPUT_R)) {
		Initialize();
	}

	enemyM->Update();
	BulletManager::GetInstance()->Update();

	if (ExBodyManager::GetInstance()->GetIsSelect()) {
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
	DrawGraph(-40, -180 + shake->randY + ScrollManager::GetInstance()->GetScroll(), backBottomImage, true);
	DrawGraph(0, -1080 + ScrollManager::GetInstance()->GetScroll(), backMiddleImage, true);
	DrawGraph(0, -1080 * 2 + ScrollManager::GetInstance()->GetScroll(), backMiddleImage, true);
	DrawGraph(0, -1080 * 3 + ScrollManager::GetInstance()->GetScroll(), backMiddleImage, true);
	DrawGraph(0, -1080 * 4 + ScrollManager::GetInstance()->GetScroll(), backMiddleImage, true);
	DrawGraph(0, -1080 * 5 + ScrollManager::GetInstance()->GetScroll(), backMiddleImage, true);
	DrawGraph(0, -1080 * 6 + ScrollManager::GetInstance()->GetScroll(), backMiddleImage, true);
	DrawGraph(0, -1080 * 7 + ScrollManager::GetInstance()->GetScroll(), backMiddleImage, true);
	DrawGraph(0, -1080 * 8 + ScrollManager::GetInstance()->GetScroll(), backTopImage, true);
	DrawGraph(0, 0, blueImage, true);
	DrawGraph(0, 0, vignetImage, true);
	enemyM->Draw();
	Player::GetInstance()->Draw();

	

	DrawGraph(555, 700 + shake->randY + ScrollManager::GetInstance()->GetScroll(), moleImage, true);

	BulletManager::GetInstance()->Draw();
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

	DrawGraph(AnagoPos[0].x, AnagoPos[0].y, anagoImage[0], true);
	DrawGraph(AnagoPos[1].x, AnagoPos[1].y, anagoImage[1], true);
	DrawGraph(AnagoPos[2].x, AnagoPos[2].y, anagoImage[0], true);
	DrawGraph(AnagoPos[3].x, AnagoPos[3].y, anagoImage[1], true);

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
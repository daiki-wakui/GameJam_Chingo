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
#include "EffectManager.h"

void GameScene::Initialize()
{
	Player::GetInstance()->Initialize();
	LevelManager::GetInstance()->Initialize();
	enemyM->Initialize();
	BulletManager::GetInstance()->Initialize();
	EffectManager::GetInstance()->Initialize();

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
	frame_[2] = 0;
	frame_[3] = 0;
	frame_[4] = 0;
	isChange = false;
	isChangeStart = false;
	endSize.x = 5;

	ChangeVolumeSoundMem(100, endSE);

	fukidasiPosY = 650;

	tutorialImage[0] = LoadGraph("GameAssets/Sprite/UI/tuto1.png");
	tutorialImage[1] = LoadGraph("GameAssets/Sprite/UI/tuto2.png");
	tutorialImage[2] = LoadGraph("GameAssets/Sprite/UI/tuto3.png");
	tutorialImage[3] = LoadGraph("GameAssets/Sprite/UI/tuto4.png");
	tutorialImage[4] = LoadGraph("GameAssets/Sprite/UI/tuto5.png");

	ChangeVolumeSoundMem(140, UI_Select);
}

void GameScene::Update()
{
	frame_[0]++;

	//マウス入力情報
	oldMouse = Mouse;
	Mouse = GetMouseInput();

	//マウスの場所取得
	GetMousePoint(&mouseX_, &mouseY_);

	fukidasiPosY = 0.15f * sinf(2 * 3.14f * frame_[0] / 200) + fukidasiPosY;

	if (isTutorialPhase == 0) {
		isTutorial = true;

		if (MouseTriggerLeft() && frame_[0] >= 140) {
			isTutorialPhase++;
			PlaySoundMem(UI_Select, DX_PLAYTYPE_BACK, true);

		}
	}
	else if (isTutorialPhase == 1) {
		if (MouseTriggerLeft()) {
			isTutorialPhase++;
			PlaySoundMem(UI_Select, DX_PLAYTYPE_BACK, true);

		}
	}
	else if (isTutorialPhase == 2) {
		if (MouseTriggerLeft()) {
			isTutorialPhase++;
			PlaySoundMem(UI_Select, DX_PLAYTYPE_BACK, true);

		}
	}
	else if (isTutorialPhase == 3) {
		if (MouseTriggerLeft()) {
			isTutorialPhase++;
			PlaySoundMem(UI_Select, DX_PLAYTYPE_BACK, true);

		}
	}
	else if (isTutorialPhase == 4) {
		if (MouseTriggerLeft()) {
			isTutorialPhase++;
			PlaySoundMem(UI_Select, DX_PLAYTYPE_BACK, true);

		}
		
	}
	else if (isTutorialPhase == 5) {
		isTutorial = false;
	}

	endSize = endSize.lerp(Vector2{ 15,0 }, Vector2{ 1.5,0 }, Easing::EaseOutBack(frame_[1], 10));

	if (EnemyManager::GetInstance()->GetIsWhaleAlive() && !isReset) {
		AnagoPos[0] = AnagoPos[0].lerp(startAnago[0], endAnago[0], Easing::EaseInCubic(frame_[0], 110));
		AnagoPos[1] = AnagoPos[1].lerp(startAnago[1], endAnago[1], Easing::EaseInCubic(frame_[0], 110));
		AnagoPos[2] = AnagoPos[2].lerp(startAnago[2], endAnago[2], Easing::EaseInCubic(frame_[0], 110));
		AnagoPos[3] = AnagoPos[3].lerp(startAnago[3], endAnago[3], Easing::EaseInCubic(frame_[0], 110));
	}
	else if (isChangeStart) {
		frame_[1]++;
		if (!isSE) {
			PlaySoundMem(endSE, DX_PLAYTYPE_BACK, true);
			isSE = true;
		}
		
	}

	if (frame_[1] >= 60) {
		frame_[4]++;

		AnagoPos[0] = AnagoPos[0].lerp(endAnago[0], startAnago[0], Easing::EaseOutCubic(frame_[4], 60));
		AnagoPos[1] = AnagoPos[1].lerp(endAnago[1], startAnago[1], Easing::EaseOutCubic(frame_[4], 60));
		AnagoPos[2] = AnagoPos[2].lerp(endAnago[2], startAnago[2], Easing::EaseOutCubic(frame_[4], 60));
		AnagoPos[3] = AnagoPos[3].lerp(endAnago[3], startAnago[3], Easing::EaseOutCubic(frame_[4], 60));
	}

	if (frame_[1] >= 150) {
		//Player::GetInstance()->StopSE();
		isChange = true;
		isSE = false;
	}
	
	if (isReset) {
		frame_[2]++;
		AnagoPos[0] = AnagoPos[0].lerp(endAnago[0], startAnago[0], Easing::EaseOutCubic(frame_[2], 30));
		AnagoPos[1] = AnagoPos[1].lerp(endAnago[1], startAnago[1], Easing::EaseOutCubic(frame_[2], 30));
		AnagoPos[2] = AnagoPos[2].lerp(endAnago[2], startAnago[2], Easing::EaseOutCubic(frame_[2], 30));
		AnagoPos[3] = AnagoPos[3].lerp(endAnago[3], startAnago[3], Easing::EaseOutCubic(frame_[2], 30));


		if (frame_[2] >= 30) {
			frame_[3]++;
			AnagoPos[0] = AnagoPos[0].lerp(startAnago[0], endAnago[0], Easing::EaseInCubic(frame_[3], 70));
			AnagoPos[1] = AnagoPos[1].lerp(startAnago[1], endAnago[1], Easing::EaseInCubic(frame_[3], 70));
			AnagoPos[2] = AnagoPos[2].lerp(startAnago[2], endAnago[2], Easing::EaseInCubic(frame_[3], 70));
			AnagoPos[3] = AnagoPos[3].lerp(startAnago[3], endAnago[3], Easing::EaseInCubic(frame_[3], 70));

		}

		if (frame_[3] >= 80) {
			isReset = false;
		}
	}

	if (Keyboard::GetInstance()->KeyTriggerPush(KEY_INPUT_R) && !isTutorial && !isReset) {
		Initialize();

		AnagoPos[0] = endAnago[0];
		AnagoPos[1] = endAnago[1];
		AnagoPos[2] = endAnago[2];
		AnagoPos[3] = endAnago[3];
		isReset = true;

	}

	enemyM->Update();
	BulletManager::GetInstance()->Update();
	EffectManager::GetInstance()->Update();

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

	if (!isTutorial) {
		Player::GetInstance()->Update();
	}

	
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

	Player::GetInstance()->SetIsGamescene(true);

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

	
	BulletManager::GetInstance()->Draw();


	Player::GetInstance()->Draw();
	DrawGraph(555, 700 + shake->randY + ScrollManager::GetInstance()->GetScroll(), moleImage, true);

	EffectManager::GetInstance()->Draw();
	DrawRotaGraph(90, 770, 0.3, 0, RkeyImage, true);
	
	ExBodyManager::GetInstance()->Draw();
	ExBodyManager::GetInstance()->LvUpDraw();

	if (!ExBodyManager::GetInstance()->GetIsSelect()) {
		LevelManager::GetInstance()->Draw();
	}

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

	if (isChangeStart) {
		DrawRotaGraph(1280/2, 900/2, endSize.x,0, endImage, true);
	}

	if (isTutorial) {
		DrawRotaGraph(1280 / 2 + 160, fukidasiPosY, 1.2, 0, fukidasiImage, true);
		if (isTutorialPhase != 4) {
			DrawRotaGraph(1280 / 2 + 165, fukidasiPosY, 0.6, 0, tutorialImage[isTutorialPhase], true);
		}
		else{
			DrawRotaGraph(1280 / 2 + 180, fukidasiPosY, 1, 0, tutorialImage[isTutorialPhase], true);
		}

		DrawRotaGraph(1280 / 2 + 280, fukidasiPosY+75, 0.2, 0, mouseLeftImage, true);
	}
	
	DrawGraph(AnagoPos[0].x, AnagoPos[0].y, anagoImage[0], true);
	DrawGraph(AnagoPos[1].x, AnagoPos[1].y, anagoImage[1], true);
	DrawGraph(AnagoPos[2].x, AnagoPos[2].y, anagoImage[0], true);
	DrawGraph(AnagoPos[3].x, AnagoPos[3].y, anagoImage[1], true);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "t %d , %d", isTutorialPhase);
}

bool GameScene::MouseTriggerLeft()
{
	if (Mouse & MOUSE_INPUT_LEFT && oldMouse != MOUSE_INPUT_LEFT) {
		return true;
	}
	return false;
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
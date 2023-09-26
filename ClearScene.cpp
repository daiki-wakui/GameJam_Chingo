#include "ClearScene.h"
#include "exBody/ExBodyManager.h"
#include "LevelManager.h"
#include "MathManager.h"
#include "Player.h"
#include "Easing.h"

void ClearScene::Initialize()
{
	//体UI
	ResultUI[1] = LoadGraph("GameAssets/Sprite/UI/masuru.png");
	ResultUI[2] = LoadGraph("GameAssets/Sprite/UI/maji.png");
	ResultUI[3] = LoadGraph("GameAssets/Sprite/UI/jet.png");
	ResultUI[4] = LoadGraph("GameAssets/Sprite/UI/gameing.png");
	ResultUI[5] = LoadGraph("GameAssets/Sprite/UI/syak.png");
	ResultUI[6] = LoadGraph("GameAssets/Sprite/UI/sakaban.png");


	ResultUI[11] = LoadGraph("GameAssets/Sprite/UI/mukimuki.png");
	ResultUI[12] = LoadGraph("GameAssets/Sprite/UI/majisya.png");
	ResultUI[13] = LoadGraph("GameAssets/Sprite/UI/jett.png");
	ResultUI[14] = LoadGraph("GameAssets/Sprite/UI/gameimgg.png");
	ResultUI[15] = LoadGraph("GameAssets/Sprite/UI/syake.png");
	ResultUI[16] = LoadGraph("GameAssets/Sprite/UI/sukabann.png");

	ResultUI[17] = LoadGraph("GameAssets/Sprite/UI/chinnanago.png");
	ResultUI[18] = LoadGraph("GameAssets/Sprite/UI/kannsei.png");



	ResultUI[7] = LoadGraph("GameAssets/Sprite/UI/anagoLv.png");
	ResultUI[8] = LoadGraph("GameAssets/Sprite/UI/body.png");
	ResultUI[9] = LoadGraph("GameAssets/Sprite/level3.png");
	ResultUI[19] = LoadGraph("GameAssets/Sprite/UI/result.png");

	levelImage[0] = LoadGraph("GameAssets/Sprite/level1.png");
	levelImage[1] = LoadGraph("GameAssets/Sprite/level2.png");
	levelImage[2] = LoadGraph("GameAssets/Sprite/level3.png");
	levelImage[3] = LoadGraph("GameAssets/Sprite/levelMax.png");

	frame = 0;
	titleAnimeTimer = 0;
	rot = 0;

	
	tempPos[0] = { 430,240 };
	tempPos[1] = { 430,350 };
	tempPos[2] = { 430,490 };
	tempPos[3] = { 430,590 };

	BodyUIStartPos[0] = { 430,900 };

	
	BodyUIEndPos[0] = { 430,240 };
	BodyUIEndPos[1] = { 430,350 };
	BodyUIEndPos[2] = { 430,450 };
	BodyUIEndPos[3] = { 430,550 };
	UIFrame[0] = 0;
	UIFrame[1] = 0;
	UIFrame[2] = 0;
	UIFrame[3] = 0;

	feadAlpha = 0;
	alpha_ = 255;
	isSE_ = false;
	isChangeStart = false;
	isChange = false;
	ChangeVolumeSoundMem(170, resultBGM);


	ChangeVolumeSoundMem(180, kansei1);
	ChangeVolumeSoundMem(180, kansei2);

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
}


void ClearScene::Update()
{

	//マウスの場所取得
	GetMousePoint(&mouseX_, &mouseY_);


	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && frame >= 440) {
		//isChange = true;
		//StopSoundMem(resultBGM);
		isChangeStart = true;
	}
	if (isChangeStart) {
		feadAlpha += 3;
		feadAlpha = min(feadAlpha, 255);
	}

	if (feadAlpha >= 255) {
		isChange = true;
	}


	Player::GetInstance()->SetIsGamescene(false);

	AnagoPos[0] = AnagoPos[0].lerp(startAnago[0], endAnago[0], Easing::EaseInCubic(frame, 10));
	AnagoPos[1] = AnagoPos[1].lerp(startAnago[1], endAnago[1], Easing::EaseInCubic(frame, 10));
	AnagoPos[2] = AnagoPos[2].lerp(startAnago[2], endAnago[2], Easing::EaseInCubic(frame, 10));
	AnagoPos[3] = AnagoPos[3].lerp(startAnago[3], endAnago[3], Easing::EaseInCubic(frame, 10));

	Player::GetInstance()->ReSetBody();
	Player::GetInstance()->ResultUpdate();
	titleAnimeTimer++;
	frame++;

	rot++;

	UIFrame[0]++;
	if (frame >= 92) {
		UIFrame[1]++;
	}
	if (frame >= 92 * 2) {
		UIFrame[2]++;
	}
	if (frame >= 92 * 3) {
		UIFrame[3]++;
	}

	if (frame >= 330) {
		alpha_-=25;
		alpha_ = max(alpha_, 0);
	}

	if (frame >= 370) {
		if (!isSE_) {
			PlaySoundMem(kansei1, DX_PLAYTYPE_BACK, true);
			PlaySoundMem(kansei2, DX_PLAYTYPE_BACK, true);
			isSE_ = true;
		}
	}
	
	
	if (titleAnimeTimer >= titleAnimeMaxTimer) {
		titleAnimeTimer = 0;
	}

	mouseLeftSize = mouseLeftSize.lerp(Vector2{ 0.4,0 }, Vector2{ 0.35,0 }, Easing::EaseOutCubic(titleAnimeTimer, titleAnimeMaxTimer));
	titleSize = titleSize.lerp(Vector2{ 1.0,0 }, Vector2{ 0.7,0 }, Easing::EaseOutCubic(titleAnimeTimer, titleAnimeMaxTimer));
	BodyUISize = BodyUISize.lerp(Vector2{ 1.3,0 }, Vector2{ 1.0,0 }, Easing::EaseOutCubic(titleAnimeTimer, titleAnimeMaxTimer));

	tempPos[0] = tempPos[0].lerp(BodyUIStartPos[0], BodyUIEndPos[0], Easing::EaseOutCubic(UIFrame[0], 60));
	tempPos[1] = tempPos[1].lerp(BodyUIStartPos[0], BodyUIEndPos[1], Easing::EaseOutCubic(UIFrame[1], 60));
	tempPos[2] = tempPos[2].lerp(BodyUIStartPos[0], BodyUIEndPos[2], Easing::EaseOutCubic(UIFrame[2], 60));
	tempPos[3] = tempPos[3].lerp(BodyUIStartPos[0], BodyUIEndPos[3], Easing::EaseOutCubic(UIFrame[3], 60));
}

void ClearScene::Draw()
{

	ExBodyManager* exM = ExBodyManager::GetInstance();
	LevelManager* lvM = LevelManager::GetInstance();
	
	//背景
	DrawGraph(0, -180, backBottomImage, true);
	DrawGraph(0, 0, blueImage, true);
	DrawGraph(0, 0, vignetImage, true);

	Player::GetInstance()->Draw();
	ExBodyManager::GetInstance()->Draw();

	//集中線
	if (frame >= 370) {
		DrawRotaGraph(1280 / 2, 900/2, 1, rot, targetImage, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);

	//結果発表
	DrawRotaGraph(1280 / 2, 80, titleSize.x, 0, ResultUI[19], true);

	//あなご
	DrawRotaGraph(150, 250, titleSize.x, 0, ResultUI[7], true);
	//からだ
	DrawRotaGraph(150, 350, titleSize.x, 0, ResultUI[8], true);

	//Lv
	DrawRotaGraph(tempPos[0].x, tempPos[0].y, BodyUISize.x, 0, levelImage[lvM->GetLevel() - 1], true);
	//胴体
	if (frame >= 92 * 1) {
		DrawRotaGraph(tempPos[1].x, tempPos[1].y, BodyUISize.x, 0, ResultUI[exM->GetBodyType(0)], true);
	}
	if (frame >= 92 * 2) {
		DrawRotaGraph(tempPos[2].x, tempPos[2].y, BodyUISize.x, 0, ResultUI[exM->GetBodyType(1)], true);
	}
	if (frame >= 92 * 3) {
		DrawRotaGraph(tempPos[3].x, tempPos[3].y, BodyUISize.x, 0, ResultUI[exM->GetBodyType(2)], true);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	if (frame >= 370) {
		DrawRotaGraph(320, 270, 1, 0, ResultUI[exM->GetBodyType(0) + 10], true);
		DrawRotaGraph(650, 380, 1, 0, ResultUI[exM->GetBodyType(1) + 10], true);
		DrawRotaGraph(980, 490, 1, 0, ResultUI[exM->GetBodyType(2) + 10], true);
		DrawRotaGraph(800, 670, 1.4, 0.1, ResultUI[17], true);
		DrawRotaGraph(1280 / 2, 105, 0.7, 0, ResultUI[18], true);
	}

	if (frame >= 440) {
		DrawRotaGraph(1180, 800, mouseLeftSize.x, 0, mouseLeftImage, true);
	}

	DrawGraph(AnagoPos[0].x, AnagoPos[0].y, anagoImage[0], true);
	DrawGraph(AnagoPos[1].x, AnagoPos[1].y, anagoImage[1], true);
	DrawGraph(AnagoPos[2].x, AnagoPos[2].y, anagoImage[0], true);
	DrawGraph(AnagoPos[3].x, AnagoPos[3].y, anagoImage[1], true);

	if (isChangeStart) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, feadAlpha);
		DrawBox(0, 0, 1280, 900, GetColor(255, 250, 220), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

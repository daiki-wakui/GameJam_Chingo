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

	ResultUI[7] = LoadGraph("GameAssets/Sprite/UI/anagoLv.png");
	ResultUI[8] = LoadGraph("GameAssets/Sprite/UI/body.png");
	ResultUI[9] = LoadGraph("GameAssets/Sprite/level3.png");
	ResultUI[10] = LoadGraph("GameAssets/Sprite/UI/result.png");

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

}


void ClearScene::Update()
{
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
	
	if (titleAnimeTimer >= titleAnimeMaxTimer) {
		titleAnimeTimer = 0;
	}

	titleSize = titleSize.lerp(Vector2{ 1.0,0 }, Vector2{ 0.7,0 }, Easing::EaseOutCubic(titleAnimeTimer, titleAnimeMaxTimer));
	BodyUISize = BodyUISize.lerp(Vector2{ 1.3,0 }, Vector2{ 1.0,0 }, Easing::EaseOutCubic(titleAnimeTimer, titleAnimeMaxTimer));

	tempPos[0] = tempPos[0].lerp(BodyUIStartPos[0], BodyUIEndPos[0], Easing::EaseOutCubic(UIFrame[0], 60));
	tempPos[1] = tempPos[1].lerp(BodyUIStartPos[0], BodyUIEndPos[1], Easing::EaseOutCubic(UIFrame[1], 60));
	tempPos[2] = tempPos[2].lerp(BodyUIStartPos[0], BodyUIEndPos[2], Easing::EaseOutCubic(UIFrame[2], 60));
	tempPos[3] = tempPos[3].lerp(BodyUIStartPos[0], BodyUIEndPos[3], Easing::EaseOutCubic(UIFrame[3], 60));
}

void ClearScene::Draw()
{
	
	DrawGraph(0, -180, backBottomImage, true);
	
	DrawGraph(0, 0, blueImage, true);
	DrawGraph(0, 0, vignetImage, true);

	if (frame >= 370) {
		DrawRotaGraph(1280 / 2, 900/2, 1, rot, targetImage, true);
	}
	DrawFormatString(0, 20, GetColor(255, 255, 255), "%d", frame);

	//結果発表
	DrawRotaGraph(1280/2, 80, titleSize.x, 0, ResultUI[10], true);

	//あなご
	DrawRotaGraph(150, 250, titleSize.x, 0, ResultUI[7], true);
	//からだ
	DrawRotaGraph(150, 350, titleSize.x, 0, ResultUI[8], true);

	ExBodyManager* exM =  ExBodyManager::GetInstance();
	LevelManager* lvM = LevelManager::GetInstance();

	DrawRotaGraph(tempPos[0].x, tempPos[0].y, BodyUISize.x, 0, levelImage[lvM->GetLevel() - 1], true);

	if (frame >= 92 * 1) {
		DrawRotaGraph(tempPos[1].x, tempPos[1].y, BodyUISize.x, 0, ResultUI[exM->GetBodyType(0)], true);
	}
	if (frame >= 92 * 2) {
		DrawRotaGraph(tempPos[2].x, tempPos[2].y, BodyUISize.x, 0, ResultUI[exM->GetBodyType(1)], true);
	}
	if (frame >= 92 * 3) {
		DrawRotaGraph(tempPos[3].x, tempPos[3].y, BodyUISize.x, 0, ResultUI[exM->GetBodyType(2)], true);
	}

	for (int i = 0; i < 3; i++) {
		Vector2 tempPos;
		Vector2 temptexturePos;

		//選択肢のポジション
		if (i == 0) {
			tempPos = { 240,165 };
		}
		else if (i == 1) {
			tempPos = { 240,265 };
		}
		else {
			tempPos = { 240,365 };
		}
		
		if (exM->GetBodyType(i) == 1) {
			//MUSCLE
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "マッスル");

			//DrawGraph(tempPos.x, tempPos.y, ResultUI[3], true);
		}
		else if (exM->GetBodyType(i) == 2) {
			//MAGICIAN
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "マジシャン");

			//DrawGraph(tempPos.x, tempPos.y, ResultUI[4], true);
			//DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
			//	256, 256, 0.5f, 0.5f, 0, magicianImage, true);
		}
		else if (exM->GetBodyType(i) == 3) {
			//JET
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "ジェット");


			//DrawGraph(tempPos.x, tempPos.y, ResultUI[5], true);
			//DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
			//	256, 256, 0.65f, 0.65f, 0, jetImage, true);
		}
		else if (exM->GetBodyType(i) == 4) {
			//GAMING
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "ゲーミング");


			//DrawGraph(tempPos.x, tempPos.y, ResultUI[6], true);
			//DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
			//	256, 256, 0.5f, 0.5f, 0, gamingImage, true);
		}
		else if (exM->GetBodyType(i) == 5) {
			//Shark
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "シャーク");
			//DrawGraph(tempPos.x, tempPos.y, ResultUI[7], true);
			//DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
			//	256, 256, 0.5f, 0.5f, 0, gamingImage, true);
		}
	}
	DrawFormatString(840, 400, GetColor(255, 255, 255), "チンアナゴ～！");

	Player::GetInstance()->Draw();
	ExBodyManager::GetInstance()->Draw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "clear");
}

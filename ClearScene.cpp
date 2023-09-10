#include "ClearScene.h"
#include "exBody/ExBodyManager.h"
#include "MathManager.h"

void ClearScene::Initialize()
{
}

void ClearScene::Update()
{

}

void ClearScene::Draw()
{
	
	DrawGraph(0, -180, backBottomImage, true);
	
	DrawGraph(0, 0, blueImage, true);
	DrawGraph(0, 0, vignetImage, true);
	DrawGraph(0, 0, targetImage, true);

	DrawRotaGraph3(620, 450,
		256, 256, 1.5, 1.5, 0, chinanaImage, true);

	ExBodyManager* exM =  ExBodyManager::GetInstance();
	for (int i = 0; i < 3; i++) {
		Vector2 tempPos;
		Vector2 temptexturePos;

		//選択肢のポジション
		if (i == 0) {
			tempPos = { 540,400 };
			temptexturePos = { 640,400 };
		}
		else if (i == 1) {
			tempPos = { 640,400 };
			temptexturePos = { 640,550 };
		}
		else {
			tempPos = { 740,400 };
			temptexturePos = { 640,700 };
		}

		if (exM->GetBodyType(i) == 1) {
			//MUSCLE
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "マッスル");

			DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
				384, 256, 0.5f, 0.5f, 0, muscularImage, true);
		}
		else if (exM->GetBodyType(i) == 2) {
			//MAGICIAN
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "マジシャン");

			DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
				256, 256, 0.5f, 0.5f, 0, magicianImage, true);
		}
		else if (exM->GetBodyType(i) == 3) {
			//JET
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "ジェット");

			DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
				256, 256, 0.65f, 0.65f, 0, jetImage, true);
		}
		else if (exM->GetBodyType(i) == 4) {
			//GAMING
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "ゲーミング");

			DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
				256, 256, 0.5f, 0.5f, 0, gamingImage, true);
		}
	}
	DrawFormatString(840, 400, GetColor(255, 255, 255), "チンアナゴ～！");

	ExBodyManager::GetInstance()->ResultDraw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "clear");
}

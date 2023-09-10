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
	ExBodyManager* exM =  ExBodyManager::GetInstance();
	for (int i = 0; i < 3; i++) {
		Vector2 tempPos;
		//選択肢のポジション
		if (i == 0) {
			tempPos = { 540,400 };
		}
		else if (i == 1) {
			tempPos = { 640,400 };
		}
		else {
			tempPos = { 740,400 };
		}

		if (exM->GetBodyType(i) == 1) {
			//MUSCLE
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "マッスル");
		}
		else if (exM->GetBodyType(i) == 2) {
			//MAGICIAN
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "マジシャン");
		}
		else if (exM->GetBodyType(i) == 3) {
			//JET
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "ジェット");
		}
		else if (exM->GetBodyType(i) == 4) {
			//GAMING
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "ゲーミング");
		}
	}
	DrawFormatString(840, 400, GetColor(255, 255, 255), "チンアナゴ～！");

	DrawGraph(0, -180, backBottomImage, true);

	DrawGraph(0, 0, blueImage, true);
	DrawGraph(0, 0, vignetImage, true);

	DrawRotaGraph3(620, 450,
		256, 256, 1.5, 1.5, 0, chinanaImage, true);
	ExBodyManager::GetInstance()->ResultDraw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "clear");
}

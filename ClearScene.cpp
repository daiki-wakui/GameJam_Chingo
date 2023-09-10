#include "ClearScene.h"
#include "exBody/ExBodyManager.h"

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

	DrawRotaGraph3(620, 450,
		256, 256, 1.5, 1.5, 0, chinanaImage, true);
	ExBodyManager::GetInstance()->ResultDraw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "clear");
}

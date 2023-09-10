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
	ExBodyManager::GetInstance()->ResultDraw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "clear");
}

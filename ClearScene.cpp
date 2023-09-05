#include "ClearScene.h"

void ClearScene::Initialize()
{
}

void ClearScene::Update()
{
}

void ClearScene::Draw()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "clear");
}

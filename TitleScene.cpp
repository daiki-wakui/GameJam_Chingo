#include "TitleScene.h"

void TitleScene::Initialize()
{
	player->Initialize();
}

void TitleScene::Update()
{
	player->Update();
}

void TitleScene::Draw()
{
	player->Draw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "title");
}

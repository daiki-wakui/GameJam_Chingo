#include "GameScene.h"

void GameScene::Initialize()
{
	player->Initialize();
}

void GameScene::Update()
{
	player->Update();
}

void GameScene::Draw()
{
	player->Draw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "game");
}

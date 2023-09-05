#include "GameScene.h"
#include "Player.h"
#include "ColliderManager.h"

void GameScene::Initialize()
{
	Player::GetInstance()->Initialize();
}

void GameScene::Update()
{
	Player::GetInstance()->Update();
	ColliderManager::GetInstance()->Update();
}

void GameScene::Draw()
{
	Player::GetInstance()->Draw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "game");
}

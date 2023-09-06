#include "GameScene.h"
#include "Player.h"
#include "ColliderManager.h"
#include "LevelManager.h"

void GameScene::Initialize()
{
	Player::GetInstance()->Initialize();
	LevelManager::GetInstance()->Initialize();
}

void GameScene::Update()
{
	Player::GetInstance()->Update();
	ColliderManager::GetInstance()->Update();
	LevelManager::GetInstance()->Update();
}

void GameScene::Draw()
{
	Player::GetInstance()->Draw();
	LevelManager::GetInstance()->Draw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "game");
}

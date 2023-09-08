#include "GameScene.h"
#include "Player.h"
#include "ColliderManager.h"
#include "LevelManager.h"
#include "exBody/ExBodyManager.h"
#include <stdlib.h>
#include <time.h>

void GameScene::Initialize()
{
	Player::GetInstance()->Initialize();
	LevelManager::GetInstance()->Initialize();
}

void GameScene::Update()
{
	if (ExBodyManager::GetInstance()->GetIsSelect()) {
		ExBodyManager::GetInstance()->Update();
		return;
	}

	Player::GetInstance()->Update();
	ColliderManager::GetInstance()->Update();
	LevelManager::GetInstance()->Update();

	//playerが地面に来た時
	if (Player::GetInstance()->GetIsShakeing()) {
		srand(time(NULL));
		shake->max = 21;
		shake->min = 10;
		shake->isShakeing = 1;
		Player::GetInstance()->SetIsShakeing(false);
		//シェイク開始
	}

	//シェイクの処理
	shake->Effect();
}

void GameScene::Draw()
{
	//地面
	DrawGraph(0, -180 + shake->randY, backImage, true);

	Player::GetInstance()->Draw();
	LevelManager::GetInstance()->Draw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "game");
}

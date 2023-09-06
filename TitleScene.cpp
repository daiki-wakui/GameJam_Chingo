#include "TitleScene.h"
#include "Player.h"

void TitleScene::Initialize()
{
	Player::GetInstance()->Initialize();
}

void TitleScene::Update()
{
	Player::GetInstance()->Update();
}

void TitleScene::Draw()
{
	Player::GetInstance()->Draw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "title");
}

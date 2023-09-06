#include "ExBodyManager.h"
#include "DxLib.h"
#include "LevelManager.h"
#include "Player.h"

ExBodyManager* ExBodyManager::GetInstance()
{
	static ExBodyManager instance;

	return &instance;
}

void ExBodyManager::Initialize()
{
	for (int i = 0; i < MAX_BODY; i++) {
		bodyType_[i] = NONE;
	}
}

void ExBodyManager::Update()
{

}

void ExBodyManager::Draw()
{
	Vector2 originPos = Player::GetInstance()->GetOriginPos();

	for (int i = 0; i < LevelManager::GetInstance()->GetLevel() - 1;i++) {
		DrawBox(originPos.x - BODY_WIDTH / 2,originPos.y + BODY_HEIGHT * i,originPos.x + BODY_WIDTH / 2,originPos.y + (BODY_HEIGHT * (i + 1)),GetColor(255,0 + i * 100,0),true);
		DrawCircle(originPos,30,GetColor(255,0,0));
	}
}

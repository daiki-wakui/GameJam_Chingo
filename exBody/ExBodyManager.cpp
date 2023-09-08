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
	isSelect_ = false;
	for (int i = 0; i < 3; i++) {
		choice_[i] = 0;
	}
}

void ExBodyManager::Update()
{
	if (isSelect_) {
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			if (mouseY > 300 && mouseY < 700) {
				if (mouseX > 40 && mouseX <= 440) {
					AddBody(MOD1);
					isSelect_ = false;
				}
				if (mouseX > 440 && mouseX <= 840) {
					AddBody(MOD2);
					isSelect_ = false;
				}
				if (mouseX > 840 && mouseX <= 1240) {
					AddBody(MOD3);
					isSelect_ = false;
				}
			}
		}
	}
}

void ExBodyManager::Draw()
{
	for (int i = 0; i < LevelManager::GetInstance()->GetLevel() - 1; i++) {
		if (Player::GetInstance()->GetActiveBody() > (i + 1) * 10) {
			BodyDraw(i);
		}
	}

	if (isSelect_) {
		DrawBox(40, 300, 440, 700, GetColor(255, 0, 0), true);
		DrawBox(440, 300, 840, 700, GetColor(0, 255, 0), true);
		DrawBox(840, 300, 1240, 700, GetColor(0, 0, 255), true);
	}
}

void ExBodyManager::BodyDraw(int i)
{
	switch (bodyType_[i])
	{
	case MOD1:
		DrawCircle(Player::GetInstance()->GetPos((i + 1) * 10), 55, GetColor(255, 0, 0));
		break;
	case MOD2:
		DrawCircle(Player::GetInstance()->GetPos((i + 1) * 10), 55, GetColor(0, 255, 0));
		break;
	case MOD3:
		DrawCircle(Player::GetInstance()->GetPos((i + 1) * 10), 55, GetColor(0, 0, 255));
		break;
	default:
		break;
	}
}

void ExBodyManager::AddBody(int num)
{
	bodyType_[LevelManager::GetInstance()->GetLevel() - 2] = num;
}

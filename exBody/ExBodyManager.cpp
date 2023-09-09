#include "ExBodyManager.h"
#include "LevelManager.h"
#include "Player.h"
#include "ScrollManager.h"

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
					AddBody(MUSCLE);
					isSelect_ = false;
				}
				if (mouseX > 440 && mouseX <= 840) {
					AddBody(MAGICIAN);
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
		DrawFormatString(40, 300,GetColor(255,255,255),"マッスル");
		DrawBox(440, 300, 840, 700, GetColor(0, 255, 0), true);
		DrawFormatString(440, 300, GetColor(255, 255, 255), "マジシャン");
		DrawBox(840, 300, 1240, 700, GetColor(0, 0, 255), true);
		DrawFormatString(840, 300, GetColor(255, 255, 255), "案3");
	}
}

void ExBodyManager::BodyDraw(int i)
{
	float angle = GetBodyAngle(i);

	switch (bodyType_[i])
	{
	case MUSCLE:
		//DrawCircle(Player::GetInstance()->GetPos((i + 1) * 10), 55, GetColor(255, 0, 0));

		DrawRotaGraph3(
			Player::GetInstance()->GetPos((i + 1) * 10).x,
			Player::GetInstance()->GetPos((i + 1) * 10).y + ScrollManager::GetInstance()->GetScroll(),
			384, 256, 0.45f, 0.45f, angle, muscularImage, true);
		break;
	case MAGICIAN:
		//DrawCircle(Player::GetInstance()->GetPos((i + 1) * 10), 55, GetColor(0, 255, 0));

		DrawRotaGraph3(
			Player::GetInstance()->GetPos((i + 1) * 10).x,
			Player::GetInstance()->GetPos((i + 1) * 10).y + ScrollManager::GetInstance()->GetScroll(),
			256, 256, 0.45f, 0.45f, angle, magicianImage, true);
		break;
	case MOD3:
		//DrawCircle(Player::GetInstance()->GetPos((i + 1) * 10), 55, GetColor(0, 0, 255));

		DrawRotaGraph3(
			Player::GetInstance()->GetPos((i + 1) * 10).x,
			Player::GetInstance()->GetPos((i + 1) * 10).y + ScrollManager::GetInstance()->GetScroll(),
			256, 256, 0.45f, 0.45f, angle, jetImage, true);
		break;
	default:
		break;
	}
}

void ExBodyManager::AddBody(int num)
{
	bodyType_[LevelManager::GetInstance()->GetLevel() - 2] = num;
}

float ExBodyManager::GetBodyAngle(int i)
{
	float temp = 3.141592f / 180.0f * Player::GetInstance()->GetAngle((i + 1) * 10);

	temp -= 3.14192f;

	return temp;
}

#include "ExBodyManager.h"
#include "LevelManager.h"
#include "Player.h"
#include "ScrollManager.h"
#include <random>

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
					AddBody(choice_[0]+1);
					isSelect_ = false;
				}
				if (mouseX > 440 && mouseX <= 840) {
					AddBody(choice_[1]+1);
					isSelect_ = false;
				}
				if (mouseX > 840 && mouseX <= 1240) {
					AddBody(choice_[2]+1);
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
		SelectDraw();
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
	case JET:
		//DrawCircle(Player::GetInstance()->GetPos((i + 1) * 10), 55, GetColor(0, 0, 255));

		DrawRotaGraph3(
			Player::GetInstance()->GetPos((i + 1) * 10).x,
			Player::GetInstance()->GetPos((i + 1) * 10).y + ScrollManager::GetInstance()->GetScroll(),
			256, 256, 0.45f, 0.45f, angle, jetImage, true);
		break;
	case GAMING:
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

void ExBodyManager::SelectRand()
{
	//ランダム
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());

	std::uniform_real_distribution<float> x(0, END_BODY_TYPE - 2 + 0.99999f);
	choice_[0] = (int)x(engine);

	while (true)
	{
		std::uniform_real_distribution<float> y(0, END_BODY_TYPE - 2 + 0.99999f);
		choice_[1] = (int)y(engine);
		if (choice_[0] != choice_[1]) {
			break;
		}
	}
	
	while (true)
	{
		std::uniform_real_distribution<float> z(0, END_BODY_TYPE - 2 + 0.99999f);
		choice_[2] = (int)z(engine);
		if (choice_[0] != choice_[2] && choice_[1] != choice_[2]) {
			break;
		}
	}
}

void ExBodyManager::SelectDraw()
{
	for (int i = 0; i < 3; i++) {
		Vector2 tempPos;
		//選択肢のポジション
		if (i == 0) {
			tempPos = { 40,300 };
		}
		else if (i == 1) {
			tempPos = { 440,300 };
		}
		else {
			tempPos = { 840,300 };
		}

		if (choice_[i] == 0) {
			//MUSCLE
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "マッスル");
		}
		else if (choice_[i] == 1) {
			//MAGICIAN
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "マジシャン");
		}
		else if (choice_[i] == 2) {
			//JET
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "ジェット");
		}
		else if (choice_[i] == 3) {
			//GAMING
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "ゲーミング");
		}
	}
}

void ExBodyManager::AddBody(int num)
{
	bodyType_[LevelManager::GetInstance()->GetLevel() - 2] = num;
}

void ExBodyManager::SetIsSelect()
{
	isSelect_ = true;
	SelectRand();
}

float ExBodyManager::GetBodyAngle(int i)
{
	float temp = 3.141592f / 180.0f * Player::GetInstance()->GetAngle((i + 1) * 10);

	temp -= 3.14192f;

	return temp;
}

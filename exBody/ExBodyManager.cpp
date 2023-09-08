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

	muscularImage = LoadGraph("GameAssets/Sprite/Body/muscular.png");
}

void ExBodyManager::Update()
{

}

void ExBodyManager::Draw()
{
	for (int i = 0; i < LevelManager::GetInstance()->GetLevel() - 1;i++) {
		if (Player::GetInstance()->GetActiveBody() > (i + 1) * 10) {
			BodyDraw(i);
		}
	}
}

void ExBodyManager::BodyDraw(int i)
{
	float angle = GetBodyAngle(i);

	switch (bodyType_[i])
	{
	case MUSCLE:
		DrawCircle(Player::GetInstance()->GetPos((i + 1) * 10), 55, GetColor(255, 0, 0));

		DrawRotaGraph3(
			Player::GetInstance()->GetPos((i + 1) * 10).x,
			Player::GetInstance()->GetPos((i + 1) * 10).y,
			384, 256, 0.45f, 0.45f, angle, muscularImage, true);
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

float ExBodyManager::GetBodyAngle(int i)
{
	float temp = 3.141592f / 180.0f * Player::GetInstance()->GetAngle((i + 1) * 10);

	temp -= 3.14192f;

	return temp;
}

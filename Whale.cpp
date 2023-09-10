#include "Whale.h"
#include "DxLib.h"
#include "EnemyManager.h"
#include "ScrollManager.h"

void Whale::Initialize(Vector2 pos)
{
	BaseEnemy::Initialize(pos);

	if (pos.x < 640) {
		pos_.x = -10;
		isWay_ = true;
	}
	if (pos.x >= 640) {
		pos_.x = 1290;
		isWay_ = false;
	}

	r_ = RADIUS;
	healHang_ = HANG;
	exp_ = EXP;

	texture_ = LoadGraph("GameAssets/Sprite/enemy_fish.png");
}

void Whale::Update()
{
	EnemyManager::GetInstance()->AddFishNum();

	if (isWay_) {
		pos_.x += SPEED_MOVE;
	}
	else {
		pos_.x += -SPEED_MOVE;
	}

	if (pos_.x > 1300 || pos_.x < -20) {
		isWay_ = (isWay_ + 1) % 2;
	}
}

void Whale::Draw()
{
	if (isWay_) {
		DrawRotaGraph3(pos_.x, pos_.y + ScrollManager::GetInstance()->GetScroll(), 256, 256, 0.2f, 0.2f, 0, texture_, true, true);
	}
	else {
		DrawRotaGraph3(pos_.x, pos_.y + ScrollManager::GetInstance()->GetScroll(), 256, 256, 0.2f, 0.2f, 0, texture_, true);
	}
	DrawCircle(pos_, r_, GetColor(255, 100, 100));
}

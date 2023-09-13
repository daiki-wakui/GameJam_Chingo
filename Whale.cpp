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
	lv_ = LV;

	texture_ = LoadGraph("GameAssets/Sprite/Enemy_Whale.png");

	colNum_ = MAX_COL;
}

void Whale::Update()
{
	EnemyManager::GetInstance()->AddWhaleNum();

	if (isWay_) {
		pos_.x += SPEED_MOVE;
	}
	else {
		pos_.x += -SPEED_MOVE;
	}

	if (pos_.x > 1300 || pos_.x < -20) {
		isWay_ = (isWay_ + 1) % 2;
	}

	colPos_[0] = pos_;
	colPos_[0].x += r_;
	colPos_[1] = pos_;
	colPos_[1].x -= r_;
}

void Whale::Draw()
{
	DrawCircle(pos_, r_, GetColor(255, 100, 100));
	DrawCircle(colPos_[0], r_, GetColor(255, 100, 100));
	DrawCircle(colPos_[1], r_, GetColor(255, 100, 100));

	if (isWay_) {
		if (!isCook_) {
			DrawRotaGraph3(pos_.x - 100, pos_.y + ScrollManager::GetInstance()->GetScroll(), 256, 256, 0.5f, 0.5f, 0, texture_, true, true);
		}
	}
	else {
		if (!isCook_) {
			DrawRotaGraph3(pos_.x - 100, pos_.y + ScrollManager::GetInstance()->GetScroll(), 256, 256, 0.5f, 0.5f, 0, texture_, true);
		}
	}
}

Vector2 Whale::Col(int num)
{
	return colPos_[num];
}

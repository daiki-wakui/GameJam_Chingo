#include "Dolphin.h"
#include "EnemyManager.h"
#include <math.h>

void Dolphin::Initialize(Vector2 pos)
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
	originY_ = pos.y;
}

void Dolphin::Update()
{
	EnemyManager::GetInstance()->AddDolphinNum();

	if (isWay_) {
		pos_.x += SPEED_MOVE;
	}
	else {
		pos_.x += -SPEED_MOVE;
	}

	if (pos_.x > 1300 || pos_.x < -20) {
		isDead_ = true;
	}

	frame_ += 0.05f;
	pos_.y = originY_ + sinf(frame_) * 100;
}

void Dolphin::Draw()
{
	DrawCircle(pos_, r_, GetColor(255, 100, 100));
}

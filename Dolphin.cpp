#include "Dolphin.h"
#include "EnemyManager.h"
#include <math.h>
#include "DxLib.h"
#include "ScrollManager.h"
#include "LevelManager.h"

void Dolphin::Initialize(Vector2 pos)
{
	BaseEnemy::Initialize(pos);

	if (pos.x < 640) {
		pos_.x = -200;
		isWay_ = true;
	}
	if (pos.x >= 640) {
		pos_.x = 1480;
		isWay_ = false;
	}

	r_ = RADIUS;
	healHang_ = HANG;
	lv_ = LV;
	exp_ = EXP;
	originY_ = pos.y;

	texture_ = LoadGraph("GameAssets/Sprite/Enemy_Dolphin.png");
	lvImage_ = LoadGraph("GameAssets/Sprite/UI/enemyLv3.png");

	colNum_ = MAX_COL;
}

void Dolphin::Update()
{
	if (!isCook_) {
		EnemyManager::GetInstance()->AddDolphinNum();

		if (isWay_) {
			pos_.x += SPEED_MOVE;
		}
		else {
			pos_.x += -SPEED_MOVE;
		}

		frame_ += 0.05f;
		pos_.y = originY_ + sinf(frame_) * 100;
	}

	if (pos_.x > 1580 || pos_.x < -300) {
		isDead_ = true;
	}

	colPos_[0] = pos_;
	colPos_[0].x += r_ * 2;
	colPos_[1] = pos_;
	colPos_[1].x -= r_ * 2;
}

void Dolphin::Draw()
{
	if (isWay_) {
		if (!isCook_) {
			DrawRotaGraph3(pos_.x, pos_.y + ScrollManager::GetInstance()->GetScroll(), 320, 256, 0.6f, 0.6f, 0, texture_, true, true);
		}
		else {
			DrawRotaGraph3(pos_.x, pos_.y + ScrollManager::GetInstance()->GetScroll(), 320, 256, 0.6f, 0.6f, 1.57, cookTex_, true, true);
		}
	}
	else {
		if (!isCook_) {
			DrawRotaGraph3(pos_.x, pos_.y + ScrollManager::GetInstance()->GetScroll(), 320, 256, 0.6f, 0.6f, 0, texture_, true);
			DrawRotaGraph(pos_.x, pos_.y + ScrollManager::GetInstance()->GetScroll() + r_ * 3 - 55, 0.5f, 0, lvImage_, true);

		}
		else {
			DrawRotaGraph3(pos_.x, pos_.y + ScrollManager::GetInstance()->GetScroll(), 320, 256, 0.6f, 0.6f, -1.57, cookTex_, true);

		}
	}
	if (LevelManager::GetInstance()->GetLevel() < LV) {
		DrawRotaGraph(pos_.x, pos_.y + ScrollManager::GetInstance()->GetScroll() + r_ * 3, 0.3f, 0, warningTex_, true);
	}

	//DrawCircle(pos_, r_, GetColor(255, 100, 100));
	//DrawCircle(colPos_[0], r_, GetColor(255, 100, 100));
	//DrawCircle(colPos_[1], r_, GetColor(255, 100, 100));
}

Vector2 Dolphin::Col(int num)
{
	return colPos_[num];
}

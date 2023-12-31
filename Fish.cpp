#include "Fish.h"
#include "DxLib.h"
#include "EnemyManager.h"
#include "ScrollManager.h"
#include "LevelManager.h"

void Fish::Initialize(Vector2 pos)
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

	texture_ = LoadGraph("GameAssets/Sprite/fish_redBream.png");
	lvImage_ = LoadGraph("GameAssets/Sprite/UI/enemyLv2.png");

	colNum_ = MAX_COL;
}

void Fish::Update()
{
	if (!isCook_) {
		EnemyManager::GetInstance()->AddFishNum();

		if (isWay_) {
			pos_.x += SPEED_MOVE;
		}
		else {
			pos_.x += -SPEED_MOVE;
		}

	}

	if (pos_.x > 1300 || pos_.x < -20) {
		isDead_ = true;
	}


	colPos_[0] = pos_;
	colPos_[0].x += r_ + 1;
	colPos_[1] = pos_;
	colPos_[1].x -= r_ + 1;
}

void Fish::Draw()
{
	if (isWay_) {
		if (!isCook_) {
			DrawRotaGraph3(pos_.x, pos_.y + ScrollManager::GetInstance()->GetScroll(), 256, 256, 0.3f, 0.3f, 0, texture_, true, true);
		}
		else {
			DrawRotaGraph3(pos_.x, pos_.y + ScrollManager::GetInstance()->GetScroll(), 256, 256, 0.3f, 0.3f, 1.57, cookTex_, true, true);
		}
	}
	else {
		if (!isCook_) {
			DrawRotaGraph3(pos_.x, pos_.y + ScrollManager::GetInstance()->GetScroll(), 256, 256, 0.3f, 0.3f, 0, texture_, true);
		}
		else {
			DrawRotaGraph3(pos_.x, pos_.y + ScrollManager::GetInstance()->GetScroll(), 256, 256, 0.3f, 0.3f, -1.57, cookTex_, true);
		}
	}
	if (LevelManager::GetInstance()->GetLevel() < LV) {
		DrawRotaGraph(pos_.x, pos_.y + ScrollManager::GetInstance()->GetScroll() + r_ * 3,0.3f, 0, warningTex_, true);
		DrawRotaGraph(pos_.x+80, pos_.y + ScrollManager::GetInstance()->GetScroll() + r_ * 3, 0.3f, 0, lvImage_, true);

	}

	//DrawCircle(pos_, r_, GetColor(255, 100, 100));
	//DrawCircle(colPos_[0], r_, GetColor(255, 100, 100));
	//DrawCircle(colPos_[1], r_, GetColor(255, 100, 100));
}

Vector2 Fish::Col(int num)
{
	return colPos_[num];
}

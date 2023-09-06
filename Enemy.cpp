#include "Enemy.h"
#include "Dxlib.h"

void Enemy::Initialize(Vector2 pos)
{
	pos_ = pos;
	r_ = 5;
	deadTimer_ = 255;
}

void Enemy::Update()
{
	if (isDead_) {
		deadTimer_-= 2;
	}
}

void Enemy::Draw()
{
	if (!isDead_) {
		DrawCircle(pos_, r_, GetColor(255, 100, 100));
		//DrawGraph(pos_.x, pos_.y, planktonImage, true);
		DrawExtendGraph(0 + pos_.x, 0 + pos_.y, 64 + pos_.x, 64 + pos_.y, planktonImage, true);
	}
	else if(deadTimer_ > 0){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, deadTimer_);
		DrawFormatString(pos_.x,pos_.y,GetColor(255,100,100),"+2");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

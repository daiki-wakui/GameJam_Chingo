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
		//DrawGraph(pos_.x - 64, pos_.y - 64, planktonImage, true);
		
		DrawExtendGraph(pos_.x - 32, pos_.y - 32, 64 + (pos_.x-32), 64 + (pos_.y-32), planktonImage, true);
		DrawCircle(pos_, r_, GetColor(255, 100, 100));
	}
	else if(deadTimer_ > 0){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, deadTimer_);
		DrawFormatString(pos_.x,pos_.y,GetColor(255,100,100),"+10");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

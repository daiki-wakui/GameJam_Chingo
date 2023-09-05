#include "Enemy.h"
#include "Dxlib.h"

void Enemy::Initialize(Vector2 pos)
{
	pos_ = pos;
	r_ = 5;
}

void Enemy::Update()
{

}

void Enemy::Draw()
{
	if (!isDead_) {
		DrawCircle(pos_, r_, GetColor(255, 100, 100));
	}
	else {
		DrawFormatString(pos_.x,pos_.y,GetColor(255,0,0),"+20");
	}
}

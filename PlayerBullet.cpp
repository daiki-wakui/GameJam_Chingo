#include "PlayerBullet.h"
#include "DxLib.h"

void PlayerBullet::Initialize(Vector2 pos,Vector2 way){
	pos_ = pos;
	way_ = way.normalize();
	timer_ = TIME;
	isDead_ = false;
}

void PlayerBullet::Update()
{
	pos_ += way_ * SPEED;
	if (--timer_ <= 0) {
		isDead_ = true;
	}
}

void PlayerBullet::Draw()
{
	DrawCircle(pos_,R,GetColor(200,0,0));
}

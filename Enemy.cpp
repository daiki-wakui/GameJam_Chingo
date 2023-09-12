#include "Enemy.h"
#include "Dxlib.h"
#include <math.h>
#include <random>
#include "ScrollManager.h"

void Enemy::Initialize(Vector2 pos)
{
	pos_ = pos;
	r_ = 5;
	deadTimer_ = 255;

	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());
	std::uniform_real_distribution<float> rand(-10, 40);

	addFrame_ = rand(engine);
}

void Enemy::Update()
{
	if (isDead_) {
		deadTimer_-= 2;
	}

	frame_++;

	pos_.y = 0.34f * sinf(2 * 3.14f * (frame_ + addFrame_) / 200) + pos_.y;
}

void Enemy::Draw()
{
	if (!isDead_) {
		//DrawGraph(pos_.x - 64, pos_.y - 64, planktonImage, true);
		
		DrawRotaGraph3(pos_.x, pos_.y + ScrollManager::GetInstance()->GetScroll(), 64, 64, 0.5f, 0.5f, rot_, planktonImage, true);

		//DrawExtendGraph(pos_.x - 32, pos_.y - 32, 64 + (pos_.x-32), 64 + (pos_.y-32), planktonImage, true);
		//DrawCircle(pos_, r_, GetColor(255, 100, 100));
	}
	else if(deadTimer_ > 0){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, deadTimer_);
		DrawFormatString(pos_.x,pos_.y,GetColor(255,100,100),"+10");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

#include "Plankton.h"
#include "ScrollManager.h"
#include <random>
#include "DxLib.h"
#include "EnemyManager.h"
#include "Easing.h"

void Plankton::Initialize(Vector2 pos)
{
	BaseEnemy::Initialize(pos);
	r_ = RADIUS;
	healHang_ = HANG;
	exp_ = EXP;
	lv_ = LV;

	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());
	std::uniform_real_distribution<float> rand(-10, 40);

	addFrame_ = rand(engine);

	texture_ = LoadGraph("GameAssets/Sprite/Enemy_Plankton_01.png");
}

void Plankton::Update()
{
	EnemyManager::GetInstance()->AddPlanktonNum(type_);

	frame_++;
	pos_.y = 0.34f * sinf(2 * 3.14f * (frame_ + addFrame_) / 200) + pos_.y;
}

void Plankton::Draw()
{
	if (!isCook_) {
		DrawRotaGraph3(pos_.x, pos_.y + ScrollManager::GetInstance()->GetScroll(), 256, 256, 0.13f * GetScale(), 0.13f * GetScale(), rot_, texture_, true);
	}
	else {
		DrawRotaGraph3(pos_.x, pos_.y + ScrollManager::GetInstance()->GetScroll(), 256, 256, 0.13f * GetScale(), 0.13f * GetScale(), rot_, cookTex_, true);
	}
	//DrawCircle(pos_, r_, GetColor(255, 100, 100));
}

float Plankton::GetScale()
{
	if (frame_ >= 30) {
		return 1.0f;
	}

	return Easing::EaseOutBack(frame_, 30);
}

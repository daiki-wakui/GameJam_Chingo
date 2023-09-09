#include "Plankton.h"
#include "ScrollManager.h"
#include <random>

void Plankton::Initialize(Vector2 pos)
{
	BaseEnemy::Initialize(pos);
	r_ = RADIUS;
	healHang_ = HANG;
	exp_ = EXP;

	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());
	std::uniform_real_distribution<float> rand(-10, 40);

	addFrame_ = rand(engine);
}

void Plankton::Update()
{
	frame_++;
	pos_.y = 0.34f * sinf(2 * 3.14f * (frame_ + addFrame_) / 200) + pos_.y;

}

void Plankton::Draw()
{
	DrawRotaGraph3(pos_.x, pos_.y + ScrollManager::GetInstance()->GetScroll(), 64, 64, 0.5f, 0.5f, rot_, planktonImage, true);
	DrawCircle(pos_, r_, GetColor(255, 100, 100));
}

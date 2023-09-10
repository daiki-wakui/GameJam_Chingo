#include "Plankton.h"
#include "ScrollManager.h"
#include <random>
#include "DxLib.h"
#include "EnemyManager.h"

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

	texture_ = LoadGraph("GameAssets/Sprite/Enemy_Plankton_01.png");
}

void Plankton::Update()
{
	EnemyManager::GetInstance()->AddPlanktonNum();

	frame_++;
	pos_.y = 0.34f * sinf(2 * 3.14f * (frame_ + addFrame_) / 200) + pos_.y;
}

void Plankton::Draw()
{
	DrawRotaGraph3(pos_.x, pos_.y + ScrollManager::GetInstance()->GetScroll(), 256, 256, 0.13f, 0.13f, rot_, texture_, true);
	//DrawCircle(pos_, r_, GetColor(255, 100, 100));
}

#include "EnemyManager.h"
#include <random>

EnemyManager* EnemyManager::GetInstance()
{
	static EnemyManager instance;

	return &instance;
}

void EnemyManager::Initialize()
{//ƒ‰ƒ“ƒ_ƒ€
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());

	for (int i = 0; i < MAX_ENEMY; i++) {
		std::uniform_real_distribution<float> x(0, 1280);
		std::uniform_real_distribution<float> y(0, 400);

		enemy_[i].Initialize({ x(engine),y(engine) });
	}
}

void EnemyManager::Update()
{
	for (int i = 0; i < MAX_ENEMY; i++) {
		enemy_[i].Update();
	}
}

void EnemyManager::Draw()
{
	for (int i = 0; i < MAX_ENEMY; i++) {
		enemy_[i].Draw();
	}
}

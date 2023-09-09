#include "EnemyManager.h"
#include <random>
#include "Plankton.h"

using namespace std;

EnemyManager* EnemyManager::GetInstance()
{
	static EnemyManager instance;

	return &instance;
}

void EnemyManager::Initialize()
{
	//リセット時の処理
	for (unique_ptr<BaseEnemy>& enemy : enemys_) {
		enemy->SetIsDead();
	}

	//ランダム
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());

	for (int i = 0; i < MAX_ENEMY; i++) {
		std::uniform_real_distribution<float> x(0, 1280);
		std::uniform_real_distribution<float> y(-3000, 500);
		std::uniform_real_distribution<float> rot(30, 300);

		PopPlankton({ x(engine),y(engine) }, rot(engine));

		//enemy_[i].Initialize({ x(engine),y(engine) });
		//enemy_[i].SetRotation(rot(engine));
	}
}

void EnemyManager::Update()
{
	//死んだ敵の削除
	enemys_.remove_if([](unique_ptr<BaseEnemy>& enemy) {
		return enemy->GetIsDead();
	});

	//敵全員の処理
	for (unique_ptr<BaseEnemy>& enemy : enemys_) {
		enemy->Update();
	}

	//for (int i = 0; i < MAX_ENEMY; i++) {
	//	enemy_[i].Update();
	//}
}

void EnemyManager::Draw()
{
	for (unique_ptr<BaseEnemy>& enemy : enemys_) {
		enemy->Draw();
	}

	//for (int i = 0; i < MAX_ENEMY; i++) {
	//	enemy_[i].Draw();
	//}
}

void EnemyManager::PopPlankton(Vector2 pos,float rot)
{
	unique_ptr<BaseEnemy> newEnemy = make_unique<Plankton>();
	newEnemy->Initialize(pos);
	newEnemy->SetRotation(rot);
	enemys_.push_back(move(newEnemy));
}

#include "EnemyManager.h"
#include <random>
#include "Plankton.h"
#include "Fish.h"

using namespace std;

EnemyManager* EnemyManager::GetInstance()
{
	static EnemyManager instance;

	return &instance;
}

void EnemyManager::Initialize()
{
	//���Z�b�g���̏���
	for (unique_ptr<BaseEnemy>& enemy : enemys_) {
		enemy->SetIsDead();
	}

	//�����_��
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());

	for (int i = 0; i < MAX_ENEMY; i++) {
		std::uniform_real_distribution<float> x(0, 1280);
		std::uniform_real_distribution<float> y(-3000, 500);
		std::uniform_real_distribution<float> rot(30, 300);

		PopPlankton({ x(engine),y(engine) }, rot(engine));
		PopFish({ x(engine),y(engine) });
	}
}

void EnemyManager::Update()
{
	//���񂾓G�̍폜
	enemys_.remove_if([](unique_ptr<BaseEnemy>& enemy) {
		return enemy->GetIsDead();
	});

	//�G�S���̏���
	for (unique_ptr<BaseEnemy>& enemy : enemys_) {
		enemy->Update();
	}
}

void EnemyManager::Draw()
{
	for (unique_ptr<BaseEnemy>& enemy : enemys_) {
		enemy->Draw();
	}
}

void EnemyManager::PopPlankton(Vector2 pos,float rot)
{
	unique_ptr<BaseEnemy> newEnemy = make_unique<Plankton>();
	newEnemy->Initialize(pos);
	newEnemy->SetRotation(rot);
	enemys_.push_back(move(newEnemy));
}

void EnemyManager::PopFish(Vector2 pos)
{
	unique_ptr<BaseEnemy> newEnemy = make_unique<Fish>();
	newEnemy->Initialize(pos);
	enemys_.push_back(move(newEnemy));
}

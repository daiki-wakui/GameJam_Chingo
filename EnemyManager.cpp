#include "EnemyManager.h"
#include <random>
#include "Plankton.h"
#include "Player.h"
#include "Fish.h"
#include "Dolphin.h"
#include "Whale.h"
#include "Sakaban.h"

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

	fishPopTimer_ = TIME_FISH_POP;
	dolphinNum_ = TIME_DOLPHIN_POP;

	PopWhale();
}

void EnemyManager::Update()
{
	//死んだ敵の削除
	enemys_.remove_if([](unique_ptr<BaseEnemy>& enemy) {
		return enemy->GetIsDead();
		});

	//敵全員の処理
	//数確認
	for (int i = 0; i < 8; i++) {
		planktonNum_[i] = 0;
	}
	fishNum_ = 0;
	dolphinNum_ = 0;
	whaleNum_ = 0;
	for (unique_ptr<BaseEnemy>& enemy : enemys_) {
		enemy->Update();
	}

	//プレイヤーが戻った時にリポップ
	if (Player::GetInstance()->GetIsExtend()) {
		for (int j = 0; j < 7; j++) {
			if (j > 3) {
				for (int i = planktonNum_[j]; i < 13; i++) {
					RePopPlankton(j);
				}
			}
			else {
				for (int i = planktonNum_[j]; i < 20; i++) {
					RePopPlankton(j);
				}
			}
		}
	}

	if (MAX_FISH > fishNum_) {
		if (--fishPopTimer_ <= 0) {
			PopFish();
		}
	}

	if (MAX_DOLPHIN > dolphinNum_) {
		if (--dolphinNum_ <= 0) {
			PopDolphin();
		}
	}

	if (--sakabanPopTimer_ <= 0) {
		PopSakaban();
	}
}

void EnemyManager::Draw()
{
	for (unique_ptr<BaseEnemy>& enemy : enemys_) {
		enemy->Draw();
	}
}

void EnemyManager::PopPlankton()
{
	//ランダム
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());

	std::uniform_real_distribution<float> x(0, 1280);
	std::uniform_real_distribution<float> y(0, 500);
	std::uniform_real_distribution<float> rot(30, 300);

	unique_ptr<BaseEnemy> newEnemy = make_unique<Plankton>();
	newEnemy->Initialize({ x(engine),y(engine) });
	newEnemy->SetRotation(rot(engine));
	newEnemy->SetType(y(engine) / 1080);
	enemys_.push_back(move(newEnemy));
}

void EnemyManager::RePopPlankton(int num)
{
	//ランダム
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());

	std::uniform_real_distribution<float> x(0, 1280);
	std::uniform_real_distribution<float> y(-1080 * (num + 1) + 600, -1080 * num + 600);
	std::uniform_real_distribution<float> rot(30, 300);


	unique_ptr<BaseEnemy> newEnemy = make_unique<Plankton>();
	newEnemy->Initialize({ x(engine),y(engine) });
	newEnemy->SetRotation(rot(engine));
	newEnemy->SetType(num);
	enemys_.push_back(move(newEnemy));
}

void EnemyManager::PopFish()
{
	//ランダム
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());

	std::uniform_real_distribution<float> x(0, 1280);
	std::uniform_real_distribution<float> y(-1080 * 8, -1080 * 1);

	unique_ptr<BaseEnemy> newEnemy = make_unique<Fish>();
	newEnemy->Initialize({ x(engine),y(engine) });
	enemys_.push_back(move(newEnemy));

	fishPopTimer_ = TIME_FISH_POP;
}

void EnemyManager::PopDolphin()
{
	//ランダム
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());

	std::uniform_real_distribution<float> x(0, 1280);
	std::uniform_real_distribution<float> y(-1080 * 8, -1080 * 3);

	unique_ptr<BaseEnemy> newEnemy = make_unique<Dolphin>();
	newEnemy->Initialize({ x(engine),y(engine) });
	enemys_.push_back(move(newEnemy));

	fishPopTimer_ = TIME_FISH_POP;
}

void EnemyManager::PopWhale()
{
	//ランダム
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());

	std::uniform_real_distribution<float> x(0, 1280);

	unique_ptr<BaseEnemy> newEnemy = make_unique<Whale>();
	newEnemy->Initialize({ x(engine),-8500 });
	enemys_.push_back(move(newEnemy));
}

void EnemyManager::PopSakaban()
{
	//ランダム
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());

	std::uniform_real_distribution<float> rand(0, 5);
	if (rand(engine) <= 0.9f) {

		std::uniform_real_distribution<float> x(0, 1280);
		std::uniform_real_distribution<float> y(-1080 * 7, 0);


		unique_ptr<BaseEnemy> newEnemy = make_unique<Sakaban>();
		newEnemy->Initialize({ x(engine),y(engine) });
		enemys_.push_back(move(newEnemy));
	}

	sakabanPopTimer_ = TIME_SAKABAN_POP;
}

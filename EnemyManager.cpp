#include "EnemyManager.h"
#include <random>
#include "Plankton.h"
#include "Player.h"
#include "Fish.h"
#include "Dolphin.h"


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

	fishPopTimer_ = TIME_FISH_POP;
	dolphinNum_ = TIME_DOLPHIN_POP;

	for (int i = 0; i < MAX_PLANKTON; i++) {
		PopPlankton();
	}
}

void EnemyManager::Update()
{
	//���񂾓G�̍폜
	enemys_.remove_if([](unique_ptr<BaseEnemy>& enemy) {
		return enemy->GetIsDead();
	});


	//�G�S���̏���
	//���m�F
	planktonNum_ = 0;
	fishNum_ = 0;
	dolphinNum_ = 0;
	for (unique_ptr<BaseEnemy>& enemy : enemys_) {
		enemy->Update();
	}

	//�v���C���[���߂������Ƀ��|�b�v
	if (Player::GetInstance()->GetIsExtend()) {
		for (int i = planktonNum_; i < MAX_PLANKTON; i++) {
			RePopPlankton();
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
}

void EnemyManager::Draw()
{
	for (unique_ptr<BaseEnemy>& enemy : enemys_) {
		enemy->Draw();
	}
}

void EnemyManager::PopPlankton()
{
	//�����_��
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());

	std::uniform_real_distribution<float> x(0, 1280);
	std::uniform_real_distribution<float> y(-3000, 500);
	std::uniform_real_distribution<float> rot(30, 300);


	unique_ptr<BaseEnemy> newEnemy = make_unique<Plankton>();
	newEnemy->Initialize({x(engine),y(engine)});
	newEnemy->SetRotation(rot(engine));
	enemys_.push_back(move(newEnemy));
}

void EnemyManager::RePopPlankton()
{
	//�����_��
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());

	std::uniform_real_distribution<float> x(0, 1280);
	std::uniform_real_distribution<float> y(-2000, 0);
	std::uniform_real_distribution<float> rot(30, 300);


	unique_ptr<BaseEnemy> newEnemy = make_unique<Plankton>();
	newEnemy->Initialize({ x(engine),y(engine) });
	newEnemy->SetRotation(rot(engine));
	enemys_.push_back(move(newEnemy));
}

void EnemyManager::PopFish()
{
	//�����_��
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());

	std::uniform_real_distribution<float> x(0, 1280);
	std::uniform_real_distribution<float> y(-3000, 0);

	unique_ptr<BaseEnemy> newEnemy = make_unique<Fish>();
	newEnemy->Initialize({ x(engine),y(engine) });
	enemys_.push_back(move(newEnemy));

	fishPopTimer_ = TIME_FISH_POP;
}

void EnemyManager::PopDolphin()
{
	//�����_��
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());

	std::uniform_real_distribution<float> x(0, 1280);
	std::uniform_real_distribution<float> y(-3000, 0);

	unique_ptr<BaseEnemy> newEnemy = make_unique<Dolphin>();
	newEnemy->Initialize({ x(engine),y(engine) });
	enemys_.push_back(move(newEnemy));

	fishPopTimer_ = TIME_FISH_POP;
}

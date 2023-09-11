#include "BulletManager.h"

using namespace std;

BulletManager* BulletManager::GetInstance()
{
	static BulletManager instance;

	return &instance;
}

void BulletManager::Initialize()
{
	//���Z�b�g���̏���
	for (unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->SetIsDead();
	}
}

void BulletManager::Update()
{
	//���񂾓G�̍폜
	bullets_.remove_if([](unique_ptr<PlayerBullet>& bullet) {
		return bullet->GetIsDead();
	});

	for (unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}
}

void BulletManager::Draw()
{
	for (unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw();
	}
}

void BulletManager::Pop(Vector2 pos,Vector2 way)
{
	unique_ptr<PlayerBullet> newEnemy = make_unique<PlayerBullet>();
	newEnemy->Initialize(pos, way);
	bullets_.push_back(move(newEnemy));
}

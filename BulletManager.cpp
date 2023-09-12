#include "BulletManager.h"

using namespace std;

BulletManager* BulletManager::GetInstance()
{
	static BulletManager instance;

	return &instance;
}

void BulletManager::Initialize()
{
	//ƒŠƒZƒbƒg‚Ìˆ—
	for (unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->SetIsDead();
	}
}

void BulletManager::Update()
{
	//€‚ñ‚¾“G‚Ìíœ
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

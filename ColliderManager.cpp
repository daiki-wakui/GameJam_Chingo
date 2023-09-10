#include "ColliderManager.h"
#include "Player.h"
#include "EnemyManager.h"
#include "LevelManager.h"
#include <memory>

using namespace std;

ColliderManager* ColliderManager::GetInstance()
{
	static ColliderManager instance;

	return &instance;
}

void ColliderManager::Update()
{
	Player* player = Player::GetInstance();
	EnemyManager* enemyM = EnemyManager::GetInstance();
	LevelManager* expM = LevelManager::GetInstance();

	for (BaseEnemy* enemy : enemyM->GetEnemyList()) {
		for (int p = 0; p < player->GetNumNeck(); p++) {
			Vector2 P = player->GetPos(p);
			if (CircleCol(enemy->GetPos(), enemy->GetR(), P, 30)) {
				player->AddBodyLength();
				enemy->SetIsDead();
				expM->AddExp(enemy->GetEXP());
			}
		}
	}
}

bool ColliderManager::CircleCol(Vector2 Ap, int Ar, Vector2 Bp, int Br)
{
	if ((Bp - Ap).length() < Ar + Br) {
		return true;
	}
	return false;
}
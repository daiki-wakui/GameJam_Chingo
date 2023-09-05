#include "ColliderManager.h"
#include "Player.h"
#include "EnemyManager.h"

ColliderManager* ColliderManager::GetInstance()
{
	static ColliderManager instance;

	return &instance;
}

void ColliderManager::Update()
{
	Player* player = Player::GetInstance();
	EnemyManager* enemyM = EnemyManager::GetInstance();

	for (int ene = 0; ene < enemyM->GetEnemyNum();ene++) {
		Vector2 E = enemyM->GetEnemyPos(ene);
		if (enemyM->GetEnemyIsDead(ene)) {
			continue;
		}
		for (int p = 0; p < player->GetActiveBody(); p++) {
			Vector2 P = player->GetPos(p);

			if (CircleCol(E, 5, P, 30)) {
				player->AddBodyLength();
				enemyM->SetEnemyIsDead(ene);
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
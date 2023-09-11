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
			if (CircleCol(enemy->GetPos(), enemy->GetR(), P, player->GetThickness())) {
				//食える時
				if (expM->GetLevel() >= enemy->GetLv()) {
					player->AddBodyLength(enemy->GetHang());
					enemy->SetIsDead();
					expM->AddExp(enemy->GetEXP());
				}
				//食えない時
				else {
					player->SubBodyLength();
					player->SetInv();
				}
			}
			else {
				for (int i = 0; i < enemy->GetColNum(); i++) {
					if (CircleCol(enemy->Col(i), enemy->GetR(), P, player->GetThickness())) {
						//食える時
						if (expM->GetLevel() >= enemy->GetLv()) {
							player->AddBodyLength(enemy->GetHang());
							enemy->SetIsDead();
							expM->AddExp(enemy->GetEXP());
						}
						//食えない時
						else {
							player->SubBodyLength();
							player->SetInv();
						}
					}
				}
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
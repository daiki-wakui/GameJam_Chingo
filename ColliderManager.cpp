#include "ColliderManager.h"
#include "Player.h"
#include "EnemyManager.h"
#include "LevelManager.h"
#include <memory>
#include "exBody/ExBodyManager.h"
#include "BulletManager.h"

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
	ExBodyManager* exBodyM = ExBodyManager::GetInstance();
	BulletManager* bulletM = BulletManager::GetInstance();

	for (BaseEnemy* enemy : enemyM->GetEnemyList()) {
		for (int p = 0; p < player->GetNumNeck(); p++) {
			Vector2 P = player->GetPos(p);
			if (CircleCol(enemy->GetPos(), enemy->GetR(), P, player->GetThickness())) {
				//食える時
				if (expM->GetLevel() >= enemy->GetLv()) {
					player->AddBodyLength(enemy->GetHang());
					expM->AddExp(enemy->GetEXP());
					if (enemy->GetIsCook()) {
						player->AddBodyLength(enemy->GetHang() / 1.25f);
						expM->AddExp(enemy->GetEXP() / 2.5f);
					}
					enemy->SetIsDead();
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
							expM->AddExp(enemy->GetEXP());
							if (enemy->GetIsCook()) {
								player->AddBodyLength(enemy->GetHang());
								expM->AddExp(enemy->GetEXP());
							}
							enemy->SetIsDead();
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
		for (int i = 0; i < 3; i++) {
			if (ExBodyManager::GetInstance()->GetBodyType(i) == BodyType::Shark) {
				if (CircleCol(player->GetPos((i + 1) * exBodyM->GetBodySpace() + 8), 150, enemy->GetPos(), enemy->GetR())) {
					//食える時
					if (expM->GetLevel() >= enemy->GetLv()) {
						player->AddBodyLength(enemy->GetHang());
						expM->AddExp(enemy->GetEXP());
						if (enemy->GetIsCook()) {
							player->AddBodyLength(enemy->GetHang());
							expM->AddExp(enemy->GetEXP());
						}
						enemy->SetIsDead();
					}
				}
			}
		}
		for (PlayerBullet* bullet : bulletM->GetBulletList()) {
			if (CircleCol(bullet->GetPos(), bullet->GetR(), enemy->GetPos(), enemy->GetR())) {
				bullet->SetIsDead();
				enemy->SetIsCook();
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
#pragma once
#include "Enemy.h"

class EnemyManager {
private:
	EnemyManager() = default;
	~EnemyManager() = default;
public:
	//コピーコンストラクタ無効
	EnemyManager(const EnemyManager& obj) = delete;
	//代入演算子を無効
	EnemyManager& operator=(const EnemyManager& obj) = delete;

	static EnemyManager* GetInstance();

	void Initialize();
	void Update();
	void Draw();

	int GetEnemyNum() {
		return MAX_ENEMY;
	}

	Vector2 GetEnemyPos(int i) {
		return enemy_[i].GetPos();
	}

	bool GetEnemyIsDead(int i) {
		return enemy_[i].GetIsDead();
	}
	void SetEnemyIsDead(int i) {
		enemy_[i].SetIsDead(true);
	}

private:
	static const int MAX_ENEMY = 100;

	Enemy enemy_[MAX_ENEMY];
};
#pragma once
#include "Enemy.h"
#include <list>
#include "BaseEnemy.h"
#include <memory>

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

	std::list<BaseEnemy*> GetEnemyList() {
		enemys2_.clear();
		for (std::unique_ptr<BaseEnemy>& enemy : enemys_) {
			enemys2_.push_back(enemy.get());
		}
		return enemys2_;
	}

	//敵の生成
	void PopPlankton(Vector2 pos, float rot);

private:
	std::list<std::unique_ptr<BaseEnemy>> enemys_;
	std::list<BaseEnemy*> enemys2_;

	static const int MAX_ENEMY = 100;

	Enemy enemy_[MAX_ENEMY];
};
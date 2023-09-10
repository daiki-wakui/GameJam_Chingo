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

	std::list<BaseEnemy*> GetEnemyList() {
		enemys2_.clear();
		for (std::unique_ptr<BaseEnemy>& enemy : enemys_) {
			enemys2_.push_back(enemy.get());
		}
		return enemys2_;
	}

	//敵の生成
	void PopPlankton();
	void RePopPlankton();
	void PopFish();
	void PopDolphin();
	void PopWhale();

	void AddPlanktonNum() {
		planktonNum_++;
	}
	void AddFishNum() {
		fishNum_++;
	}
	void AddDolphinNum() {
		dolphinNum_++;
	}

private:
	std::list<std::unique_ptr<BaseEnemy>> enemys_;
	std::list<BaseEnemy*> enemys2_;

	const int MAX_PLANKTON = 100;
	int planktonNum_;

	const int MAX_FISH = 30;
	const int TIME_FISH_POP = 2 * 60;
	int fishNum_;
	int fishPopTimer_;

	const int MAX_DOLPHIN = 15;
	const int TIME_DOLPHIN_POP = 5 * 60;
	int dolphinNum_;
	int dolphinPopTimer_;
};
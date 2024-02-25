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
	void RePopPlankton(int num);
	void PopFish();
	void PopDolphin();
	void PopWhale();
	void PopSakaban();

	void AddPlanktonNum(int type) {
		planktonNum_[type]++;
	}
	void AddFishNum() {
		fishNum_++;
	}
	void AddDolphinNum() {
		dolphinNum_++;
	}
	void AddWhaleNum() {
		whaleNum_++;
	}

	bool GetIsWhaleAlive() {
		return whaleNum_;
	}

private:
	std::list<std::unique_ptr<BaseEnemy>> enemys_;
	std::list<BaseEnemy*> enemys2_;

	const int MAX_PLANKTON = 30;
	int planktonNum_[8];

	const int MAX_FISH = 50;
	const int TIME_FISH_POP = 30; //0.5s
	int fishNum_;
	int fishPopTimer_;

	const int MAX_DOLPHIN = 30;
	const int TIME_DOLPHIN_POP = 60; //1.0s
	int dolphinNum_;
	int dolphinPopTimer_;

	int whaleNum_;

	const int TIME_SAKABAN_POP = 10 * 60;
	int sakabanPopTimer_;

	const int oneFramePop_ = 1;
	int popTimer_;
};
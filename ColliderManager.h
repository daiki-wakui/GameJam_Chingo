#pragma once
#include "Player.h"
#include "EnemyManager.h"

class ColliderManager {
private:
	ColliderManager() = default;
	~ColliderManager() = default;
public:
	//コピーコンストラクタ無効
	ColliderManager(const ColliderManager& obj) = delete;
	//代入演算子を無効
	ColliderManager& operator=(const ColliderManager& obj) = delete;

	static ColliderManager* GetInstance();

	void Update();

	bool CircleCol(Vector2 Ap,int Ar,Vector2 Bp,int Br);
};
#pragma once
#include "Player.h"
#include "EnemyManager.h"

class ColliderManager {
private:
	ColliderManager() = default;
	~ColliderManager() = default;
public:
	//�R�s�[�R���X�g���N�^����
	ColliderManager(const ColliderManager& obj) = delete;
	//������Z�q�𖳌�
	ColliderManager& operator=(const ColliderManager& obj) = delete;

	static ColliderManager* GetInstance();

	void Update();

	bool CircleCol(Vector2 Ap,int Ar,Vector2 Bp,int Br);
};
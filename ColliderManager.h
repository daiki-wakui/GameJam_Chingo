#pragma once
#include "Player.h"
#include "EnemyManager.h"
#include "DxLib.h"

class ColliderManager {
private:
	ColliderManager() = default;
	~ColliderManager() = default;

	int playerDamaged = LoadSoundMem("GameAssets/Sound/SFX_PlayerDamaged.wav");
	int playerEat = LoadSoundMem("GameAssets/Sound/SFX_eat.wav");

	float sharkPar = 0.33f;

public:
	//�R�s�[�R���X�g���N�^����
	ColliderManager(const ColliderManager& obj) = delete;
	//������Z�q�𖳌�
	ColliderManager& operator=(const ColliderManager& obj) = delete;

	static ColliderManager* GetInstance();

	void Initialize();
	void Update();

	bool CircleCol(Vector2 Ap,int Ar,Vector2 Bp,int Br);
};
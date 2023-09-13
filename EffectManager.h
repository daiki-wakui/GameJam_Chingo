#pragma once
#include "MathManager.h"
#include <list>

struct Effect {
	Vector2 pos;
	float r;
	Vector2 way;
	Vector3 color;
};

class EffectManager
{
private:
	EffectManager() = default;
	~EffectManager() = default;
public:
	//�R�s�[�R���X�g���N�^����
	EffectManager(const EffectManager& obj) = delete;
	//������Z�q�𖳌�
	EffectManager& operator=(const EffectManager& obj) = delete;

	static EffectManager* GetInstance();

	void Initialize();
	void Update();
	void Draw();

	void Pop(Vector2 pos);

private:
	std::list<Effect> effects_;
};


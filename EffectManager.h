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
	//コピーコンストラクタ無効
	EffectManager(const EffectManager& obj) = delete;
	//代入演算子を無効
	EffectManager& operator=(const EffectManager& obj) = delete;

	static EffectManager* GetInstance();

	void Initialize();
	void Update();
	void Draw();

	void Pop(Vector2 pos);

private:
	std::list<Effect> effects_;
};


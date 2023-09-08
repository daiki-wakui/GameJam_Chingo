#pragma once
#include "MathManager.h"
#include "DxLib.h"

class Enemy {
public:
	void Initialize(Vector2 pos);
	void Update();
	void Draw();
	void SetRotation(float rot) { rot_ = rot; }

	Vector2 GetPos() {
		return pos_;
	}

	bool GetIsDead() {
		return isDead_;
	}
	void SetIsDead(bool is) {
		isDead_ = is;
	}

private:
	int planktonImage = LoadGraph("GameAssets/Sprite/Enemy_Plankton_01.png");

	Vector2 pos_;
	int r_;
	bool isDead_;
	int deadTimer_;
	float rot_;
	float frame_;
	float addFrame_;
};
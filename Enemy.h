#pragma once
#include "MathManager.h"

class Enemy {
public:
	void Initialize(Vector2 pos);
	void Update();
	void Draw();

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
	Vector2 pos_;
	int r_;
	bool isDead_;
	int deadTimer_;
};
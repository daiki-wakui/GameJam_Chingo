#pragma once
#include "MathManager.h"

class PlayerBullet{
public:
	void Initialize(Vector2 pos, Vector2 way);
	void Update();
	void Draw();

	bool GetIsDead() {
		return isDead_;
	}
	void SetIsDead() {
		isDead_ = true;
	}

	Vector2 GetPos() {
		return pos_;
	}
	int GetR() {
		return R;
	}


private:
	const int SPEED = 3;
	const int TIME = 15 * 60;
	const int R = 10;

	Vector2 pos_;
	Vector2 way_;
	int timer_;
	bool isDead_;
};


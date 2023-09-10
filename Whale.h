#pragma once
#include "BaseEnemy.h"

class Whale : public BaseEnemy {
public:
	void Initialize(Vector2 pos) override;
	void Update() override;
	void Draw() override;

private:
	const int RADIUS = 100;
	const int HANG = 300;
	const int EXP = 300;

	const float SPEED_MOVE = 0.5f;

	bool isWay_;

	int texture_;
};
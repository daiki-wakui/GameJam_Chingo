#pragma once
#include "BaseEnemy.h"

class Fish : public BaseEnemy{
public:
	void Initialize(Vector2 pos) override;
	void Update() override;
	void Draw() override;

private:
	const int RADIUS = 15;
	const int HANG = 30;
	const int EXP = 30;

	const float SPEED_MOVE = 1.5f;

	bool isWay_;

	int texture_;
};

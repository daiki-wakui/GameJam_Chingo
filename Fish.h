#pragma once
#include "BaseEnemy.h"

class Fish : public BaseEnemy{
public:
	void Initialize(Vector2 pos) override;
	void Update() override;
	void Draw() override;

private:
	const int RADIUS = 10;
	const int HANG = 10;
	const int EXP = 10;

	const float SPEED_MOVE = 0.5f;

	bool isWay_;
};

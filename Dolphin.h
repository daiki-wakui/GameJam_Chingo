#pragma once
#include "BaseEnemy.h"

class Dolphin : public BaseEnemy {
public:
	void Initialize(Vector2 pos) override;
	void Update() override;
	void Draw() override;

private:
	const int RADIUS = 50;
	const int HANG = 50;
	const int EXP = 100;
	const float SPEED_MOVE = 3.0f;

	bool isWay_;
	float originY_;
	float frame_;
};
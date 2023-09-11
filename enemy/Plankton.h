#pragma once
#include "BaseEnemy.h"

class Plankton : public BaseEnemy {
public:
	void Initialize(Vector2 pos) override;
	void Update() override;
	void Draw() override;

private:
	const int RADIUS = 5;
	const int HANG = 15;
	const int EXP = 10;
	const int LV = 1;

	float frame_;
	float addFrame_;
};
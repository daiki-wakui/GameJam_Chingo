#pragma once
#include "BaseEnemy.h"

class Plankton : public BaseEnemy {
public:
	void Initialize(Vector2 pos) override;
	void Update() override;
	void Draw() override;

	void SetType(int num) {
		type_ = num;
	}

private:
	const int RADIUS = 15;
	const int HANG = 15;
	const int EXP = 15;
	const int LV = 1;

	float frame_;
	float addFrame_;
};
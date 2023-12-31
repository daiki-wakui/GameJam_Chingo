#pragma once
#include "BaseEnemy.h"

class Sakaban : public BaseEnemy {
public:
	void Initialize(Vector2 pos) override;
	void Update() override;
	void Draw() override;
	Vector2 Col(int num) override;

private:
	const int RADIUS = 25;
	const int HANG = 50;
	const int EXP = 150;
	const int LV = 2;

	const float SPEED_MOVE = 2.5f;

	bool isWay_;

	int texture_;

	static const int MAX_COL = 2;
	Vector2 colPos_[MAX_COL];
};

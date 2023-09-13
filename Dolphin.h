#pragma once
#include "BaseEnemy.h"

class Dolphin : public BaseEnemy {
public:
	void Initialize(Vector2 pos) override;
	void Update() override;
	void Draw() override;
	Vector2 Col(int num) override;

private:
	const int RADIUS = 50;
	const int HANG = 50;
	const int EXP = 75;
	const float SPEED_MOVE = 8.5f;
	const int LV = 3;

	bool isWay_;
	float originY_;
	float frame_;

	int lvImage_;

	static const int MAX_COL = 2;
	Vector2 colPos_[MAX_COL];
};
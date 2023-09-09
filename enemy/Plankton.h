#pragma once
#include "BaseEnemy.h"
#include "DxLib.h"

class Plankton : public BaseEnemy {
public:
	void Initialize(Vector2 pos) override;
	void Update() override;
	void Draw() override;

private:
	const int RADIUS = 5;
	const int HANG = 10;
	const int EXP = 10;

	int planktonImage = LoadGraph("GameAssets/Sprite/Enemy_Plankton_01.png");
	float frame_;
	float addFrame_;
};
#pragma once
#include "DxLib.h"

class ClearScene
{
private:
	int backBottomImage = LoadGraph("GameAssets/Sprite/background_bottom.png");
	int blueImage = LoadGraph("GameAssets/Sprite/blue.png");
	int vignetImage = LoadGraph("GameAssets/Sprite/vignette.png");
	int chinanaImage = LoadGraph("GameAssets/Sprite/chinana.png");

public:

	void Initialize();
	void Update();
	void Draw();
};


#pragma once
#include "DxLib.h"

class ClearScene
{
private:
	int backBottomImage = LoadGraph("GameAssets/Sprite/background_bottom.png");
	int blueImage = LoadGraph("GameAssets/Sprite/blue.png");
	int vignetImage = LoadGraph("GameAssets/Sprite/vignette.png");
	int chinanaImage = LoadGraph("GameAssets/Sprite/chinana.png");

	int muscularImage = LoadGraph("GameAssets/Sprite/Body/muscular.png");
	int magicianImage = LoadGraph("GameAssets/Sprite/Body/magician.png");
	int jetImage = LoadGraph("GameAssets/Sprite/Body/jet.png");
	int gamingImage = LoadGraph("GameAssets/Sprite/Body/gamers.png");

	int targetImage = LoadGraph("GameAssets/Sprite/target.png");

public:

	void Initialize();
	void Update();
	void Draw();
};


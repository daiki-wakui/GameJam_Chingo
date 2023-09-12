#pragma once
#include "DxLib.h"
#include "Vector2.h"

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

	int ResultUI[20];
	int levelImage[4];


	Vector2 titleSize = { 0,0 };
	Vector2 BodyUISize = { 0,0 };
	Vector2 BodyUIStartPos[4];
	Vector2 BodyUIEndPos[4];

	int titleAnimeTimer = 0;
	int titleAnimeMaxTimer = 23;
	int rot = 0;

	int frame = 0;

	float UIFrame[4];

	Vector2 tempPos[4];
public:

	void Initialize();
	void Update();
	void Draw();
};


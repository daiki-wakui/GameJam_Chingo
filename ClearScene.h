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

	int kansei1 = LoadSoundMem("GameAssets/Sound/kansei1.wav");
	int kansei2 = LoadSoundMem("GameAssets/Sound/kansei2.wav");
	bool isSE_ = false;


	int mouseLeftImage = LoadGraph("GameAssets/Sprite/UI/mouseLeftUI.png");


	int ResultUI[30];
	int levelImage[4];

	Vector2 mouseLeftSize = { 0,0 };
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

	int alpha_;

	int mouseX_, mouseY_;
	bool isChange;

public:

	bool GetIsChange() { return isChange; }

	void Initialize();
	void Update();
	void Draw();
};


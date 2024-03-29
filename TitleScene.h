#pragma once
#include "DxLib.h"
#include "Vector2.h"
#include "Keyboard.h"
#include <memory>


class TitleScene
{
private:

	int bubbleImage = LoadGraph("GameAssets/Sprite/bubble.png");
	int gameStartImage = LoadGraph("GameAssets/Sprite/gameStart.png");
	int fukidasiImage = LoadGraph("GameAssets/Sprite/fukidasi.png");
	int blueImage = LoadGraph("GameAssets/Sprite/blue.png");
	int vignetImage = LoadGraph("GameAssets/Sprite/vignette.png");
	int titleImage = LoadGraph("GameAssets/Sprite/title.png");
	int moleImage = LoadGraph("GameAssets/Sprite/mole2.png");
	int backBottomImage = LoadGraph("GameAssets/Sprite/background_bottom.png");

	int mouseImage[2];
	int ABotanImage;

	int anagoImage[2];

	Vector2 startAnago[4];
	Vector2 endAnago[4];
	Vector2 AnagoPos[4];

	int startSE = LoadSoundMem("GameAssets/Sound/start.mp3");
	

	Keyboard* keyboard = Keyboard::GetInstance();

	static const int BUBBLE_SUM = 500;

	Vector2 bubblePos[BUBBLE_SUM];
	float size[BUBBLE_SUM];

	int mouseX_, mouseY_;

	Vector2 start[BUBBLE_SUM];
	Vector2 end[BUBBLE_SUM];

	float timer;
	float maxTimer = 60;

	bool isChangeStart = false;
	bool isChange = false;

	Vector2 titleUI = { 0,0 };
	Vector2 gameStartUI = { 550 ,500 };
	Vector2 mouseUI = { 550 ,500 };
	float startUIRot_ = 0;
	float startUISize_ = 180;
	float frame_[2];
	int state_;
	
	bool backResult;
	int feadAlpha = 255;

public:

	bool GetIsSceneChange() { return isChange; }

	bool GetIsChangeStart(){ return isChangeStart; }
	void SetIsSceneChange(bool change) { isChangeStart = change; }

	bool GetIsbackResult() { return backResult; }
	void SetIsbackResult(bool backresult) { backResult = backresult; }


	void Initialize();
	void Update();
	void Draw();
};


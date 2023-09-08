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

	Keyboard* keyboard = Keyboard::GetInstance();

	static const int BUBBLE_SUM = 500;

	Vector2 bubblePos[BUBBLE_SUM];
	float size[BUBBLE_SUM];

	Vector2 emitterLeftTop;
	Vector2 emitterRightBotoom;
	int mouseX_, mouseY_;

	Vector2 start[BUBBLE_SUM];
	Vector2 end[BUBBLE_SUM];

	float timer;
	float maxTimer = 100;

	bool isChangeStart = false;
	bool isChange = false;

	Vector2 gameStartUILeft = { 520 ,250 + 520 };
	Vector2 gameStartUIRight = { 530 ,100 + 530 };

public:

	bool GetIsSceneChange() { return isChange; }

	bool GetIsChangeStart(){ return isChangeStart; }
	void SetIsSceneChange(bool change) { isChangeStart = change; }

	void Initialize();
	void Update();
	void Draw();
};


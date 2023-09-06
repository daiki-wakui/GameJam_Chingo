#pragma once
#include "DxLib.h"
#include "Vector2.h"
#include "Keyboard.h"
#include <memory>


class TitleScene
{
private:

	int bubbleImage = LoadGraph("GameAssets/Sprite/bubble.png");

	Keyboard* keyboard = Keyboard::GetInstance();

	static const int BUBBLE_SUM = 500;

	Vector2 bubblePos[BUBBLE_SUM];
	float size[BUBBLE_SUM];

	Vector2 emitterLeftTop;
	Vector2 emitterRightBotoom;
	int mouseX_, mouseY_;


public:

	void Initialize();
	void Update();
	void Draw();
};


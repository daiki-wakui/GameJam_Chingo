#pragma once
#include "MathManager.h"

class Player {
public:
	void Initialize();
	void Update();
	void Draw();

private:
	Vector2 pos_;//顏の位置
	Vector2 mouseWay_;//マウスの位置
	Vector2 originPos_;//チンアナゴの出る位置
	int length_;
	int mouseX_, mouseY_;
};
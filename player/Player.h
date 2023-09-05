#pragma once
#include "MathManager.h"

class Player {
public:
	void Initialize();
	void Update();
	void Draw();

private:
	static const int MAX_BODY = 255; //体の最大数
	static const int NUM_NECK = 5;	 //首から上の数
	static const int SPEED_NECK = 5; //首の最大回転スピード

	Vector2 pos_[MAX_BODY];//顏の位置
	Vector2 neckWay_;//首の角度
	int oldNeckWay_;//1フレ前の角度
	Vector2 originPos_;//チンアナゴの出る位置
	int mouseX_, mouseY_;

	int maxLength_;
	int activeLength_;

	int mouseAngle_;//マウスの角度
};
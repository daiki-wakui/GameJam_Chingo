#include "Player.h"
#include "DxLib.h"
#include <math.h>

const float PI = 3.1415f;

void Player::Initialize()
{
	originPos_ = { 640,800 };
	for (int i = 0; i < MAX_BODY; i++) {
		pos_[i] = originPos_;
	}

	maxLength_ = 100;
	activeLength_ = NUM_NECK;
	oldNeckWay_ = 180;
}

void Player::Update()
{
	//マウスの場所取得
	GetMousePoint(&mouseX_, &mouseY_);

	//マウスの方向計算
	Vector2 mouseWay;
	mouseWay.x = mouseX_ - pos_[NUM_NECK].x;
	mouseWay.y = mouseY_ - pos_[NUM_NECK].y;
	//単位化
	mouseWay.normalize();

	//角度を計算
	mouseAngle_ = atan2(mouseWay.cross({ 0,-1 }), -mouseWay.dot({ 0,-1 })) / PI * 180;
	//0~360調整
	if (mouseAngle_ <= 0) {
		mouseAngle_ += 360;
	}
	DrawFormatString(0,0,GetColor(255,255,255),"angle = %d",mouseAngle_);
	//0と360を繋ぐ処理
	if (oldNeckWay_ + 180 < mouseAngle_) {
		oldNeckWay_ += 360;
	}
	if (oldNeckWay_ - 180 > mouseAngle_) {
		oldNeckWay_ -= 360;
	}
	//首振り速度調整
	if (oldNeckWay_ + SPEED_NECK < mouseAngle_) {
		mouseAngle_ = oldNeckWay_ + SPEED_NECK;
	}
	else if (oldNeckWay_ - SPEED_NECK > mouseAngle_) {

		mouseAngle_ = oldNeckWay_ - SPEED_NECK;
	}
	//次フレーム用に記録
	oldNeckWay_ = mouseAngle_;
	DrawFormatString(0, 20, GetColor(255, 255, 255), "neckAngle = %d", mouseAngle_);
	neckWay_ = { sinf(PI / 180 * mouseAngle_ * -1),cosf(PI / 180 * mouseAngle_ * -1) };
	neckWay_ *= 10;

	//首から上の部分
	for (int i = NUM_NECK; i >= 0; i--) {
		pos_[i] = pos_[NUM_NECK] + neckWay_ * ((i - 5) * -1);
	}

	//伸ばし縮み
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		if (maxLength_ > activeLength_) {
			activeLength_++;

			for (int i = activeLength_ - 1; i >= NUM_NECK - 1; i--) {
				pos_[i + 1] = pos_[i];
			}
		}
	}
	else if (activeLength_ > NUM_NECK) {
		activeLength_--;
		for (int i = NUM_NECK - 1; i < activeLength_ + 1; i++) {
			pos_[i] = pos_[i + 1];
		}
	}


}

void Player::Draw()
{
	//チンアナゴ
	for (int i = 0; i < activeLength_; i++) {
		DrawCircle(pos_[i], BODY_THICKNESS, GetColor(255 - (i * 2), 255, 255));
	}
	DrawLine(pos_[NUM_NECK], pos_[NUM_NECK] + neckWay_, GetColor(255, 0, 0));
}

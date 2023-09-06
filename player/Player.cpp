#include "Player.h"
#include "DxLib.h"
#include <math.h>
#include "DebugManager.h"
#include "LevelManager.h"

const float PI = 3.1415f;

Player* Player::GetInstance()
{
	static Player instance;

	return &instance;
}

void Player::Initialize()
{
	originPos_ = { 640,800 };
	for (int i = 0; i < MAX_BODY; i++) {
		pos_[i] = originPos_;
	}

	maxLength_ = START_BODY_LENGTH;
	activeLength_ = NUM_NECK;
	oldNeckWay_ = 180;//真上が180

	isReturn_ = false;
}

void Player::Update()
{
	//デバッグ処理
	if (DebugManager::GetInstance()->GetIsDebugMode()) {
		maxLength_ = MAX_BODY - 1;
	}
	DrawFormatString(0, 60, GetColor(255, 255, 255), "bodyMaxLength = %d", maxLength_);
	DrawFormatString(0, 80, GetColor(255, 255, 255), "nowLength = %d", activeLength_);

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
	neckWay_ = { sinf(PI / 180 * mouseAngle_ * -1),cosf(PI / 180 * mouseAngle_ * -1) };
	neckWay_ *= 10;

	//首から上の部分
	for (int i = NUM_NECK; i >= 0; i--) {
		pos_[i] = pos_[NUM_NECK] + neckWay_ * ((i - 5) * -1);
	}

	//伸ばし縮み
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && !isReturn_) {
		if (maxLength_ > activeLength_) {
			activeLength_++;

			for (int i = activeLength_ - 1; i >= NUM_NECK - 1; i--) {
				pos_[i + 1] = pos_[i];
			}
		}
	}
	else if (activeLength_ > NUM_NECK) {
		isReturn_ = true;
		//高速縮み
		for (int j = 0; j < 3; j++) {
			activeLength_--;
			for (int i = NUM_NECK - 1; i < activeLength_ + 1; i++) {
				pos_[i] = pos_[i + 1];
			}
			//これ以上縮まない時の例外処理
			if (activeLength_ < NUM_NECK + 1) {
				break;
			}
		}
	}

	if (activeLength_ <= NUM_NECK) {
		isReturn_ = false;
		LevelManager::GetInstance()->IncludeExp();
	}
}

void Player::Draw()
{
	//チンアナゴ
	for (int i = 0; i < activeLength_; i++) {
		DrawCircle(pos_[i], BODY_THICKNESS, GetColor(255, 255, 255 - (i * 2)));
	}
	DrawLine(pos_[NUM_NECK], pos_[NUM_NECK] + neckWay_, GetColor(255, 0, 0));
}

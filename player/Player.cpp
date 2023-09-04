#include "Player.h"
#include "DxLib.h"

void Player::Initialize()
{
	originPos_ = { 640,800 };
	pos_ = { 640,800 };
	length_ = 500;
}

void Player::Update()
{
	//マウスの場所取得
	GetMousePoint(&mouseX_, &mouseY_);

	//マウスの方向計算
	mouseWay_.x = mouseX_ - pos_.x;
	mouseWay_.y = mouseY_ - pos_.y;
	//単位化
	mouseWay_.normalize();
}

void Player::Draw()
{
	//地面
	DrawBox(0, 790, 1280, 900, GetColor(255, 255, 255), true);
	//チンアナゴ
	int a = 0;
	for (int i = 0; i < length_; i++) {
		a++;
		if (originPos_.y + mouseWay_.y * i < mouseY_) {
			DrawCircle(originPos_.x + mouseWay_.x * i, originPos_.y + mouseWay_.y * i, 20, GetColor(100, 100, 100));
			break;
		}
		DrawCircle(originPos_.x + mouseWay_.x * i, originPos_.y + mouseWay_.y * i, 20, GetColor(100, 100, 100));
	}
	for (int i = 0; i < length_ - a; i++) {
		DrawCircle(originPos_.x, originPos_.y + i, 20, GetColor(100, 100, 100));
	}
}

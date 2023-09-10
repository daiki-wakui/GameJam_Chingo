#include "Player.h"
#include "DxLib.h"
#include <math.h>
#include "DebugManager.h"
#include "LevelManager.h"
#include "exBody/ExBodyManager.h"
#include "ScrollManager.h"
#include "Keyboard.h"

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

	maxHunger_ = START_BODY_LENGTH;
	activeLength_ = NUM_NECK;
	oldNeckWay_ = 180;//真上が180

	isReturn_ = false;
	oldLevel_ = 1;

	shrinkDistance_ = 0;
	isBackShakeing_ = false;

	ExBodyManager::GetInstance()->Initialize();

	eyeTexure_ = LoadGraph("GameAssets/Sprite/Body/mainBody_eyes.png");
}

void Player::Update()
{
	//インスタンス呼び出し
	DebugManager* debugM = DebugManager::GetInstance();
	LevelManager* levelM = LevelManager::GetInstance();
	ExBodyManager* exM = ExBodyManager::GetInstance();

	//デバッグ処理
	if (debugM->GetIsDebugMode()) {
		maxHunger_ = MAX_BODY - 1;
	}

	//マウスの場所取得
	GetMousePoint(&mouseX_, &mouseY_);

	//マウスの方向計算
	Vector2 mouseWay;
	mouseWay.x = mouseX_ - pos_[NUM_NECK].x;
	mouseWay.y = mouseY_ - ScrollManager::GetInstance()->GetScroll() - pos_[NUM_NECK].y;
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
	if (GetIsExtend()) {
		mouseAngle_ = 180;
		oldNeckWay_ = mouseAngle_;
	}
	neckWay_ = { sinf(PI / 180 * mouseAngle_ * -1),cosf(PI / 180 * mouseAngle_ * -1) };
	neckWay_ *= 10;

	//首から上の部分
	for (int i = NUM_NECK; i >= 0; i--) {
		pos_[i] = pos_[NUM_NECK] + neckWay_ * ((i - 5) * -1);
	}

	//伸ばし縮み
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && !isReturn_) {
		if (maxHunger_ > activeLength_) {
			shrinkDistance_++;
			activeLength_++;

			for (int i = activeLength_ - 1; i >= NUM_NECK - 1; i--) {
				pos_[i + 1] = pos_[i];
			}
		}
		else {
			isReturn_ = true;
		}
	}
	else if (activeLength_ > NUM_NECK) {
		isReturn_ = true;
		//高速縮み
		for (int j = 0; j < 3; j++) {
			activeLength_--;
			for (int i = 0; i < activeLength_ + 1; i++) {
				pos_[i] = pos_[i + 1];
			}
			//これ以上縮まない時の例外処理
			if (activeLength_ < NUM_NECK + 1) {
				break;
			}
		}
	}

	//縮み切っている状態
	if (GetIsExtend()) {
		//デバッグ用強制レベルアップ
		if (Keyboard::GetInstance()->KeyTriggerPush(KEY_INPUT_L)) {
			levelM->Debug();
			isReturn_ = true;
		}

		levelM->IncludeExp();
		//縮みきったタイミング
		if (isReturn_) {
			if (oldLevel_ != levelM->GetLevel()) {
				oldLevel_ = levelM->GetLevel();
				exM->SetIsSelect();
			}

			if (shrinkDistance_ >= 30) {
				isBackShakeing_ = true;
			}

		}

		shrinkDistance_ = 0;
		isReturn_ = false;
		levelM->GetMax();
	}

	//各、体の角度
	for (int i = 1; i < activeLength_; i++) {
		Vector2 frontBody = pos_[i - 1] - pos_[i];
		angle_[i] = atan2(frontBody.cross({ 0,-1 }), -frontBody.dot({ 0,-1 })) / PI * 180;
		if (angle_[i] <= 0) {
			angle_[i] += 360;
		}
	}

	//左右をつなげる処理
	for (int i = 0; i < NUM_NECK + 1; i++) {
		if (pos_[i].x < 0) {
			pos_[i].x += 1280;
		}
		else if (pos_[i].x > 1280) {
			pos_[i].x -= 1280;
		}
	}

	exM->Update();
}

void Player::Draw(bool scroll)
{
	//チンアナゴ
	for (int i = 0; i < activeLength_; i++) {
		if (scroll) {
			DrawCircle(pos_[i], BODY_THICKNESS, GetBodyColor(i));
			if (pos_[i].x < BODY_THICKNESS) {
				DrawCircle({ pos_[i].x + 1280,pos_[i].y }, BODY_THICKNESS, GetBodyColor(i));
			}
			if (pos_[i].x > 1280 - BODY_THICKNESS) {
				DrawCircle({ pos_[i].x - 1280,pos_[i].y }, BODY_THICKNESS, GetBodyColor(i));
			}
		}
		else {
			DrawCircleNotScroll(pos_[i], BODY_THICKNESS, GetBodyColor(i));
		}
	}
	DrawLine(pos_[NUM_NECK], pos_[NUM_NECK] + neckWay_, GetColor(255, 0, 0));

	ExBodyManager::GetInstance()->Draw();

	for (int i = 1; i < activeLength_; i++) {
		if (scroll) {
			DrawLine(pos_[i], pos_[i] + Vector2(sinf(PI / 180 * angle_[i] * -1), cosf(PI / 180 * angle_[i] * -1)) * 10, GetColor(100, 100, 100));
		}
		else {
			DrawLineNotScroll(pos_[i], pos_[i] + Vector2(sinf(PI / 180 * angle_[i] * -1), cosf(PI / 180 * angle_[i] * -1)) * 10, GetColor(100, 100, 100));
		}
	}

	if (scroll) {
		DrawRotaGraph3(GetPos(0).x, GetPos(0).y + ScrollManager::GetInstance()->GetScroll(), 128, 128, 0.25, 0.25, (PI / 180 * angle_[1]) + PI, eyeTexure_, true);
	}
	else {
		DrawRotaGraph3(GetPos(0).x, GetPos(0).y, 128, 128, 0.25, 0.25, (PI / 180 * angle_[1]) + PI, eyeTexure_, true);
	}
	DrawFormatString(0, 160, GetColor(255, 255, 255), "bodyMaxLength = %d", maxHunger_);
	DrawFormatString(0, 180, GetColor(255, 255, 255), "nowLength = %d", activeLength_);
	//DrawFormatString(200, 80, GetColor(255, 255, 255), "nowLength = %d", shrinkDistance_);
}

bool Player::GetIsExtend()
{
	if (activeLength_ <= NUM_NECK) {
		return true;
	}
	return false;
}

unsigned int Player::GetBodyColor(int i)
{
	int num = i % 200;
	num -= 100;
	if (num < 0) {
		num *= -1;
	}

	return GetColor(255,255, num * 2);
}

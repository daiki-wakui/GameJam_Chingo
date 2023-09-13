#include "Player.h"
#include <math.h>
#include "DebugManager.h"
#include "LevelManager.h"
#include "exBody/ExBodyManager.h"
#include "ScrollManager.h"
#include "Keyboard.h"
#include "EnemyManager.h"

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
	for (int i = 0; i < MAX_BODY; i++) {
		thickness_[i] = START_BODY_THICKNESS;
	}
	thick_ = START_BODY_THICKNESS;
	invTime_ = 0; 
	bodySpace_ = START_BODY_SPACE;
	speedNeck_ = START_SPEED_NECK;
	addHang_ = 0;
	isSakaban_ = false;

	ExBodyManager::GetInstance()->Initialize();

	ChangeVolumeSoundMem(128, startExtending);
	ChangeVolumeSoundMem(200, playerExpanding);
	ChangeVolumeSoundMem(200, playerShrinking);
	ChangeVolumeSoundMem(180, hungerGaugeEmpty);
	ChangeVolumeSoundMem(140, levelUp);
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
	if (oldNeckWay_ + speedNeck_ < mouseAngle_) {
		mouseAngle_ = oldNeckWay_ + speedNeck_;
	}
	else if (oldNeckWay_ - speedNeck_ > mouseAngle_) {

		mouseAngle_ = oldNeckWay_ - speedNeck_;
	}
	//次フレーム用に記録
	oldNeckWay_ = mouseAngle_;
	if (GetIsExtend()) {
		mouseAngle_ = 180;
		oldNeckWay_ = mouseAngle_;
	}
	neckWay_ = { sinf(PI / 180 * mouseAngle_ * -1),cosf(PI / 180 * mouseAngle_ * -1) };
	neckWay_.normalize();
	neckWay_ *= bodySpace_;

	//首から上の部分
	if (!isReturn_) {
		for (int i = NUM_NECK; i >= 0; i--) {
			pos_[i] = pos_[NUM_NECK] + neckWay_ * ((i - 5) * -1);
		}
	}

	//伸ばし縮み
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && !isReturn_) {
		if (CheckSoundMem(playerExpanding) == 0) {
			PlaySoundMem(playerExpanding, DX_PLAYTYPE_LOOP, true);
		}

		if (!isExtend) {
			PlaySoundMem(startExtending, DX_PLAYTYPE_BACK, true);
			isExtend = true;
		}

		if (maxHunger_ > activeLength_) {
			shrinkDistance_++;
			activeLength_++;

			for (int i = activeLength_ - 1; i >= NUM_NECK - 1; i--) {
				pos_[i + 1] = pos_[i];
			}
		}
		else {
			isReturn_ = true;

			//ゲームシーンのときだけ鳴らす
			if (nowGameScene) {
				if (CheckSoundMem(hungerGaugeEmpty) == 0) {
					PlaySoundMem(hungerGaugeEmpty, DX_PLAYTYPE_BACK, true);
				}
			}
		}
	}
	else if (activeLength_ > NUM_NECK) {
		StopSoundMem(playerExpanding);
		if (CheckSoundMem(playerShrinking) == 0 && EnemyManager::GetInstance()->GetIsWhaleAlive()) {
			PlaySoundMem(playerShrinking, DX_PLAYTYPE_LOOP, true);
		}
		
		isReturn_ = true;
		//高速縮み
		for (int j = 0; j < 5; j++) {
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
			//levelM->Debug();
			//isReturn_ = true;
		}

		levelM->IncludeExp();
		//縮みきったタイミング
		if (isReturn_) {
			StopSoundMem(playerShrinking);
			PlaySoundMem(playerLand, DX_PLAYTYPE_BACK, true);
			if (oldLevel_ != levelM->GetLevel()) {
				oldLevel_ = levelM->GetLevel();
				exM->SetIsSelect();
				PlaySoundMem(levelUp, DX_PLAYTYPE_BACK, true);
			}

			if (shrinkDistance_ >= 30) {
				isBackShakeing_ = true;
			}

		}

		shrinkDistance_ = 0;
		isReturn_ = false;
		isExtend = false;
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

	
	for (int i = activeLength_; i > 0; i--) {
		thickness_[i] = thickness_[i - 1];
	}
	for (int i = activeLength_; i > 0; i--) {
		thickness_[i] = thickness_[i - 1];
	}
	thickness_[0] = thick_;
}

void Player::ResultUpdate()
{
	activeLength_ = 50;
	originPos_ = { 640,950 };

	//マウスの場所取得
	GetMousePoint(&mouseX_, &mouseY_);

	//マウスの方向計算
	Vector2 mouseWay;
	mouseWay.x = mouseX_ - originPos_.x;
	mouseWay.y = mouseY_ - originPos_.y;
	//単位化
	mouseWay.normalize();

	for (int j = 0; j < 50; j++) {
		pos_[0] = pos_[1] + mouseWay * 10;
		for (int i = 50; i >= 0; i--) {
			pos_[i + 1] = pos_[i];
		}
	}

	for (int i = 1; i < activeLength_; i++) {
		Vector2 frontBody = pos_[i - 1] - pos_[i];
		angle_[i - 1] = atan2(frontBody.cross({ 0,-1 }), frontBody.dot({ 0,1 })) / PI * 180;
		if (angle_[i] <= 0) {
			angle_[i] += 360;
		}
	}
}

void Player::Draw(bool scroll)
{
	//DrawLine(mouseX_, mouseY_, pos_[0].x, pos_[0].y + ScrollManager::GetInstance()->GetScroll(), GetColor(200, 200, 200),3);

	//チンアナゴ
	for (int i = activeLength_; i >= 0; i--) {
		if (i < NUM_NECK) {
			if (scroll) {
				if (!(invTime_ % 10 >= 1 && invTime_ % 10 <= 3)) {
					DrawCircle(pos_[i], thickness_[i], GetBodyColor(i));
				}
				if (pos_[i].x < thickness_[i]) {
					if (!(invTime_ % 10 >= 1 && invTime_ % 10 <= 3)) {
						DrawCircle({ pos_[i].x + 1280,pos_[i].y }, thickness_[i], GetBodyColor(i));
					}
				}
				if (pos_[i].x > 1280 - thickness_[i]) {
					if (!(invTime_ % 10 >= 1 && invTime_ % 10 <= 3)) {
						DrawCircle({ pos_[i].x - 1280,pos_[i].y }, thickness_[i], GetBodyColor(i));
					}
				}
			}
			else {
				DrawCircleNotScroll(pos_[i], thickness_[i], GetBodyColor(i));
			}
		}
		else {
			if (scroll) {
				DrawCircle(pos_[i], thickness_[i], GetBodyColor(i));
				if (pos_[i].x < thickness_[i]) {
					DrawCircle({ pos_[i].x + 1280,pos_[i].y }, thickness_[i], GetBodyColor(i));
				}
				if (pos_[i].x > 1280 - thickness_[i]) {
					DrawCircle({ pos_[i].x - 1280,pos_[i].y }, thickness_[i], GetBodyColor(i));
				}
			}
			else {
				DrawCircleNotScroll(pos_[i], thickness_[i], GetBodyColor(i));
			}
		}
	}
	
	if (!(--invTime_ % 10 >= 1 && invTime_ % 10 <= 3)) {
		if (scroll) {
			if (!isSakaban_) {
				DrawRotaGraph3(GetPos(0).x, GetPos(0).y + ScrollManager::GetInstance()->GetScroll(), 128, 128, 0.25, 0.25, (PI / 180 * angle_[1]) + PI, eyeTexure_, true);
			}
			else {
				DrawRotaGraph3(GetPos(0).x, GetPos(0).y + ScrollManager::GetInstance()->GetScroll(), 256, 256, 0.25, 0.25, (PI / 180 * angle_[1]) + PI, sakabanEyeTex, true);

			}
		}
		else {
			if (!isSakaban_) {
				DrawRotaGraph3(GetPos(0).x, GetPos(0).y, 128, 128, 0.25, 0.25, (PI / 180 * angle_[1]) + PI, eyeTexure_, true);
			}
			else {
				DrawRotaGraph3(GetPos(0).x, GetPos(0).y, 256, 256, 0.25, 0.25, (PI / 180 * angle_[1]) + PI, sakabanEyeTex, true);
			}
		}
	}
	
	//DrawFormatString(0, 160, GetColor(255, 255, 255), "bodyMaxLength = %d", maxHunger_);
	//DrawFormatString(0, 180, GetColor(255, 255, 255), "nowLength = %d", activeLength_);

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

	return GetColor(255, 255, num * 2);
}

bool Player::GetInv()
{
	if (invTime_ <= 0) {
		return true;
	}
	return false;
}

void Player::ReSetBody()
{
	for (int i = 0; i < MAX_BODY; i++) {
		pos_[i] = originPos_;
	}
}

void Player::StopSE()
{
	StopSoundMem(startExtending);
	StopSoundMem(playerExpanding);
	StopSoundMem(playerShrinking);
	StopSoundMem(hungerGaugeEmpty);
	StopSoundMem(levelUp);
}

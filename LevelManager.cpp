#include "LevelManager.h"
#include "exBody/ExBodyManager.h"
#include "Player.h"

LevelManager* LevelManager::GetInstance()
{
	static LevelManager instance;

	return &instance;
}

void LevelManager::Initialize()
{
	nowLevel_ = 1;
	nextExp_ = EXP_LV1;
	nowExp_ = 0;
	haveExp_ = 0;

	for (int i = 0; i < 3; i++) {
		haveExpGaugeYTop_[i] = 0;
		nowExpGaugeYTop_[i] = 750;
	}

	levelImage[0] = LoadGraph("GameAssets/Sprite/level1.png");
	levelImage[1] = LoadGraph("GameAssets/Sprite/level2.png");
	levelImage[2] = LoadGraph("GameAssets/Sprite/level3.png");
	levelImage[3] = LoadGraph("GameAssets/Sprite/levelMax.png");

	ChangeVolumeSoundMem(180, canLevelUp);

}

void LevelManager::Update()
{
	Player* player = Player::GetInstance();

	hungerLength_ = player->GetMaxLength() - player->GetActiveBody();
	
	//レベル管理
	if (nowExp_ >= EXP_LV3) {
		nowLevel_ = 4;
		nextExp_ = 0;
		player->SetThickness(BODY_THICKNESS_LV4);
	}
	else if (nowExp_ >= EXP_LV2) {
		nowLevel_ = 3;
		nextExp_ = EXP_LV3;
		player->SetThickness(BODY_THICKNESS_LV3);
	}
	else if (nowExp_ >= EXP_LV1) {
		nowLevel_ = 2;
		nextExp_ = EXP_LV2;
		player->SetThickness(BODY_THICKNESS_LV2);
		if (haveExp_ > EXP_LV3 - EXP_LV2) {
			haveExp_ = EXP_LV3 - EXP_LV2;
		}
	}
	else {
		if (haveExp_ > EXP_LV2) {
			haveExp_ = EXP_LV2;
		}
	}

	//持ってる餌のゲージ増加(透明)
	if (nowLevel_ == 1) {
		haveExpGaugeYTop_[0] = haveExp_ * 2;
	}
	if (nowLevel_ == 2) {
		haveExpGaugeYTop_[1] = haveExp_ * 0.5;
	}
	if (nowLevel_ == 3) {
		haveExpGaugeYTop_[2] = haveExp_ * 0.28;
	}

	//伸び続けてる間に次のレベルになった時の例外処理
	if (nowLevel_ == 1 && GetNowAndHaveExp() >= 100) {
		haveExpGaugeYTop_[1] = (GetNowAndHaveExp() - 100) * 0.5;

		if (!isCanLvUp) {
			PlaySoundMem(canLevelUp, DX_PLAYTYPE_BACK, true);
			isCanLvUp = true;
		}
	}
	if (nowLevel_ == 2 && GetNowAndHaveExp() >= 500) {
		haveExpGaugeYTop_[2] = (GetNowAndHaveExp() - 500) * 0.28;

		if (!isCanLvUp) {
			PlaySoundMem(canLevelUp, DX_PLAYTYPE_BACK, true);
			isCanLvUp = true;
		}
	}
	if (nowLevel_ == 3 && GetNowAndHaveExp() >= 1200) {

		if (!isCanLvUp) {
			PlaySoundMem(canLevelUp, DX_PLAYTYPE_BACK, true);
			isCanLvUp = true;
		}
	}
	
	
	for (int i = 0; i < 3; i++) {
		//レベルアップまでの残りゲージ
		restGrauge[i] = GaugeLength - nowExpGaugeYTop_[i];

		//ゲージが貯まりきったら表示しない
		if (restGrauge[i] <= 0) {
			haveExpGaugeYTop_[i] = 0;
		}
	}

	if (nowLevel_ == 2) {
		nowExpGaugeYTop_[0] = 750;
		haveExpGaugeYTop_[0] = 0;
	}
	if (nowLevel_ == 3) {
		nowExpGaugeYTop_[1] = 750;
		haveExpGaugeYTop_[1] = 0;
	}
	if (nowLevel_ == 4) {
		nowExpGaugeYTop_[2] = 550;
		haveExpGaugeYTop_[2] = 0;
	}
	
	ExBodyManager* exM = ExBodyManager::GetInstance();

	if (isSetRatio_) {
		muscleNum_ = 0;


		if (exM->GetBodyType(nowLevel_-2) == 1) {
			muscleNum_ += 100;
		}

		hungerLength_ = player->GetMaxLength() - player->GetActiveBody();
		hungerLength_++;
		hungerLength_ += muscleNum_;

		ratio_ = 1280.0f / (float)hungerLength_;
		isSetRatio_ = false;
	}

	
}

void LevelManager::Draw()
{
	DrawGraph(2, 790, hungerGaugeBackImage, true);

	if (nowLevel_ == 1) {
		DrawRectGraph(-3, 792, 0, 0, hungerLength_ * 13.4, 128, hungerGaugeBarImage, true);
	}
	else {
		DrawRectGraph(-3, 792, 0, 0, hungerLength_ * ratio_, 128, hungerGaugeBarImage, true);
	}

	/*else if (nowLevel_ == 2) {
		
	}
	else if (nowLevel_ == 3) {
		DrawRectGraph(-3, 792, 0, 0, hungerLength_ * ratio_, 128, hungerGaugeBarImage, true);
	}*/
	DrawGraph(2, 790, hungerGaugeFrameImage, true);

	//ゲージの枠

	DrawBox(1200, 550, 1240, 750, GetColor(16, 16, 103), true);

	//現在のレベル表示
	for (int i = 0; i < 4; i++) {
		if (nowLevel_ == i + 1) {
			DrawExtendGraph(1150, 710, 128 + 1150, 128 + 710, levelImage[i], true);
		}
	}

	//溜まってるゲージの描画レベル1,2,3
	
	DrawBox(1200, nowExpGaugeYTop_[0], 1200 + 40, nowExpGaugeYBottom_[0], GetColor(46, 104, 214), true);
	DrawBox(1200, nowExpGaugeYTop_[1], 1200 + 40, nowExpGaugeYBottom_[1], GetColor(46, 104, 214), true);
	DrawBox(1200, nowExpGaugeYTop_[2], 1200 + 40, nowExpGaugeYBottom_[2], GetColor(46, 104, 214), true);
	DrawBox(1200, 550, 1200 + 40, 750, GetColor(66, 255, 251), false);
	DrawBox(1200+2, 550+2, 1200-2 + 40, 750-2, GetColor(66, 255, 251), false);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//透明ゲージの描画レベル1,2,3
	
	if (nowLevel_ == 1 && GetNowAndHaveExp() >= 100) {
		DrawBox(1200, 550, 1240, nowExpGaugeYTop_[0], GetColor(46, 104, 214), true);
	}
	else {
		DrawBox(1200, (nowExpGaugeYTop_[0] - haveExpGaugeYTop_[0]), 1240, nowExpGaugeYTop_[0], GetColor(46, 104, 214), true);
	}

	if (nowLevel_ == 2 && GetNowAndHaveExp() >= 500) {
		DrawBox(1200, 550, 1240, nowExpGaugeYTop_[1], GetColor(46, 104, 214), true);
	}
	else {
		DrawBox(1200, (nowExpGaugeYTop_[1] - haveExpGaugeYTop_[1]), 1240, nowExpGaugeYTop_[1], GetColor(46, 104, 214), true);
	}

	if (GetNowAndHaveExp() >= 1200) {
		DrawBox(1200, 550, 1240, nowExpGaugeYTop_[1], GetColor(46, 104, 214), true);
	}
	else {
		DrawBox(1200, (nowExpGaugeYTop_[2] - haveExpGaugeYTop_[2]), 1240, nowExpGaugeYTop_[2], GetColor(46, 104, 214), true);

	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//レベルアップ可能表示
	if (nowLevel_ == 1 && GetNowAndHaveExp() >= 100 || nowLevel_ == 2 && GetNowAndHaveExp() >= 500||nowLevel_==3&& GetNowAndHaveExp() >= 1200) {
		DrawExtendGraph(1050, 690, 128 + 1050, 128 + 690, levelUpImage, true);
	}
	
	//DrawFormatString(0,80,GetColor(255,255,255),"nowLevel = %d",nowLevel_);
	//DrawFormatString(0, 100, GetColor(255, 255, 255), "haveExp_ = %d",haveExp_);
	//DrawFormatString(0, 120, GetColor(255, 255, 255), "nowExp_ = %d / %d", nowExp_,nextExp_);
	//DrawFormatString(0, 220, GetColor(255, 255, 255), "plen = %d", Player::GetInstance()->GetMaxLength());
	//DrawFormatString(0, 200, GetColor(255, 255, 255), "hungerlen = %d", hungerLength_);
	//DrawFormatString(0, 240, GetColor(255, 255, 255), "hungerlen+mass = %d", hungerLength_+muscleNum_);
}

void LevelManager::IncludeExp()
{
	isCanLvUp = false;
	nowExp_ += haveExp_;

	//レベル1のゲージ増加
	if (nowLevel_ == 1) {
		nowExpGaugeYTop_[0] -= haveExp_ * 2;
	}

	//レベル2のゲージ増加
	if (nowLevel_ == 2) {
		nowExpGaugeYTop_[1] -= haveExp_ * 0.5;
	}
	else if (nowLevel_ == 1 && nowExp_ >= 100) {
		nowExpGaugeYTop_[1] -= (nowExp_ - 100) * 0.5;
	}

	//レベル3のゲージ増加
	if (nowLevel_ == 3) {
		nowExpGaugeYTop_[2] -= haveExp_ * 0.28;
	}
	else if (nowLevel_ == 2 && nowExp_ >= 500) {
		nowExpGaugeYTop_[2] -= (nowExp_ - 500) * 0.28;
	}

	if (nowLevel_ == 4) {
		nowExpGaugeYTop_[2] = 550;
	}

	haveExp_ = 0;
	Update();
}

void LevelManager::GetMax()
{
	Player* player = Player::GetInstance();

	if (nowExp_ >= EXP_LV3) {
		player->SetMaxLength(HANG_LV4);
	}
	else if (nowExp_ >= EXP_LV2) {
		player->SetMaxLength(HANG_LV3);
	}
	else if (nowExp_ >= EXP_LV1) {
		player->SetMaxLength(HANG_LV2);
	}
	else {
		player->SetMaxLength(HANG_LV1);
	}
}

void LevelManager::Debug()
{
	if (nowLevel_ == 1) {
		nowExp_ += EXP_LV1;
	}
	else if (nowLevel_ == 2) {
		nowExp_ += EXP_LV2;
	}
	else if (nowLevel_ == 3) {
		nowExp_ += EXP_LV3;
	}
}


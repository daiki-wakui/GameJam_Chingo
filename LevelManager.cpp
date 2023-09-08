#include "LevelManager.h"
#include "DxLib.h"

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
}

void LevelManager::Update()
{
	if (nowExp_ >= EXP_LV3) {
		nowLevel_ = 4;
		nextExp_ = 0;
	}
	else if (nowExp_ >= EXP_LV2) {
		nowLevel_ = 3;
		nextExp_ = EXP_LV3;
	}
	else if (nowExp_ >= EXP_LV1) {
		nowLevel_ = 2;
		nextExp_ = EXP_LV2;
	}
	restGrauge[0] = GaugeLength - nowExpGaugeXRight_[0];
	restGrauge[1] = GaugeLength - nowExpGaugeXRight_[1];
	restGrauge[2] = GaugeLength - nowExpGaugeXRight_[2];

	if (nowLevel_ == 1) {
		haveExpGaugeXRight_[0] = haveExp_ * 12;
	}
	if (nowLevel_ == 2) {
		haveExpGaugeXRight_[1] = haveExp_ * 3;
	}
	if (nowLevel_ == 3) {
		haveExpGaugeXRight_[2] = haveExp_ * 2;
	}

	//if (nowLevel_ == 1 && haveExp_ >= 100) {
	//	haveExpGaugeXRight_[1] = (haveExp_ - 100) * 3;
	//	haveExpGaugeXRight_[0] = 1200;
	//}



	//ゲージが貯まりきったら表示しない
	if (restGrauge[0] <= 0) {
		haveExpGaugeXRight_[0] = 0;
	}

	if (restGrauge[1] <= 0) {
		haveExpGaugeXRight_[1] = 0;
	}
}

void LevelManager::Draw()
{
	//レベル1
	DrawBox(nowExpGaugeXLeft_[0], 830, nowExpGaugeXRight_[0] + 40, 880, GetColor(255, 0, 0), true);
	//レベル2
	DrawBox(nowExpGaugeXLeft_[1], 830, nowExpGaugeXRight_[1] + 40, 880, GetColor(0, 255, 0), true);
	//レベル3
	DrawBox(nowExpGaugeXLeft_[2], 830, nowExpGaugeXRight_[2] + 40, 880, GetColor(0, 0, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//レベル1
	DrawBox(haveExpGaugeXLeft_[0] + nowExpGaugeXRight_[0], 830, haveExpGaugeXRight_[0] + nowExpGaugeXRight_[0] + 40, 880, GetColor(255, 0, 0), true);
	//レベル2
	DrawBox(haveExpGaugeXLeft_[1] + nowExpGaugeXRight_[1], 830, haveExpGaugeXRight_[1] + nowExpGaugeXRight_[1] + 40, 880, GetColor(0, 255, 0), true);
	//レベル3
	DrawBox(haveExpGaugeXLeft_[2] + nowExpGaugeXRight_[2], 830, haveExpGaugeXRight_[2] + nowExpGaugeXRight_[2] + 40, 880, GetColor(0, 0, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	
	DrawBox(40, 830, 1240, 880, GetColor(255, 255, 255), false);


	DrawFormatString(0,80,GetColor(255,255,255),"nowLevel = %d",nowLevel_);
	DrawFormatString(0, 100, GetColor(255, 255, 255), "haveExp_ = %d",haveExp_);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "nowExp_ = %d / %d", nowExp_,nextExp_);
	DrawFormatString(0, 140, GetColor(255, 255, 255), "1Exp_ = %d 2 %d  3 %d", restGrauge[0],restGrauge[1],restGrauge[2]);
}

void LevelManager::IncludeExp()
{
	nowExp_ += haveExp_;

	if (nowLevel_ == 1) {
		nowExpGaugeXRight_[0] += haveExp_ * 12;
		nowExpGaugeXRight_[0] = min(nowExpGaugeXRight_[0], 1200);
	}


	if (nowLevel_ == 2) {
		nowExpGaugeXRight_[1] += haveExp_ * 3;

		if (nowExpGaugeXRight_[1] >= 1200) {
			nowExpGaugeXRight_[1] = 1200;
		}
	}
	else if (nowLevel_ == 1 && nowExp_ >= 100) {
		nowExpGaugeXRight_[1] += (nowExp_ - 100) * 3;
	}

	if (nowLevel_ == 3) {
		nowExpGaugeXRight_[2] += haveExp_ * 2;

		if (nowExpGaugeXRight_[2] >= 1200) {
			nowExpGaugeXRight_[2] = 1200;
		}
	}
	else if (nowLevel_ == 2 && nowExp_ >= 500) {
		nowExpGaugeXRight_[2] += (nowExp_ - 500) * 2;
	}


	haveExp_ = 0;
	Update();
}


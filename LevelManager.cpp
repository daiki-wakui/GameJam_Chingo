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

}

void LevelManager::Draw()
{
	DrawFormatString(0,80,GetColor(255,255,255),"nowLevel = %d",nowLevel_);
	DrawFormatString(0, 100, GetColor(255, 255, 255), "haveExp_ = %d",haveExp_);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "nowExp_ = %d / %d", nowExp_,nextExp_);
}


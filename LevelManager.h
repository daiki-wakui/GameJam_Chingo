#pragma once
#include "DxLib.h"

class LevelManager {
private:
	LevelManager() = default;
	~LevelManager() = default;
public:
	//コピーコンストラクタ無効
	LevelManager(const LevelManager& obj) = delete;
	//代入演算子を無効
	LevelManager& operator=(const LevelManager& obj) = delete;

	static LevelManager* GetInstance();

	void Initialize();
	void Update();
	void Draw();

	void AddExp(int num) {
		haveExp_ += num;
	}

	void IncludeExp();

	int GetLevel() {
		return nowLevel_;
	}

	int GetNowAndHaveExp() {
		return nowExp_ + haveExp_;
	}

	void GetMax();

	void Debug();

private:

	int levelUpImage = LoadGraph("GameAssets/Sprite/levelUp.png");

	int hungerGaugeBackImage = LoadGraph("GameAssets/Sprite/UI_gauge_background.png");
	int hungerGaugeFrameImage = LoadGraph("GameAssets/Sprite/UI_gauge_frame.png");
	int hungerGaugeBarImage = LoadGraph("GameAssets/Sprite/UI_gauge_bar.png");

	int levelImage[3];

	const int EXP_LV1 = 100;
	const int EXP_LV2 = 500;
	const int EXP_LV3 = 1200;

	const int HANG_LV1 = 100;
	const int HANG_LV2 = 120;
	const int HANG_LV3 = 150;
	const int HANG_LV4 = 200;

	const int START_BODY_THICKNESS = 30; //体の太さ
	const int BODY_THICKNESS_LV2 = 40;
	const int BODY_THICKNESS_LV3 = 50;
	const int BODY_THICKNESS_LV4 = 60;

	int nowExp_;
	int nextExp_;
	int nowLevel_;
	int haveExp_;

	int haveExpGaugeYBottom_[3] = { 750,750,750 };
	int haveExpGaugeYTop_[3];

	int nowExpGaugeYBottom_[3] = { 750,750,750 };
	int nowExpGaugeYTop_[3] = { 750,750,750 };

	int GaugeLength = 1200;
	int restGrauge[3] = {};

	int level3Exp_;
	int hungerLength_;

};
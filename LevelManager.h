#pragma once

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

private:
	const int EXP_LV1 = 100;
	const int EXP_LV2 = 500;
	const int EXP_LV3 = 1200;

	int nowExp_;
	int nextExp_;
	int nowLevel_;
	int haveExp_;

	int haveExpGaugeXLeft_[3] = { 40,40,40 };
	int haveExpGaugeXRight_[3];

	int nowExpGaugeXLeft_[3] = { 40,40,40 };
	int nowExpGaugeXRight_[3];
};
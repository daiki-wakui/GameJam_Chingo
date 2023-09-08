#pragma once

class LevelManager {
private:
	LevelManager() = default;
	~LevelManager() = default;
public:
	//�R�s�[�R���X�g���N�^����
	LevelManager(const LevelManager& obj) = delete;
	//������Z�q�𖳌�
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

private:
	const int EXP_LV1 = 100;
	const int EXP_LV2 = 500;
	const int EXP_LV3 = 1200;

	int nowExp_;
	int nextExp_;
	int nowLevel_;
	int haveExp_;
};
#pragma once
#include "DxLib.h"

enum BodyType
{
	NONE,
	MUSCLE,
	MAGICIAN,
	JET,
	GAMING,
	Shark,
	END_BODY_TYPE,
};

class ExBodyManager {
private:
	ExBodyManager() = default;
	~ExBodyManager() = default;
public:
	//コピーコンストラクタ無効
	ExBodyManager(const ExBodyManager& obj) = delete;
	//代入演算子を無効
	ExBodyManager& operator=(const ExBodyManager& obj) = delete;

	static ExBodyManager* GetInstance();

	void Initialize();
	void Update();
	void LvUpDraw();
	void Draw();

	void BodyDraw(int i);
	void SelectRand();
	void SelectDraw();
	void ResultDraw();

	void AddBody(int num);

	bool GetIsSelect() {
		return isSelect_;
	}
	void SetIsSelect();

	float GetBodyAngle(int i);
	int GetBodyType(int num) {
		return bodyType_[num];
	}

	int GetBodySpace() {
		return EX_BODY_SPACE;
	}
  
private:
	const int BODY_WIDTH = 60;
	const int BODY_HEIGHT = 100;
	static const int MAX_BODY = 3;
	const int EX_BODY_SPACE = 13;
	const int RESULT_BODY_SPACE = 20;
	const int TIME_BULLET = 3 * 60;
	
	int bodyType_[MAX_BODY];

	int bulletTimer_;

	//体選択画面
	bool isSelect_;
	int choice_[3];

	int muscularImage = LoadGraph("GameAssets/Sprite/Body/muscular.png");
	int magicianImage = LoadGraph("GameAssets/Sprite/Body/magician.png");
	int jetImage = LoadGraph("GameAssets/Sprite/Body/jet.png");
	int gamingImage = LoadGraph("GameAssets/Sprite/Body/gamers.png");
	int shakeImage = LoadGraph("GameAssets/Sprite/Body/body_shark.png");

	bool isRelease = true;
};
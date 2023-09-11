#pragma once
#include "DxLib.h"

enum BodyType
{
	NONE,
	MUSCLE,
	MAGICIAN,
	JET,
	GAMING,
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
	void Draw();
	void LvUpDraw();

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
  
private:
	const int BODY_WIDTH = 60;
	const int BODY_HEIGHT = 100;
	static const int MAX_BODY = 3;
	const int EX_BODY_SPACE = 10;
	const int RESULT_BODY_SPACE = 20;
	
	int bodyType_[MAX_BODY];

	//体選択画面
	bool isSelect_;
	int choice_[3];

	int muscularImage = LoadGraph("GameAssets/Sprite/Body/muscular.png");
	int magicianImage = LoadGraph("GameAssets/Sprite/Body/magician.png");
	int jetImage = LoadGraph("GameAssets/Sprite/Body/jet.png");
	int gamingImage = LoadGraph("GameAssets/Sprite/Body/gamers.png");

	bool isRelease = true;
};
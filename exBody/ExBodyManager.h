#pragma once

enum BodyType
{
	NONE,
	MUSCLE,
	MAGICIAN,
	MOD3,
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

	void BodyDraw(int i);

	void AddBody(int num);

	bool GetIsSelect() {
		return isSelect_;
	}
	void SetIsSelect(bool is) {
		isSelect_ = is;
	}

	float GetBodyAngle(int i);
  
private:
	const int BODY_WIDTH = 60;
	const int BODY_HEIGHT = 100;
	static const int MAX_BODY = 3;
	
	int bodyType_[MAX_BODY];

	//体選択画面
	bool isSelect_;
	int choice_[3];

	int muscularImage;
};
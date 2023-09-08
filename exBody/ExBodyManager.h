#pragma once

enum BodyType
{
	NONE,
	MUSCLE,
	MOD2,
	MOD3,
};

class ExBodyManager {
private:
	ExBodyManager() = default;
	~ExBodyManager() = default;
public:
	//�R�s�[�R���X�g���N�^����
	ExBodyManager(const ExBodyManager& obj) = delete;
	//������Z�q�𖳌�
	ExBodyManager& operator=(const ExBodyManager& obj) = delete;

	static ExBodyManager* GetInstance();

	void Initialize();
	void Update();
	void Draw();

	void BodyDraw(int i);

	void AddBody(int num);

	float GetBodyAngle(int i);
private:
	const int BODY_WIDTH = 60;
	const int BODY_HEIGHT = 100;
	static const int MAX_BODY = 3;
	
	int bodyType_[MAX_BODY];
};
#pragma once

class DebugManager {
private:
	DebugManager() = default;
	~DebugManager() = default;
public:
	//�R�s�[�R���X�g���N�^����
	DebugManager(const DebugManager& obj) = delete;
	//������Z�q�𖳌�
	DebugManager& operator=(const DebugManager& obj) = delete;

	static DebugManager* GetInstance();

public:
	void Initialize();
	void Update();
	void Draw();

	void SetIsDebugMode(bool is) {
		isDebugMode_ = is;
	};
	bool GetIsDebugMode() {
		return isDebugMode_;
	};
private:
	bool isDebugMode_;
};
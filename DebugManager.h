#pragma once

class DebugManager {
private:
	DebugManager() = default;
	~DebugManager() = default;
public:
	//コピーコンストラクタ無効
	DebugManager(const DebugManager& obj) = delete;
	//代入演算子を無効
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
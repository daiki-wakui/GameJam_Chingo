#pragma once
#include "MathManager.h"

class ScrollManager {
private:
	ScrollManager() = default;
	~ScrollManager() = default;
public:
	//コピーコンストラクタ無効
	ScrollManager(const ScrollManager& obj) = delete;
	//代入演算子を無効
	ScrollManager& operator=(const ScrollManager& obj) = delete;

	static ScrollManager* GetInstance();

	float GetScroll();

public:
	const int STOP = 3240;

	float originPos_ = 400;
};
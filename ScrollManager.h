#pragma once
#include "MathManager.h"

class ScrollManager {
private:
	ScrollManager() = default;
	~ScrollManager() = default;
public:
	//�R�s�[�R���X�g���N�^����
	ScrollManager(const ScrollManager& obj) = delete;
	//������Z�q�𖳌�
	ScrollManager& operator=(const ScrollManager& obj) = delete;

	static ScrollManager* GetInstance();

	float GetScroll();

public:
	const int STOP = 3240;

	float originPos_ = 400;
};
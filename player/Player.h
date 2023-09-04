#pragma once
#include "MathManager.h"

class Player {
public:
	void Initialize();
	void Update();
	void Draw();

private:
	Vector2 pos_;//���̈ʒu
	Vector2 mouseWay_;//�}�E�X�̈ʒu
	Vector2 originPos_;//�`���A�i�S�̏o��ʒu
	int length_;
	int mouseX_, mouseY_;
};
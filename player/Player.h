#pragma once
#include "MathManager.h"

class Player {
public:
	void Initialize();
	void Update();
	void Draw();

private:
	static const int MAX_BODY = 255; //�̂̍ő吔
	static const int NUM_NECK = 5;	 //�񂩂��̐�
	static const int SPEED_NECK = 5; //��̍ő��]�X�s�[�h

	Vector2 pos_[MAX_BODY];//���̈ʒu
	Vector2 neckWay_;//��̊p�x
	int oldNeckWay_;//1�t���O�̊p�x
	Vector2 originPos_;//�`���A�i�S�̏o��ʒu
	int mouseX_, mouseY_;

	int maxLength_;
	int activeLength_;

	int mouseAngle_;//�}�E�X�̊p�x
};
#pragma once
#include "MathManager.h"

class Player {
private:
	Player() = default;
	~Player() = default;
public:
	//�R�s�[�R���X�g���N�^����
	Player(const Player& obj) = delete;
	//������Z�q�𖳌�
	Player& operator=(const Player& obj) = delete;

	static Player* GetInstance();

public:
	void Initialize();
	void Update();
	void Draw();

	int GetActiveBody() {
		return activeLength_;
	}
	
	Vector2 GetPos(int i) {
		return pos_[i];
	}

	Vector2 GetOriginPos() {
		return originPos_;
	}

	void AddBodyLength() {
		maxLength_+= 2;
	}

	bool GetIsShakeing() {
		return isBackShakeing_;
	}

	void SetIsShakeing(bool shakeing) {
		isBackShakeing_ = shakeing;
	}

	int GetAngle(int i) {
		return angle_[i];
	}

private:
	static const int MAX_BODY = 1000; //�̂̍ő吔
	static const int NUM_NECK = 5;	 //�񂩂��̐�
	static const int SPEED_NECK = 5; //��̍ő��]�X�s�[�h
	static const int BODY_THICKNESS = 30; //�̂̑���

	static const int START_BODY_LENGTH = 100; //�X�^�[�g���̑̂̍ő咷��

	Vector2 pos_[MAX_BODY];//���̈ʒu
	int angle_[MAX_BODY];//�p�x
	Vector2 neckWay_;//��̊p�x
	int oldNeckWay_;//1�t���O�̊p�x
	Vector2 originPos_;//�`���A�i�S�̏o��ʒu
	int mouseX_, mouseY_;

	int maxLength_;
	int activeLength_;

	int mouseAngle_;//�}�E�X�̊p�x

	bool isReturn_;

	bool isBackShakeing_;

	int oldLevel_;
};
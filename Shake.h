#pragma once
class Shake
{
public:
	//�����o�ϐ��錾
	int randX;
	int randY;
	int isShakeing;
	int timer;
	int max;
	int min;

public:
	//�R���X�g���N�^�錾
	Shake();

	//�����o�֐��錾
	void Effect();

	void Reset();
};


#pragma once
#include "DxLib.h"
#include "Vector3.h"
#include "Vector2.h"

class Keyboard
{
private:
	Keyboard() = default;
	~Keyboard() = default;
public:
	//�R�s�[�R���X�g���N�^����
	Keyboard(const Keyboard& obj) = delete;
	//������Z�q�𖳌�
	Keyboard& operator=(const Keyboard& obj) = delete;

	static Keyboard* GetInstance();


private:

	Vector2 test;

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

public:

	void Update();

	//�������ĂԎ���"KEY_INPUT_����"�ŏo�Ă���

	bool KeyPush(INT16 key);	//�����Ă��
    bool KeyTriggerPush(INT16 key);	//�������u��
	bool KeyRelease(INT16 key);	//�����Ă��
	bool KeyTriggerRelease(INT16 key);	//�������u��

};


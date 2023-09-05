#include "Keyboard.h"

Keyboard* Keyboard::GetInstance()
{
	static Keyboard instance;

	return &instance;
}

void Keyboard::Update()
{
	// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
	for (int i = 0; i < 256; ++i)
	{
		oldkeys[i] = keys[i];
	}
	// �ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);
}

bool Keyboard::KeyPush(INT16 key)
{
	if (keys[key]) {
		return true;
	}
	return false;
}

bool Keyboard::KeyTriggerPush(INT16 key)
{
	if (keys[key] && !oldkeys[key]) {
		return true;
	}

	return false;
}

bool Keyboard::KeyRelease(INT16 key)
{
	if (!keys[key]) {
		return true;
	}

	return false;
}

bool Keyboard::KeyTriggerRelease(INT16 key)
{
	if (!keys[key] && oldkeys[key]) {
		return true;
	}

	return false;
}
